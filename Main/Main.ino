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
IntervalTimer CAN_EVENTS_Timer;

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

// TODO: Determine if we should store these values 
bool ECU_OK;
bool PRECHARGE_FINISHED;
bool READY_TO_GO;
bool HV_READY;

// adslk;fjsal;kfj
int TorqueCommand = 0;
int SpeedCommand = 0;
int Direction = 0;
int InverterEnabled = 0;
int Duration = 0;


void setup() {
 
  Serial.begin(38400);

  currentState = INIT;
  prechargeTime = 2000; // TODO: MAGIC NUMBER

  // Teensy I2C Master 
  pinMode(PIN_SDA, OUTPUT);
  pinMode(PIN_SCL, OUTPUT);
  
  // Teensy I2C Slave Code
  //  Wire.begin(0x40);
  //  Wire.onRequest(displayRequestEvent);
  //  Wire.onReceive(displayReceiveEvent);

  // CAN RX/TX
  pinMode(PIN_CAN1_RX, INPUT);
  pinMode(PIN_CAN1_TX, OUTPUT); 

  // Configure CAN BUS 0 
  Can0.begin();
  Can0.setBaudRate(BAUD_RATE);
  Can0.setMaxMB(NUM_RX_MAILBOXES);
  Can0.enableFIFO();
  Can0.enableFIFOInterrupt();
  Can0.onReceive(canSniff);
  Can0.mailboxStatus();

  // RMS CAN RX Mailbox
  // Can0.setMBFilter(MB6, 0x123);
  // Can0.setMB(MB6,RX,STD); // Set mailbox as receiving standard frames.

  // RMS CAN TX Mailbox
  Can0.setMBFilter(MB9, 0x0C0);
  Can0.setMB(MB9,TX); // Set mailbox as transmit

  // RMS Command Message Heartbeat
  Heartbeat.priority(128);
  Heartbeat.begin(sendRMSHeartbeat, HEARTBEAT); // send message at least every half second

  // RMS trigger events periodically
  // CAN_EVENTS_Timer.priority(129);
  // CAN_EVENTS_Timer.begin(Can0.events, (HEARTBEAT / 2));

}

void loop() {
  
  /* State Machine Flow
   * Function corresponding to state is called inside conditional. Boolean 
   * value determines if machine needs to switch states.
   */

  Can0.events();


  delay(1000);

  return;


  switch(currentState){
    case INIT:
      if(carInit())
        currentState=RESET;
      break;

    case RESET:
      if(carReset())
        currentState=HV_READY_WAIT;
      else // Failed to RESET
        currentState=ERROR_STATE;
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
      if (prechargeWait())
        currentState = READY_TO_GO_WAIT;
      break;
     
    case READY_TO_GO_WAIT:
      if (readyToGoWait())
        break;
      break;
      
    default: // TODO: error if we are here
      break;
 }
}

bool carInit(){
  // Initialization done in setup(), function here for completeness
  ECU_OK=false;
  PRECHARGE_FINISHED=true;
  return true;
}

bool carReset(){
  ECU_OK=false;
  PRECHARGE_FINISHED=true;
  // TODO: Marshal (2/14/22) Reset memory when memory is implemented
  return true;
}

bool resetConfirm(){
  return false;
}
  
bool error(){
  // TODO: Should turn off Heartbeat and events timers when we are in a fault state
  return false;
}

bool routineCheck(){
  return true;
}

bool preHVCheck(){
  // TODO: add checks

  return true;
}

bool HVReadyWait(){
  ECU_OK = true;
  HV_READY = true;
  return true;
}

bool prechargeWait(){
  // Timer for precharge time needed
  // TODO: NOT CORRECT IMPLEMENTATION 
  if (!timerStarted) {
    startTime=millis();
  }
  else if (timerStarted && ((millis() - startTime) <= prechargeTime)) {
    PRECHARGE_FINISHED=true;
    return true;
  } 
  else {
    timerStarted=false;
    PRECHARGE_FINISHED=false;
    currentState = ERROR_STATE;
  }
  return false;
}
  
bool readyToGoWait(){
  /* Main Loop Code Here */

  val = analogRead(17); // TODO: magic number
  val = val-lowerBound;
  return false;

  // TODO: remove debug code
  val = val/range;
  val = val*100;
  Serial.println("AccelPedal1 Percentage"+(String)val);
  delay(250);
  return false;
}
