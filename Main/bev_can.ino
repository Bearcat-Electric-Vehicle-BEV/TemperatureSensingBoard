#include "include/bev_can.h"


/*
 * sendInverterEnable
 *
 * Before the inverter can be ran, must send a disable command.
 * For more information see Section 2.2.1 Inverter Enable Safety Options
 * of the RMS CAN Protocol Document
 */
void sendInverterEnable(){
  cmdMsg.id = COMMAND_MESSGE_ADDR;
  cmdMsg.flags.extended = 0;
  cmdMsg.len = 8;

  cmdMsg.buf[0] = 0; 
  cmdMsg.buf[1] = 0; 
  cmdMsg.buf[2] = 0; 
  cmdMsg.buf[3] = 0; 
  cmdMsg.buf[4] = 0; 
  cmdMsg.buf[5] = 0; 
  cmdMsg.buf[6] = 0; 
  cmdMsg.buf[7] = 0;

  Can0.write(cmdMsg);

}

/*
 * sendRMSHeartbeat
 *
 * Populates CAN_message_t cmdMsg, then writes on Can0. For more information
 * on the CAN Command Message for the RMS see Section 2.2 Command Message in
 * the RMS CAN Protocol document. 
 *
 */
void sendRMSHeartbeat(){

  cmdMsg.id = COMMAND_MESSGE_ADDR;
  cmdMsg.flags.extended = 0;
  cmdMsg.len = 8;

  // Construct msg
  cmdMsg.buf[0] = (TorqueCommand * 10) % 256;
  cmdMsg.buf[1] = int(TorqueCommand * 10 / 256);
  cmdMsg.buf[2] = SpeedCommand % 256;
  cmdMsg.buf[3] = int(SpeedCommand / 256);
  cmdMsg.buf[4] = Direction;
  cmdMsg.buf[5] = int(InverterEnabled);
  cmdMsg.buf[6] = 0;
  cmdMsg.buf[7] = 0;
  
  Can0.write(cmdMsg);

}

/*
 * canSniff
 *
 * Callback function that prints the CAN traffic to Serial Console
 */
void canSniff(const CAN_message_t &msg){
	printCANMsg(msg);	

}

/*
 * printCANMsg 
 *
 * Prints a CAN msg to the Serial Console
 */
void printCANMsg(const CAN_message_t &msg){
  Serial.print("MB "); Serial.print(msg.mb);
  Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
  Serial.print("  LEN: "); Serial.print(msg.len);
  Serial.print(" EXT: "); Serial.print(msg.flags.extended);
  Serial.print(" TS: "); Serial.print(msg.timestamp);
  Serial.print(" ID: "); Serial.print(msg.id, HEX);
  Serial.print(" Buffer: ");
  for ( uint8_t i = 0; i < msg.len; i++ ) {
    Serial.print(msg.buf[i], HEX); Serial.print(" ");
  } Serial.println();

}

