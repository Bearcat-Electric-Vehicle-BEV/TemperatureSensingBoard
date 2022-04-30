/*
 * $$$$$$$\  $$$$$$$$\ $$\    $$\ 
 * $$  __$$\ $$  _____|$$ |   $$ |
 * $$ |  $$ |$$ |      $$ |   $$ |
 * $$$$$$$\ |$$$$$\    \$$\  $$  |
 * $$  __$$\ $$  __|    \$$\$$  / 
 * $$ |  $$ |$$ |        \$$$  /  
 * $$$$$$$  |$$$$$$$$\    \$  /   
 * \_______/ \________|    \_/    
 *
 * Main.ino
 *                              
 * Created by Xiahua Liu (2020-21)                  
 * Modified by Marshal Stewart (2022-)
 *
 * This is the main file for the BEV TeensyECU. It contains the setup and loop,
 * functions. The intention is for this file to be readable at a high level. 
 * For example a leadership member from another team should be able to read this
 * file and get a good understanding of what is going on. Then be able to 
 * navigate to the various source files for implementation concerns for things 
 * such as I2C or CAN function implementations. 
 *
 */

#include "include/bev_i2c.h"
#include "include/bev_can.h"
#include "include/bev_logger.h"
#include "include/bev_etc.h"

#define PIN_VEHICLE_PWR 2
#define PIN_Brake_Light 5
#define PIN_ECU_OK 9
#define PIN_PRECHARGE_FINISHED 10
#define PIN_READY_TO_GO 11
#define PIN_SHUTDOWN_TTL_OK 12
#define PIN_CAN1_RX 23
#define PIN_CAN1_TX 22
#define PIN_CAN_TRANS_STDBY 33
#define PIN_SDA 19
#define PIN_SCL 18
#define PIN_ACCEL_0 17
#define PIN_ACCEL_1 16
#define PIN_BRAKE_POS 40
#define PIN_SOC 39
#define PIN_SPEAKER 37
#define PIN_RESET 36

/* State Machine Diagram https://drive.google.com/file/d/1_kZ9mo7b1bYq2sO-uvetE1C0Gtml-KTl/view?usp=sharing
 * Original documentation on the states can be found at https://xiahualiu.github.io/posts/bev-tasks/
 */

#define FOREACH_STATE(STATE) \
        STATE(INIT)   \
        STATE(RESET)  \
        STATE(RESET_CONFIRM)   \
        STATE(ERROR_STATE)  \
        STATE(ROUTINE_CHECK)  \
        STATE(PRE_HV_CHECK)  \
        STATE(HV_READY_WAIT)  \
        STATE(PRECHARGE_WAIT)  \
        STATE(READY_TO_GO_WAIT)  \

enum ECUState{
    FOREACH_STATE(GENERATE_ENUM)
};

static const char *STATE_STRING[] = {
    FOREACH_STATE(GENERATE_STRING)
};

ECUState currentState;
IntervalTimer Heartbeat;

// TODO: Marshal (2/14/22) Implement watchdog 

// RMS Command Parameters 
int TorqueCommand = 0;
int SpeedCommand = 0;
int Direction = 0;
int InverterEnabled = 0;
int Duration = 0;

// Display Parameters
int Speed = 0;
int Battery_Temp = 0;
int Battery_Life = 0;
int Range_KM = 0;
int Range_Mins = 0;

void change_state(ECUState newState) {
    currentState = newState;
    char buffer[100];
    snprintf(buffer, 100, "ENTERED %s state", STATE_STRING[newState]);
    Log.info(buffer);
}

