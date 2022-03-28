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

// TODO: make them all caps or not
#define PIN_VEHICLE_PWR 2
#define PIN_CURRENT_OUT 3
#define PIN_WHEEL_MOVE_OUT 4
#define PIN_ECU_OK 9
#define PIN_PRECHARGE_FINISHED 10
#define PIN_READY_TO_GO 11
#define PIN_SHUTDOWN_TTL_OK 12
#define PIN_WHEEL2_SENSE 24
#define PIN_WHEEL3_SENSE 25
#define PIN_CAN_RX 23
#define PIN_CAN_TX 22
#define PIN_WHEEL0_SENSE 21
#define PIN_WHEEL1_SENSE 20
#define PIN_SDA 19
#define PIN_SCL 18
// #define PIN_SDA1 17
// #define PIN_SCL1 16
#define PIN_ACCEL_0 17
#define PIN_ACCEL_1 16
#define PIN_CURRENT_IN 41
#define PIN_BRAKE_POS 40
#define PIN_SPEAKER 37
#define PIN_RESET 36
#define PIN_ECU_FAULT 0
#define PIN_ECU_CHARGER_FAULT 0
#define PIN_PRECHARGE_NOT_FINISHED 0

/* State Machine Diagram https://drive.google.com/file/d/1_kZ9mo7b1bYq2sO-uvetE1C0Gtml-KTl/view?usp=sharing
 * Original documentation on the states can be found at https://xiahualiu.github.io/posts/bev-tasks/
 */
enum ECUState {
   INIT, RESET, RESET_CONFIRM, ERROR_STATE, ROUTINE_CHECK, PRE_HV_CHECK, 
   HV_READY_WAIT, PRECHARGE_WAIT, READY_TO_GO_WAIT};

ECUState currentState;

// TODO: Marshal (2/14/22) Implement watchdog 
// TODO: Marshal (2/14/22) Need to have a logging and error handling system, example (status/return codes)
// TODO: Marshal (2/14/22): Lots of globals that are undocumented
// TODO: Marshal (2/14/22) need to be strict on typing to save memory and speed
double val;
double startTime;
double prechargeTime;
bool timerStarted=false;

// Curve that maps accelerator pedal position to torque
String pedalInputCurve = "120X";

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

// DEBUG FLAG
bool debug = true;

void setup() {
  
  Serial.begin(38400);

  currentState = INIT;
  prechargeTime = 2000; // TODO: MAGIC NUMBER

  // Initialize I2C Bus 
  pinMode(PIN_SDA, OUTPUT);
  pinMode(PIN_SCL, OUTPUT);
  // Code for teensy to act as slave
//  Wire.begin(0x40);
//  Wire.onRequest(displayRequestEvent);
//  Wire.onReceive(displayReceiveEvent);
//  digitalWrite(PIN_SDA, HIGH);

}

void loop() {
  
  /* State Machine Flow
   * Function corresponding to state is called inside conditional. Boolean 
   * value determines if machine needs to switch states.
   */

  // DEBUG LOOP
  if (debug){

    displayRequestEvent();
    delay(1000);

    return;
  }


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

bool ETC() {
  
  // TODO: Initialise these variables outside function
  double accel_val1 = analogRead(PIN_ACCEL_0);
  double accel_val2 = analogRead(PIN_ACCEL_1);
  double accel_val;
  double brake_val = analogRead(PIN_BRAKE_POS);
  
  // Might want to change this since they would be under different voltages
  if (accel_val1 != accel_val2) {
    // Call error function
    return false;
  }

  accel_val = (accel_val1 + accel_val2) / 2.0;
  
  // TODO: Call CAN function to read current Torque value from motor controller  
  double currentTorque = 0;
  
  double targetTorqueValue = getTorqueValueFromCurve(pedalInputCurve, accel_val, currentTorque);

  //Call CAN function to send target Torque value to motor controller

  return true;
  
}

double getTorqueValueFromCurve(String curve, double currentAccelPos, double currentTorque) {
  
  // TODO: Figure out what sort of throttle response do we need, and modelling it with a polynormal curve
  return 120;
  
}
  
bool readyToGoWait(){
  /* Main Loop Code Here */

  if(!ETC()) {
    // Something went wrong, call error function
  }

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
