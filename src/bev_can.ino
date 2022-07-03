/**
 * $$$$$$$\  $$$$$$$$\ $$\    $$\ 
 * $$  __$$\ $$  _____|$$ |   $$ |
 * $$ |  $$ |$$ |      $$ |   $$ |
 * $$$$$$$\ |$$$$$\    \$$\  $$  |
 * $$  __$$\ $$  __|    \$$\$$  / 
 * $$ |  $$ |$$ |        \$$$  /  
 * $$$$$$$  |$$$$$$$$\    \$  /   
 * \_______/ \________|    \_/    
 *
 * @name bev_can.ino
 *                              
 * @author Marshal Stewart
 * 
 * APIs for interacting with CAN bus and the devices on it.
 * 
 * @lib https://github.com/tonton81/FlexCAN_T4 
 *
 */


#include "bev_can.h"
#include "bev_logger.h"
#include "bev_state.h"

#include "bev_dbc.h"
#include "bev_dbc-binutil.h"


/** @todo make volatile ? */
static FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

/** @todo make static */
bev_dbc_rx_t DBCParser;


void ServiceCANIdle()
{
    Can0.events();
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
    Can0.setBaudRate(250000);
    Can0.setMaxMB(16);
    Can0.enableFIFO();
    Can0.enableFIFOInterrupt();
    Can0.onReceive(CanSniff);
    Can0.mailboxStatus();
    
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

    static CAN_message_t msg;
    
    if (buffer == nullptr)
        return FAIL;
    
    msg.id = id;
    msg.flags.extended = 0;
    
    for (unsigned i=0; i<len; i++){
        msg.buf[i] = buffer[i];
    }

    Can0.write(msg);

    return OK;

}

void SendInverterEnable() 
{
    static CmdParameters_t cmd = {0};
    cmd.Direction_Command = 0x1;
    SendCommandMessage(&cmd);
}

void SendInverterDisable() 
{
    static CmdParameters_t cmd = {0};
    SendCommandMessage(&cmd);
}

/**
 * @brief 
 * 
 * @param cmd 
 */
void SendCommandMessage(CmdParameters_t *cmd){

    static CAN_message_t msg;

    msg.id = M192_Command_Message_CANID;
    msg.flags.extended = 0;
    msg.len = M192_Command_Message_DLC;
    
    msg.buf[0] = (cmd->Torque_Command * 10) % 256;
    msg.buf[1] = int(cmd->Torque_Command * 10 / 256);
    
    /** @todo should speed mode be disabled? */
    // msg.buf[2] = SpeedCommand % 256;
    // msg.buf[3] = int(SpeedCommand / 256);
    msg.buf[2] = msg.buf[3] = 0;

    msg.buf[4] = (cmd->Direction_Command & 0x1);

    msg.buf[5] = (cmd->InvertedEnable & 0x1);
    msg.buf[5] |= (cmd->Inverter_Discharge & 0x2);
    
    // msg.buf[5] |= (cmd->Speed_Mode_Enabled & 0x4);
    msg.buf[5] |= (cmd->RollingCounter & 0x8);    

    msg.buf[6] = (cmd->Torque_Limit_Command * 10) % 256;
    msg.buf[7] = int(cmd->Torque_Limit_Command * (10 / 256));
    
    Can0.write(msg);

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

    Log.can(msg);
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

/**
 * CAN2Str
 * 
 * @param msg           CAN Message to be casted
 * @param buffer        Buffer that will be written to
 * @param len           Buffer len (not DLC)
 * 
 * @return void
 * 
 * Breaks down CAN message and writes to buffer in CAN King format
 * 
 * TODO: make CAN king format, so we can use parsing tools
 * 
 */
void CAN2Str(const CAN_message_t &msg, char *buffer, size_t len) {

    snprintf(buffer, len, "MB:%d OVERRUN:%d LEN:%d EXT:%d TS:%05d ID:%04lX BUFFER: ", 
              msg.mb, msg.flags.overrun, msg.len, msg.flags.extended, 
              msg.timestamp, msg.id);
    
    /* Adding char '0' to numeric returns ascii value */
    char tmpBuf[msg.len] = {0};
    for ( uint8_t i = 0; i < msg.len; i++ ) {
        tmpBuf[i] = msg.buf[i] + '0';
    }

    /* Append to buffer */
    strncat(buffer, tmpBuf, msg.len);

}
