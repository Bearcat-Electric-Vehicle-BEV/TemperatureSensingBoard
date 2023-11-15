/**
 * @file Main.ino
 * @author Marshal Stewart (stewa2m3@mail.uc.edu)
 * @brief Sir Percy 
 * @version v1.2
 * @date 2023-011-014
 * 
 * This is the main file for the BEV Temperature Sensing Board. In this file an external ADC is sampled 
 * via SPI, and a checksum is calculated and sent to the Orion BMS 2. For more information on either the ADC
 * SPI communication or Orion BMS 2 Thermal Expansion Module CAN protocol. Please see their respected documentation
 * in sharepoint.
 *  
 * $$$$$$$\  $$$$$$$$\ $$\    $$\
 * $$  __$$\ $$  _____|$$ |   $$ |
 * $$ |  $$ |$$ |      $$ |   $$ |
 * $$$$$$$\ |$$$$$\    \$$\  $$  |
 * $$  __$$\ $$  __|    \$$\$$  /
 * $$ |  $$ |$$ |        \$$$  /
 * $$$$$$$  |$$$$$$$$\    \$  /   
 * \_______/ \________|    \_/    
 * Copyright University of Cincinnati 2023
 * 
 */

/* Required for SPI */
#include "SPI.h"
#include "SPI_MSTransfer_MASTER.h"

/* Required for CAN */
#include <FlexCAN_T4.h>

/* Free rtos includes */
#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>

/* ADC lookup table */
#include "temp_lookup.h"

/* Uncomment macro def DEBUG if you want to debug */
//#define DEBUG

// Declare CAN HW object
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> can0;

// Declare SPI HW object
SPI_MSTransfer_MASTER<&SPI, 10, 0x1235> mySPI1235;

/* Freertos definitions */
TaskHandle_t pxBMSTaskHandle;
void vBMSTask(void *pvParameters);

// Debug CAN print function
static void CAN2Str(const CAN_message_t &msg, char *buffer, size_t len);

void setup()
{
#ifdef DEBUG
    Serial.begin(115200);
#endif
    
    // Initialize Hardware
    SPI.begin();

    // No idea... Might be CS? Kinda doubt it. Best to leave alone. Won't have an impact
    pinMode(0, OUTPUT);
    digitalWrite(0, HIGH);
    
    // CAN Trans STANDY pin, enable is ACTIVE-LOW
    pinMode(33, OUTPUT);
    digitalWrite(33, LOW);
   
    // Application specific wrapper for 16-bit SPI library 
    mySPI1235.begin();

    // Start CAN library
    can0.begin();
    can0.setBaudRate(500000);  // 500 Kbit/s

    // Creates the execution task and allocates a stack size
    xTaskCreate(vBMSTask, "BMS", 4096, nullptr, 5, &pxBMSTaskHandle);

    /* NOTE: Execution doesn't go beyond scheduler */
    vTaskStartScheduler();

    for (;;) { /* Intentionally do nothing */ }
}

/* Debug Function for converting CAN message objects to strings
 */
static void CAN2Str(const CAN_message_t &msg, char *buffer, size_t len)
{

    snprintf(buffer, len, "MB:%d OVERRUN:%d LEN:%d EXT:%d TS:%05d ID:%04lX BUFFER: ",
             msg.mb, msg.flags.overrun, msg.len, msg.flags.extended,
             msg.timestamp, msg.id);

    /* Adding char '0' to numeric returns ascii value */
    char tmpBuf[msg.len] = {0};
    for (uint8_t i = 0; i < msg.len; i++)
    {
        tmpBuf[i] = msg.buf[i] + '0';
    }

    /* Append to buffer */
    strncat(buffer, tmpBuf, msg.len);
}

void loop() { /* Intentionally do nothing */ }


