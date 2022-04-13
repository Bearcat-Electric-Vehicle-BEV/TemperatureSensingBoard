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

#include <i2c_driver.h>
#include <i2c_driver_wire.h>
#include "include/bev_i2c.h"
#include "include/bev_can.h"
#include "include/bev_sd.h"

#define PIN_VEHICLE_PWR 2
#define PIN_Brake_Light 5
#define PIN_ECU_OK 9
#define PIN_PRECHARGE_FINISHED 10
#define PIN_READY_TO_GO 11
#define PIN_SHUTDOWN_TTL_OK 12
#define PIN_CAN1_RX 23
#define PIN_CAN1_TX 22
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
enum ECUState {
   INIT, RESET, RESET_CONFIRM, ERROR_STATE, ROUTINE_CHECK, PRE_HV_CHECK, 
   HV_READY_WAIT, PRECHARGE_WAIT, READY_TO_GO_WAIT};

ECUState currentState;

IntervalTimer Heartbeat;

// TODO: Marshal (2/14/22) Implement watchdog 
// TODO: Marshal (2/14/22) Need to have a logging and error handling system, example (status/return codes)
double val;
double startTime;
double prechargeTime;
bool timerStarted=false;

//upper bound of potentiometer
int upperBound = 940;
int lowerBound = 0;
int range = upperBound-lowerBound;
//outgoing signal table true means it should be High false means it should be low

// RMS Command Parameters 
int TorqueCommand = 500;
int SpeedCommand = 500;
int Direction = 1;
int InverterEnabled = 1;
int Duration = 0;

// TODO: move to a display file
// Display Parameters
int Speed = 0;
int Battery_Temp = 0;
int Battery_Life = 0;
int Range_KM = 0;
int Range_Mins = 0;

void setup() {
 
  Serial.begin(38400);
  currentState = INIT;

  // Set Pin Modes
  pinMode(PIN_VEHICLE_PWR, INPUT);
  pinMode(PIN_Brake_Light, OUTPUT);
  pinMode(PIN_ECU_OK, OUTPUT);
  pinMode(PIN_PRECHARGE_FINISHED, INPUT);
  pinMode(PIN_READY_TO_GO, OUTPUT);
  pinMode(PIN_SHUTDOWN_TTL_OK, INPUT);
  pinMode(PIN_CAN1_RX, INPUT);
  pinMode(PIN_CAN1_TX, OUTPUT); 
  pinMode(PIN_SDA, OUTPUT);
  pinMode(PIN_SCL, OUTPUT);
  pinMode(PIN_ACCEL_0, INPUT);
  pinMode(PIN_ACCEL_1, INPUT);
  pinMode(PIN_BRAKE_POS, INPUT);
  pinMode(PIN_SOC, INPUT);
  pinMode(PIN_SPEAKER, OUTPUT);
  pinMode(PIN_RESET, INPUT);
 
  // Teensy I2C Slave Code
  Wire.begin(0x40);
  Wire.onRequest(displayRequestEvent);
  Wire.onReceive(displayReceiveEvent);

  // Configure CAN BUS 0 
  Can0.setBaudRate(250000);
  Can0.onReceive(canSniff);
  Can0.begin();
//  Can0.setMaxMB(8);
//  Can0.enableFIFO();
//  Can0.enableFIFOInterrupt();
  
//  Can0.enableMBInterrupts(); // enables all mailboxes to be interrupt enabled
//  Can0.mailboxStatus();

  // RMS CAN RX Mailbox
//   Can0.setMBFilter(MB6, 0x123);
//   Can0.setMB(MB6,RX,STD); // Set mailbox as receiving standard frames.

  // RMS CAN TX Mailbox
//  Can0.setMBFilter(MB9, 0x0C0);
//  Can0.setMB(MB9,TX); // Set mailbox as transmit

 sendInverterEnable();

  // RMS Command Message Heartbeat
 Heartbeat.priority(128);
 Heartbeat.begin(sendRMSHeartbeat, HEARTBEAT); // send message at least every half second

}

void loop() {
  
  /* State Machine Flow
   * Function corresponding to state is called inside conditional. Boolean 
   * value determines if machine needs to switch states.
   */

//  Can0.mailboxStatus();

   Can0.events();


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
      
    default: // TODO: error if we are here
      Serial.println("Error: in unknown state");
      break;
 }
}

void carInit(){
  // Initialization done in setup(), function here for completeness
  digitalWrite(PIN_ECU_OK, LOW);
  
  // TODO: determine if busy waiting is the best strategy
//  while (digitalRead(PRECHARGE_FINISHED) != HIGH);

  currentState = RESET;

//  return true;
}

void carReset(){
  digitalWrite(PIN_ECU_OK, LOW);
  // digitalRead(PIN_PRECHARGE_FINISHED);
  // TODO: Marshal (2/14/22) Reset memory when memory is implemented

  // Passed reset
  currentState = HV_READY_WAIT;

  // If Failed to RESET
  // currentState = ERROR_STATE;

//  return true;
}

void resetConfirm(){
//  return false;
}
  
void error(){
  // TODO: Should turn off Heartbeat and events timers when we are in a fault state
  
  digitalWrite(PIN_ECU_OK, LOW);

//  return false;
}

void routineCheck(){
//  return true;
}

void preHVCheck(){
  // TODO: add checks

//  return true;
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
  currentState = READY_TO_GO_WAIT;

//  return false;
}
  
void readyToGoWait(){
  /* Main Loop Code Here */

//  return false;

}