void setup() {
 
  Serial.begin(115200); delay(400);
  change_state(INIT);

  // Set Pin Modes
  pinMode(PIN_VEHICLE_PWR, INPUT);
  pinMode(PIN_Brake_Light, OUTPUT);
  pinMode(PIN_ECU_OK, OUTPUT);
  pinMode(PIN_PRECHARGE_FINISHED, INPUT);
  pinMode(PIN_READY_TO_GO, OUTPUT);
  pinMode(PIN_SHUTDOWN_TTL_OK, INPUT);
//  pinMode(PIN_CAN1_RX, INPUT);
//  pinMode(PIN_CAN1_TX, OUTPUT); 
  pinMode(PIN_CAN_TRANS_STDBY, OUTPUT);
  pinMode(PIN_SDA, OUTPUT);
  pinMode(PIN_SCL, OUTPUT);
  pinMode(PIN_ACCEL_0, INPUT);
  pinMode(PIN_ACCEL_1, INPUT);
  pinMode(PIN_BRAKE_POS, INPUT);
  pinMode(PIN_SOC, INPUT);
  pinMode(PIN_SPEAKER, OUTPUT);
  pinMode(PIN_RESET, INPUT);
 
  // Teensy I2C Master Code
  Wire.begin();

  if (!check_display_online()) {
    Log.error("Display not online");
  }

  // Configure CAN BUS 0 
  digitalWrite(PIN_CAN_TRANS_STDBY, LOW); /* optional tranceiver enable pin */
  Can0.begin();
  Can0.setBaudRate(250000);
  Can0.setMaxMB(16);
  Can0.enableFIFO();
  Can0.enableFIFOInterrupt();
  Can0.onReceive(canSniff);
  Can0.mailboxStatus();
  
  Can0.enableMBInterrupts(); // enables all mailboxes to be interrupt enabled
  Can0.mailboxStatus();

  // RMS CAN RX Mailbox
//   Can0.setMBFilter(MB6, 0x123);
//   Can0.setMB(MB6,RX,STD); // Set mailbox as receiving standard frames.

  // RMS CAN TX Mailbox
//  Can0.setMBFilter(MB9, 0x0C0);
//  Can0.setMB(MB9,TX); // Set mailbox as transmit

  sendInverterEnable();

  // PM100Dx Command Message Heartbeat
  Heartbeat.priority(128);
  Heartbeat.begin(sendRMSHeartbeat, HEARTBEAT); // send message at least every half second

}

void loop() {
  
  /* State Machine Flow
   * Function corresponding to state is called inside conditional. Boolean 
   * value determines if machine needs to switch states.
   */

  Can0.events();

  if(checkFaultCodes()) {
      dump_fault_codes();
  }

  int pedal_0 = analogRead(PIN_ACCEL_0);
  int pedal_1 = analogRead(PIN_ACCEL_1); 

  char buffer[100];
  snprintf(buffer, 100, "Pedal Pos 0:%d Pedal Pos 1:%d", 
            pedal_0, pedal_1);

  Log.info(buffer);

  // if (!validate_pedals(pedal_0, pedal_1)) {
  //     Log.critical("Pedal positions not within 10%!!!!"); 
  //     change_state(ERROR_STATE);
  //     return;
  // }

  // if (!validate_current_drawn()) {
  //     Log.critical("Current drawn is over current limit!!!");
  //     change_state(ERROR_STATE);
  //     return;
  // } 

  return;
  
  switch(currentState){
    case INIT:
      carInit();
      break;

    case RESET:
      carReset();
      break;
   
    case RESET_CONFIRM:
      resetConfirm();
      break;

    case ERROR_STATE:
      error();
      break;

    case ROUTINE_CHECK:
      routineCheck();
      break;

    case PRE_HV_CHECK:
      preHVCheck();
      break;

    case HV_READY_WAIT:
      HVReadyWait();
      break;
     
    case PRECHARGE_WAIT:
      prechargeWait();
      break;
     
    case READY_TO_GO_WAIT:
      readyToGoWait();
      break;
      
    default:
      char buffer[100];
      snprintf(buffer, 100, "IN UNKNOWN STATE:%d", currentState);
      Log.critical(buffer);
      change_state(ERROR_STATE);
      break;
 }
}

void carInit(){
  // Initialization done in setup(), function here for completeness
  digitalWrite(PIN_ECU_OK, LOW);
  
  // TODO: determine if busy waiting is the best strategy
//  while (digitalRead(PRECHARGE_FINISHED) != HIGH);

  change_state(RESET);

}

void carReset(){
  digitalWrite(PIN_ECU_OK, LOW);
  // digitalRead(PIN_PRECHARGE_FINISHED);
  // TODO: Marshal (2/14/22) Reset memory when memory is implemented

  // Passed reset
  change_state(HV_READY_WAIT);

  // If Failed to RESET
  change_state(ERROR_STATE);

}

void resetConfirm(){
}
  
void error(){

    Log.critical("Entered ERROR STATE!!!");
    digitalWrite(PIN_ECU_OK, LOW);

    // Inverter enable sends a 0 torque command to stop motor
    sendInverterEnable();
    Heartbeat.end();

    // TODO: prepare for shutdown or something? 

}

void routineCheck(){
}

void preHVCheck(){
  // TODO: add checks

}

void HVReadyWait(){
//  digitalWrite(PIN_ECU_OK, HIGH);
//  digitalWrite(PIN_HV_READY, HIGH);
//  return true;
}

void prechargeWait(){

  if (analogRead(PIN_SOC) > 500){
    // TODO: SOC needs ADC mapped
  }

  // if passed precharge wait
  change_state(READY_TO_GO_WAIT);
}
  
void readyToGoWait(){
  /* Main Loop Code Here */


}