#define ORION_BMS_THERM_EXPANSION_RATE 100
void vBMSTask(__attribute__((unused)) void *pvParameters)
{
    /* Free rtos execution rate */
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(ORION_BMS_THERM_EXPANSION_RATE);

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    // Infinite loop, this is essentially main()
    for (;;)
    {
        /* NOTE: ADC088S022CIMTX SPI Addresses for each channel */
        #define NUM_ADC_CH 7
        const uint16_t address[NUM_ADC_CH] = {0x00, 0x800, 0x1000, 0x1800, 0x2000, 0x2800, 0x3000};
        
        int8_t min = 0; // Min Temp (1 C*)
        int8_t max = 0; // Max Temp (1 C*)
        // NOTE: BMS ignores the average, can still be calculated if needed
        int8_t average = 0; // Average Temp (1 C*)

        uint16_t rxbuff = 0x0; // SPI Rx Buffer
        uint16_t txbuff = 0x0; // SPI Tx Buffer
       
        uint8_t adcRaw = 0x0; // RAW 8-bit ADC value
        int8_t convTemp = 0; // Temperature from ADC table
        
        // Checksum for CAN msg
        uint8_t checksum = 0x0;
        
        // CAN msg object to send to BMS
        CAN_message_t msg;
 
        for (int i = 0; i < NUM_ADC_CH; i++)
        {
            // Load txBuff with SPI CH address
            txbuff = address[i];

            /* NOTE: This function isn't instant. It will busy wait for the HW transfer
             * to complete. In SPI when a tx bit is sent out, an rx bit is usually sent out immediately following.
             * In this case there is a delay and the first 4 bits are don't care. Here they are shifted off. The 
             * ADC is actually an 8-bit ADC. However at least a 12-bit transfer is required. A 16-bit transfer was
             * chosen for ease of implimentation.
             */
            rxbuff = mySPI1235.transfer16(&txbuff, 1, 1);
            adcRaw = (rxbuff >> 4) & 0xff;

            /* NOTE: This section was for playing around with the "center" of the table lookup. The 39 was
             * for offsetting the raw ADC value to be 1* Celsius. This will most likely need to played around with
             * recommend logging the raw ADC value you collect via CAN or Serial. 
             */
            int index = adcRaw - 39;
            if (index < 0)
            {
                index = 0;
            }
            if (index > 57)
            {
                index = 57;
            }
            convTemp = lookup[index];

#ifdef DEBUG
        static int debugAdcCnt = 10;  // Log on serial on first pass
        if (debugAdcCnt >= 10) // 100ms * 10 = 1000ms ; message is logged on serial at a 1s rate. 
        {
            char debugAdcBuf[100];
            snprintf(debugAdcBuf, 100, "Raw ADC Value:0x%X\nConversion Temperature:%d\n", adcRaw, convTemp);
            Serial.println(debugAdcBuf);
            debugAdcCnt = 0; // Reset count
        }
        else
        {
            debugAdcCnt++;
        } 
#endif        
            // ternary operator 
            min = (min > convTemp) ? convTemp : min; 
            max = (max < convTemp) ? convTemp : max; 
        }

        /* NOTE: Here we are creating the msg to send the BMS. For more information about the structure of a 
         * CAN message please see the following examples: https://www.mathworks.com/help/vnt/ug/transmit-and-receive-can-messages.html.
         */

        msg.id = 0x1839F380; // Extended J1939 ID for Orion BMS 2 rx, Thermal Expansion Module tx
        msg.len = 8;
        msg.flags.extended = 1;

        msg.buf[0] = 0x00;    //  rxbuff(0x00)  Thermistor module number
        msg.buf[1] = min;     // min;
        msg.buf[2] = max;     // max;
        msg.buf[3] = average; // average;
        msg.buf[4] = 0x01;    // Number of thermistors enabled   (1)
        msg.buf[5] = 0x01;    // Highest thermistor ID on the module
        msg.buf[6] = 0x00;    // Lowest thermistor ID on the module

        // Checksum 8-bit (sum of all bytes + ID + length)
        checksum = (min + max + average + 0x07 + 0x01 + 0x00 + 0 + 8);
        msg.buf[7] = checksum;

        // Sends CAN Tx message
        can0.write(msg);

#ifdef DEBUG
        static int debugCnt = 10;  // Log on serial on first pass
        if (debugCnt >= 10) // 100ms * 10 = 1000ms ; message is logged on serial at a 1s rate. 
        {
            uint8_t debugBuf[8] = {0};
            CAN2Str(msg, debugBuf, 8);
            Serial.println(debugBuf);
            debugCnt = 0; // Reset count
        }
        else
        {
            debugCnt++;
        } 
#endif        
        
        /* NOTE: How CAN Rx works
         * CAN Rx registers aren't populated async, they need to be manually polled. can0.events() does this
         */
        can0.events();

        // DEBUG: Prints out the current status of all CAN mailboxes
#ifdef DEBUG
        //can0.mailboxStatus();
#endif        

        /* NOTE: Forcing executation rate. The BMS expects a message at a 100ms rate. This task runs at that rate. */
        vTaskDelayUntil(&xLastWakeTime, xFrequency);

    }

    // Never will be here
    configASSERT(NULL);
}
