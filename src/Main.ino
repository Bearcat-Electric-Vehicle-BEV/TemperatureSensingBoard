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

#include "bev_i2c.h"
#include "bev_can.h"
#include "bev_logger.h"
#include "bev_etc.h"

#include "Watchdog_t4.h"

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

double val;
double startTime;
double prechargeTime;
bool timerStarted=false;

// ETC related global var
int ACCEL_MAXPOS = 1023;
int ACCEL_MINPOS = 0;

int accel_ped_1_pos;
int accel_ped_2_pos;
double accel_ped_pos; // This is the resultant value after verifying accel_1 and accel_2
double brake_val;
double deltaCurrent; // This is max DC current limit - current current
double motorSpeed;

// In Nm. The motor is rated for 102Nm, but due to the uncertainty around battery capacity, we have capped the value to this value.
// This value should be adjusted after physical testing
double max_safe_torque = 80; 

//y = -4570.8x6 + 14346x5 - 16327x4 + 7827.7x3 - 1323.3x2 + 127.54x - 0.3364
double throttleSensitivityCurve[] = {-4942.1, 15757, -18538, 9616.5, -2076.3, 272.37, -9.7821};
int throttleSensitivityCurve_N = 7;
double minAccInput = 0.05;
double maxAccInput = 1;

double currentDeltaNFCurve[] = {-75.524, 75.929, -19.345, -1.9054, 1.0115};
int currentDeltaNFCurve_N = 5;
double currentDeltaCurve_inputMultiplier = 0.01; // Needed to get polynomial coefficients to not be too small or big
double minDeltaCurrentInput = 0;
double maxDeltaCurrentInput = 50;

double RPMNegativeFeedbackCurve[] = {-73.1935, 1508.7335, -11652.4883, 39966.6888, -51366.9768};
int RPMCurve_N = 5;
double RPMCurve_inputMultiplier = 0.001; // Needed to get polynomial coefficients to not be too small or big
double minRPMInput = 5000;
double maxRPMInput = 5500;

bool shouldSimulateETCInputs = true;

ECUState currentState;

IntervalTimer Heartbeat;
// IntervalTimer UpdateDisplay;

// https://github.com/tonton81/WDT_T4
// WDT_T4<WDT1> wdt;



void change_state(ECUState newState) {
    currentState = newState;
    char buffer[100];
    snprintf(buffer, 100, "ENTERED %s state", STATE_STRING[newState]);
    Log.info(buffer);
}

void watchdogCallback() {
  Log.critical("Watchdog timer not reset!!! Resetting ECU!!!");
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
    Serial.println("Display not online");
  }

  // Configure CAN BUS 0 
  digitalWrite(PIN_CAN_TRANS_STDBY, LOW); /* tranceiver enable pin */
  
  Can0.begin();
  Can0.setBaudRate(250000);
  Can0.setMaxMB(16);
  Can0.enableFIFO();
  Can0.enableFIFOInterrupt();
  Can0.onReceive(canSniff);
  // Can0.mailboxStatus();
  
  // Can0.enableMBInterrupts(); // enables all mailboxes to be interrupt enabled
  // Can0.mailboxStatus();

  // RMS CAN RX Mailbox
//   Can0.setMBFilter(MB6, 0x123);
//   Can0.setMB(MB6,RX,STD); // Set mailbox as receiving standard frames.

  // RMS CAN TX Mailbox
//  Can0.setMBFilter(MB9, 0x0C0);
//  Can0.setMB(MB9,TX); // Set mailbox as transmit

 // sendInverterEnable();

  // PM100Dx Command Message Heartbeat
  // Heartbeat.priority(128);
  // Heartbeat.begin(sendRMSHeartbeat, HEARTBEAT); // send message at least every half second

  // Initialize the watchdog timer
  WDT_timings_t config;
  config.trigger = 5; /* in seconds, 0->128 */
  config.timeout = 10; /* in seconds, 0->128 */
  config.callback = watchdogCallback;
