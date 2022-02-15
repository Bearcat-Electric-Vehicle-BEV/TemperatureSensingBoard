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
 * navigate to the various source files for implementation concerns. 
 *
 */

// #include <Arduino.h>
#include <i2c_driver.h>
#include <i2c_driver_wire.h>
#include "include/bev_i2c.h"
#include "include/bev_state.h"

// TODO: Marshal (2/14/22) Need to have a logging and error handling system, example (status/return codes)

ECUState currentState;

// TODO: Marshal (2/14/22): Lots of globals that are undocumented
// TODO: Marshal (2/14/22) need to be strict on typing to save memory and speed
double val;
double startTime;
double prechargeTime;
bool timerStarted=false;

//upper bound of potentiometer
int upperBound = 940;
int lowerBound = 0;
int range = upperBound-lowerBound;
//outgoing signal table true means it should be High false means it should be low
bool ECUOk;
bool PRECHARGE_FINISHED;
bool READY_TO_GO;

void setup() {
  
  Serial.begin(38400);

  currentState = INIT;
  prechargeTime=2000; // TODO: MAGIC NUMBER

  // Join I2C bus
  Wire.begin();
  
  // TODO: Marshal (2/14/22) Implement watchdog 
  // TODO: Marshal (2/14/22) Implement interrupt table 
}

// TODO: Marshal (2/14/22)
/* create a potentiometer class that can be used for breaks, accel etc. 
 * Optionally an analog input class but that prob not needed
 */


void loop() {
  
  //inside loop determine which function to jump into and if it returns false step to the next state for states that step to another one 

  // https://xiahualiu.github.io/posts/bev-tasks/ 
  switch(currentState){
    case INIT:
      if(carInit())
        currentState=RESET;
      break;

    case RESET:
      if(carReset())
        currentState=HV_READY_WAIT;
      
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
  }
}

bool carInit(){
  ECUOk=false;
  PRECHARGE_FINISHED=true;
  return true;
}

bool carReset(){
  ECUOk=false;
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
  return false;
}

bool preHVCheck(){
  return false;
}

bool HVReadyWait(){
  return false;
}

bool prechargeWait(){
  // Timer for precharge time needed
  if(!timerStarted){
    startTime=millis();}
  else if(timerStarted&&millis()-startTime<=prechargeTime){
    PRECHARGE_FINISHED=true;
    return false;
    }
  else{
    timerStarted=false;
    PRECHARGE_FINISHED=false;
    return true;
    }
  return false;
}
  
bool readyToGoWait(){
  /* Main Loop Code Here */

  val = analogRead(17);
  val = val-lowerBound;
  return false;
  val = val/range;
  val = val*100;
  Serial.println("AccelPedal1 Percentage"+(String)val);
  delay(250);
  return false;
}
