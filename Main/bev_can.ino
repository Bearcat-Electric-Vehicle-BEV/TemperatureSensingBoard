#include "include/bev_can.h"






/*
 * canSniff
 *
 * Callback function that prints the CAN traffic to Serial Console
 */
void canSniff(const CAN_message_t &msg){
	// DEBUG
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

