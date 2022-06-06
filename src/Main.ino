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
 * This is the main file for the BEV TeensyECU. It contains the setup and loop,
 * functions. The intention is for this file to be readable at a high level. 
 * For example a leadership member from another team should be able to read this
 * file and get a good understanding of what is going on. Then be able to 
 * navigate to the various source files for implementation concerns for things 
 * such as I2C or CAN function implementations. 
 *
 */

#include "bev_i2c.h"
#include "bev_can.h"
#include "bev_logger.h"
#include "bev_etc.h"
#include "bev_state.h"
#include "bev_pins.h"


// TODO: replace with RTOS task
IntervalTimer Heartbeat;

void setup() {
 
  Serial.begin(115200); delay(400);
  ChangeState(INIT);

  // Set Pin Modes
  pinMode(PIN_VEHICLE_PWR, INPUT);
  pinMode(PIN_Brake_Light, OUTPUT);
  pinMode(PIN_ECU_OK, OUTPUT);
  pinMode(PIN_PRECHARGE_FINISHED, INPUT);
  pinMode(PIN_READY_TO_GO, OUTPUT);
  pinMode(PIN_SHUTDOWN_TTL_OK, INPUT);
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

  if (!CheckDisplayOnline()) {
    Serial.println("Display not online");
  }

  // Configure CAN BUS 0 
  digitalWrite(PIN_CAN_TRANS_STDBY, LOW); /* tranceiver enable pin */

  CANInit();

  randomSeed(1);

  // PM100Dx Command Message Heartbeat
  // TODO: there is a compiler warning
  // Heartbeat.priority(128);
  // Heartbeat.begin(SendRMSHeartbeat, HEARTBEAT); // send message at least every half second

  EnableMotor(); // TODO: in future may return bool
  SendInverterDisable();
  Log.critical("Unable to enable motor!!!"); 
  ChangeState(ERROR_STATE);

  // Create Tasks

  // Validation

  // Add Tasks

  // Start Scheduler


}

void loop() {
  
  /* State Machine Flow
   * Function corresponding to state is called inside conditional. Boolean 
   * value determines if machine needs to switch states.
   */
  
  Can0.events();
  
  //cringe
  String tempBMSVars = "SOC:" + String(SOC) + " DCL:" + String(DCL) + " InternalTemperature:" + String(InternalTemperature) + " HighestCellVoltage:" + String(HighestCellVoltage) + " PackCurrent:" + String(PackCurrent) + " AverageTemperature:" + String(AverageTemperature) + " CheckSum:" + String(CheckSum);
  Serial.println(tempBMSVars);

  Serial.println(MotorSpeed);

  // if(!ETC()) {
  //   Serial.println("Something went wrong with ETC");
  // }

  if (CheckFaultCodes()) {
      DumpFaultCodes();
      SendClearFaults();
      // TODO: error
  }
  // } else if (faultPersistant){
  //     send_clear_faults();
  //     faultPersistant = false;
  // } else {
  //   // TODO: remove
  // }
  
  // apply_pedals(pedal_0);

  // if (!validate_current_drawn()) {
  //     Log.critical("Current drawn is over current limit!!!");
  //     ChangeState(ERROR_STATE);
  //     return;
  // } 

  delay(100);

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
      ChangeState(ERROR_STATE);
      break;
 }
}

void HVReadyWait(){
  digitalWrite(PIN_ECU_OK, HIGH);
  // digitalWrite(PIN_HV_READY, HIGH);

  ChangeState(PRECHARGE_WAIT);

}

void prechargeWait(){

  if (SOC > 500){
    // TODO: SOC needs ADC mapped
  }

  // if passed precharge wait
  ChangeState(READY_TO_GO_WAIT);
}
  
void readyToGoWait(){
}
