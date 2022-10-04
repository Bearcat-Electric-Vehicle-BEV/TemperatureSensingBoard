/**
 * @file bev_can.ino
 * @author Marshal Stewart (stewa2m3@mail.uc.edu)
 * @brief 
 * @version v1.1
 * @date 2022-07-03
 * @link https://github.com/tonton81/FlexCAN_T4 
 *
 * $$$$$$$\  $$$$$$$$\ $$\    $$\
 * $$  __$$\ $$  _____|$$ |   $$ |
 * $$ |  $$ |$$ |      $$ |   $$ |
 * $$$$$$$\ |$$$$$\    \$$\  $$  |
 * $$  __$$\ $$  __|    \$$\$$  /
 * $$ |  $$ |$$ |        \$$$  /
 * $$$$$$$  |$$$$$$$$\    \$  /   
 * \_______/ \________|    \_/    
 * Copyright University of Cincinnati 2022
 * 
 */

#include "bev_logger.h"
#include "bev_state.h"
#include "bev_can.h"

#include "bev_dbc.h"
#include "bev_dbc-binutil.h"

#include <semphr.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

bev_dbc_rx_t DBCParser;

void ServiceCANIdle()
{

    #ifdef DEBUG_BEV
    // Serial.println("Service CAN");
    #endif

    portENTER_CRITICAL();
    Can0.events();
    portEXIT_CRITICAL();

}

/**
 * CANInit
 * 
 * @param void
 * 
 * @return void
 * 
 * Initializes CAN bus, mailboxes, filters. Should be called before attempting to use Can0
 * 
 * @todo #define guards for what messages are being used
 * 
 * @todo Needs reworked and validated
 * 
 */
code_t CANInit(){

    Can0.begin();
    Can0.setBaudRate(500000);
    Can0.setMaxMB(16);

    Can0.enableFIFO();
    // Can0.setFIFOFilter(REJECT_ALL);
    // Can0.setFIFOFilter(0, M192_Command_Message_CANID, STD);
    // Can0.setFIFOFilter(1, MSGID_0X6B2_CANID, STD);
    Can0.enableFIFOInterrupt();
    
    Can0.onReceive(CanSniff);
    Can0.mailboxStatus();
    
    // Can0.enableLoopBack(1);

    /** @todo setup mailbox filters */

    return OK;

}

/**
 * SendMessage
 * 
 * @param id                CAN message ID
 * @param buffer            Buffer to create message from
 * @param len               Length of Buffer (DLC)
 * 
 * @return True/Success, False/Failed
 * 
 * Constructs a CAN msg from parameters and attempts to write to CAN bus. Fails
 * if the user provides an invalid parameter.
 * 
 */
code_t SendMessage(unsigned id, const unsigned *buffer, unsigned len) {

    CAN_message_t msg;
    
    if (buffer == nullptr)
        return FAIL;
    
    msg.id = id;
    msg.flags.extended = 0;
    
    for (unsigned i=0; i<len; i++){
        msg.buf[i] = buffer[i];
    }

    #ifdef DEBUG_BEV
    // Serial.println("Sending Message ID:");
    // Serial.println(msg.id);
    #endif

    vTaskSuspendAll();
    Can0.write(msg);
    xTaskResumeAll();
        
    // if( xSemaphoreTake( xCanSemaphore, ( TickType_t ) 10 ) == pdTRUE )
    // {
    //     xSemaphoreGive(xCanSemaphore);
    // }

    return OK;

}

void SendInverterEnable() 
{
    CmdParameters_t cmd = {0};
    cmd.InvertedEnable = 0x1;
    SendCommandMessage(&cmd);
}

void SendInverterDisable() 
{
    CmdParameters_t cmd = {0};
    cmd.InvertedEnable = 0x0;
    SendCommandMessage(&cmd);
}

/**
 * @brief 
 * 
 * @param cmd 
 */
void SendCommandMessage(CmdParameters_t *cmd){

    CAN_message_t msg;

    msg.id = M192_Command_Message_CANID;
    msg.flags.extended = 0;
    msg.len = M192_Command_Message_DLC;
    
    msg.buf[0] = (cmd->Torque_Command * 10) % 256;
    msg.buf[1] = int(cmd->Torque_Command * 10 / 256);
    
    /** @todo should speed mode be disabled? */
    msg.buf[2] = cmd->Speed_Command % 256;
    msg.buf[3] = int(cmd->Speed_Command / 256);

    msg.buf[4] = (cmd->Direction_Command & 0x1);

    msg.buf[5] = (cmd->InvertedEnable & 0x1);
    msg.buf[5] |= (cmd->Inverter_Discharge & 0x2);
    
    msg.buf[5] |= (cmd->Speed_Mode_Enabled & 0x4);
    msg.buf[5] |= (cmd->RollingCounter & 0x8);    

    msg.buf[6] = (cmd->Torque_Limit_Command * 10) % 256;
    msg.buf[7] = int(cmd->Torque_Limit_Command * (10 / 256));

    #ifdef DEBUG_BEV
    // Serial.println("Sending CMD");
    // Serial.println(msg.id);
    // Log.can(msg);
    #endif

    vTaskSuspendAll();
    Can0.write(msg);
    xTaskResumeAll();

}

/**
 * CanSniff
 * 
 * @param msg       CAN Message Object, passed by reference
 * 
 * @return void
 * 
 * Callback function that assigns incoming signals to globals
 * 
 */
void CanSniff(const CAN_message_t &msg){

    #ifdef DEBUG_BEV
    // Serial.println("Recieved can msg, ID:");
    #endif

    // Log.can(msg);
    bev_dbc_Receive(&DBCParser, msg.buf, msg.id, msg.len);

    /** @todo Orion BMS Checksum */
    // if (msg.id >=BMS_ADDR_LOW && msg.id <= BMS_ADDR_HIGH) {

    //     /* Checksum - Byte 7
    //      1. Take the broadcast ID and add 8 (the length).
    //      2. Add bytes 0-6 to the value from step 1.
    //      3. Chop off the least significant 8 bits (effectively turning
    //         it into an unsigned byte) and that will be the checksum 
    //         value.
    //      4. If the computed checksum doesn't equal the provided checksum, 
    //         the values should be discarded.
    //      */
                
    //         // Checksum
    //         // Expect all message to be 8 bytes in len
    //         int sum = msg.id + 8;
    //         for (int i=0; i<7; i++){
    //             sum += msg.buf[i];
    //         }

    //         sum &= ~8;

    //         if (sum != msg.buf[7]){
    //             Log.error("Failed checksum");
    //             return;
    //         }


    //     }


}