//  wdt.begin(config);

  randomSeed(1);
  // Can0.setMBFilter(REJECT_ALL);
  
  // Can0.setMB(MB0, RX, STD);  // 0x0A2 Temperature #3
  // Can0.setMB(MB1, RX, STD);  // 0x0A5 Motor Position Information
  // Can0.setMB(MB2, RX, STD);  // 0x0AB Fault Codes
  // Can0.setMB(MB3, RX, STD);  // 0x0AC Torque and Timer Information
  // Can0.setMB(MB4, RX, STD);  // 0x0AF Diagnostic Data
  
  // Can0.setMB(MB5, TX);  // 0x0C0 Command Message
  // Can0.setMB(MB6, TX);  // 0x0C8 Parameter Message 
  // Can0.setMB(MB7, TX);
  // Can0.setMB(MB8, TX);
  // Can0.setMB(MB9, TX);
  // Can0.setMB(MB10, TX);
  // Can0.setMB(MB11, TX);
  // Can0.setMB(MB12, TX);
  // Can0.setMB(MB13, TX);
  // Can0.setMB(MB14, TX);
  // Can0.setMB(MB15, TX);

  // TODO: create message specific callbacks
  // Can0.onReceive(MB0, canSniff);
  // Can0.onReceive(MB1, canSniff);
  // Can0.onReceive(MB2, canSniff);
  // Can0.onReceive(MB3, canSniff);
  // Can0.onReceive(MB4, canSniff);

  // RX
  Can0.setMBFilter(MB0, RMS_TEMPERATURES_3);
  Can0.setMBFilter(MB1, RMS_MOTOR_POSITION_INFO);
  Can0.setMBFilter(MB2, RMS_FAULT_CODES);
  Can0.setMBFilter(MB3, RMS_TORQUE_AND_TIMER_INFORMATION);
  Can0.setMBFilter(MB4, RMS_DIAGNOSTIC_DATA);

  // TX
  // Can0.setMBUserFilter(MB5, RMS_COMMAND_MESSGE_ADDR, 0xFF);
  // Can0.setMBUserFilter(MB6, RMS_PARAMETER_MSG1, 0xFF);
  
  // Can0.enableMBInterrupts(MB0);
  // Can0.enableMBInterrupts(MB1);
  // Can0.enableMBInterrupts(MB2);
  // Can0.enableMBInterrupts(MB3);
  // Can0.enableMBInterrupts(MB4);
  // Can0.enableMBInterrupts(MB5);
  // Can0.enableMBInterrupts(MB6);

  Can0.mailboxStatus();

  // PM100Dx Command Message Heartbeat
  Heartbeat.priority(128);
  Heartbeat.begin(sendRMSHeartbeat, HEARTBEAT); // send message at least every half second
  // UpdateDisplay.priority(127);
  // UpdateDisplay.begin(update_display, 1000000);

  // Initialize the watchdog timer
  // WDT_timings_t config;
  // config.trigger = 5; /* in seconds, 0->128 */
  // config.timeout = 10; /* in seconds, 0->128 */
  // config.callback = watchdogCallback;
  // wdt.begin(config);

  if (!enable_motor()) {
      sendInverterDisable();
      Log.critical("Unable to enable motor!!!"); 
      change_state(ERROR_STATE);
  }

}

void loop() {
  
  /* State Machine Flow
   * Function corresponding to state is called inside conditional. Boolean 
   * value determines if machine needs to switch states.
   */
  
  // Watchdog reset
  // wdt.feed();

  Can0.events();
  
  String tempBMSVars = "SOC:" + String(SOC) + " DCL:" + String(DCL) + " InternalTemperature:" + String(InternalTemperature) + " HighestCellVoltage:" + String(HighestCellVoltage) + " PackCurrent:" + String(PackCurrent) + " AverageTemperature:" + String(AverageTemperature) + " CheckSum:" + String(CheckSum);
  Serial.println(tempBMSVars);

  Serial.println(MotorSpeed);

  if(!ETC()) {
    Serial.println("Something went wrong with ETC");
  }

  if (checkFaultCodes()) {
      dump_fault_codes();
      send_clear_faults();
      // TODO: error
  }
  // } else if (faultPersistant){
  //     send_clear_faults();
  //     faultPersistant = false;
  // } else {
  //   // TODO: remove
  // }
  
  // apply_pedals(pedal_0);

  // Can0.disableMBInterrupts();
  //update_display();
  // Can0.enableMBInterrupts();

  // if (!validate_current_drawn()) {
  //     Log.critical("Current drawn is over current limit!!!");
  //     change_state(ERROR_STATE);
  //     return;
  // } 

  delay(100); // we go too fast

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
  change_state(RESET);
}

void carReset(){
  // TODO (Marsh May 2022): what memory needs reset?

  digitalWrite(PIN_ECU_OK, LOW);
  
  if (digitalRead(PIN_PRECHARGE_FINISHED) == HIGH) {
      change_state(PRE_HV_CHECK);
  } 
  else {
    // If Failed to RESET
    change_state(ERROR_STATE);
  }

}

void resetConfirm(){
  // TODO (marsh May 2022): is this state necessary?

}
  
