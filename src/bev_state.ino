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
 * @name bev_state.ino
 *                              
 * @author Marshal
 * 
 * State Machine APIs
 * 
 * State Machine Diagram https://drive.google.com/file/d/1_kZ9mo7b1bYq2sO-uvetE1C0Gtml-KTl/view?usp=sharing
 * Original documentation on the states can be found at https://xiahualiu.github.io/posts/bev-tasks/
 * 
 */


#include "bev_logger.h"
#include "bev_pins.h"
#include "bev_state.h"


ECUState currentState;

/**
 * ChangeState
 * 
 * @param newState		State to change to
 * 
 * @brief Changes current state to newState and logs
 */
void ChangeState(ECUState newState) {
    currentState = newState;
    char buffer[100];
    snprintf(buffer, 100, "ENTERED %s state", STATE_STRING[newState]);
    Log.info(buffer);
}

void carInit(){
  // Initialization done in setup(), function here for completeness
  digitalWrite(PIN_ECU_OK, LOW);
  ChangeState(RESET);
}

void carReset(){
  // TODO (Marsh May 2022): what memory needs reset?

  digitalWrite(PIN_ECU_OK, LOW);
  
  if (digitalRead(PIN_PRECHARGE_FINISHED) == HIGH) {
      ChangeState(PRE_HV_CHECK);
  } 
  else {
    // If Failed to RESET
    ChangeState(ERROR_STATE);
  }

}

void resetConfirm(){
  // TODO (marsh May 2022): is this state necessary?

}
  
void error(){

    Log.critical("Entered ERROR STATE!!!");
    digitalWrite(PIN_ECU_OK, LOW);

    // Inverter enable sends a 0 torque command to stop motor
    SendInverterEnable(); // todo: make a disable command
    // Heartbeat.end();

    // TODO: prepare for shutdown or something? 

}

void routineCheck(){
}

void preHVCheck(){
  // TODO: add checks

  // Check BMS values make sense

  // Check that motor controller make sense

  // Check that display is online

  // check can-bus is online

}