void error(){

    Log.critical("Entered ERROR STATE!!!");
    digitalWrite(PIN_ECU_OK, LOW);

    // Inverter enable sends a 0 torque command to stop motor
    sendInverterEnable(); // todo: make a disable command
    Heartbeat.end();

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

void HVReadyWait(){
  digitalWrite(PIN_ECU_OK, HIGH);
  // digitalWrite(PIN_HV_READY, HIGH);

  change_state(PRECHARGE_WAIT);

}

void prechargeWait(){

  if (SOC > 500){
    // TODO: SOC needs ADC mapped
  }

  // if passed precharge wait
  change_state(READY_TO_GO_WAIT);
}

// function for testing ETC, by setting specific input values
void simulateETCInputs() {
//  DCL = 200;
//  PackCurrent = 170;

  // motorSpeed = random(5000,5501);
  // accel_ped_pos = ((double)random(11))/10.0;
  // deltaCurrent = random(51);
  //accel_ped_pos = 0.05;
  deltaCurrent = 100;
}

// This function is responsible for processing input params for ETC
void processInputParameters() {
  
  accel_ped_1_pos = analogRead(PIN_ACCEL_0);
  accel_ped_2_pos = analogRead(PIN_ACCEL_1);
  brake_val = analogRead(PIN_BRAKE_POS);
  motorSpeed = MotorSpeed;

  // if (!validate_pedals(accel_ped_1_pos, accel_ped_2_pos)) {
  //     sendInverterDisable();
  //     Log.critical("Pedal positions not within 10%!!!!"); 
  //     // change_state(ERROR_STATE);
  //     return;
  // }
  
  // temp, should do additional processing
  // It should be investigates as to why the pedal values only go from 924 and 808
  accel_ped_pos = min(1.0 - (accel_ped_1_pos)/931.0, 1.0);
 
  deltaCurrent = DCL - PackCurrent; // DCL and PackCurrent are values received from the BMS via CAN
}

void capETCInputParameters() {
  accel_ped_pos = capBetweenRange(accel_ped_pos, minAccInput, maxAccInput);
  deltaCurrent = capBetweenRange(deltaCurrent, minDeltaCurrentInput, maxDeltaCurrentInput);
  motorSpeed = capBetweenRange(motorSpeed, minRPMInput, maxRPMInput);
}

bool ETC() {
  processInputParameters();
  if(shouldSimulateETCInputs) {
    simulateETCInputs();
  }
  capETCInputParameters();
  
  double torque_from_pedal = capBetweenRange(evaluatePolynomial(throttleSensitivityCurve, throttleSensitivityCurve_N, accel_ped_pos), 0, max_safe_torque);

  double currentDelta_NF = capBetweenZeroToOne(evaluatePolynomial(currentDeltaNFCurve, currentDeltaNFCurve_N, deltaCurrent * currentDeltaCurve_inputMultiplier));
  double rpm_NF = capBetweenZeroToOne(evaluatePolynomial(RPMNegativeFeedbackCurve, RPMCurve_N, (double)motorSpeed * RPMCurve_inputMultiplier));

  double nf_weights[] = {currentDelta_NF, rpm_NF};
  double NF_weight = getMax(nf_weights, 2);

  // This is the global parameter that whose value gets sent to the motor controller via CAN
  double finalTorque = (1.0-NF_weight) * torque_from_pedal;

  if(finalTorque == 0) {
    if(InverterEnabled) {
      sendInverterDisable();
      InverterEnabled = 0;
    }
  }
  else {
    if(InverterEnabled == 0) {
      sendInverterEnable();
      InverterEnabled = 1;
    }
  }
  
  TorqueCommand = (int)finalTorque; // This is the variable whose value gets sent to the MC

  String outputString = "acc 1: " + String(accel_ped_1_pos) + " Final Acc_pos:" + String(accel_ped_pos) + " DeltaCurr:" + String(deltaCurrent) + " RPM:" + String(MotorSpeed) + " only_pedal_torque:" + String(torque_from_pedal) + " deltaCurr_nw:" + String(currentDelta_NF) + " rpm_nw:" + String(rpm_NF) + " final_nw:" + String(NF_weight) + " finalTorque:" + String(finalTorque) + " is inverter enabled: " + String(InverterEnabled);
  Serial.println(outputString);
  
  return true;
}

// Uses Horner's method to evaluate polynomials in O(n)
// https://www.geeksforgeeks.org/horners-method-polynomial-evaluation/
double evaluatePolynomial(double poly[], int n, double x) {
  double result = poly[0];
  for (int i = 1; i < n; i++) {
    result = result * x + poly[i];
  }
  return result;
}

// Function created for sanity check/debug purposes. The above function is more efficient
double evaluatePolynomial2(double poly[], int n, double x) {
  double result = poly[n-1];
  double xPow = x;

  for (int i = 1; i < n; i++) {
    result += (poly[n-i-1] * xPow);
    xPow *= x;
  }
  return result;
}


double getMax(double values[], int n) {
  double largest = values[0];
  for(int i = 1;i < n; i++) {
    if(values[i] > largest) {
      largest = values[i];
    }
  }
  return largest;
}

double capBetweenZeroToOne(double value) {
    return capBetweenRange(value, 0.0, 1.0);
}

double capBetweenRange(double value, double lb, double ub) {
  if(value > ub) {
    return ub;  
  }
  else if (value < lb) {
    return lb;
  }
  else {
    return value;
  }
}

double min(double val1, double val2) {
  if(val1 <= val2) {return val1;}
  else {return val2;}
}

double max(double val1, double val2) {
  if(val1 >= val2) {return val1;}
  else {return val2;}
}
  
void readyToGoWait(){
}
