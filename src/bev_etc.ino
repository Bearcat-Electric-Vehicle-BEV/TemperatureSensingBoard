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
 * @name bev_etc.ino
 *                              
 * @author Alan Aneeth Jegaraj
 * 
 * ETC APIs and general Throttle control functions
 *
 */


#include "bev_etc.h"
#include "bev_can.h"
#include "bev_pins.h"

/**
 * APPS Detection
 * 
 * The pedals are read through the ADC, depending on what our actual input 
 * voltage is this will change. This is also dependent on what ADC resolution
 * is being used. The Teensy 4.1 uses 10-bit ADC resolution, by default, but
 * 12-bit resolution can be enabled. The following is to accomidate these.
 *
 * @todo Once Teensy Board is revisioned, should add checking of 3.3V src ping
 *      for max ADC resolution
 * 
 * @todo Check what ADC bit resolution is being used
 */


#define ACCEL_MAX = 1023

uint16_t accel_ped_1_pos;
uint16_t accel_ped_2_pos;

double accel_ped_pos; // This is the resultant value after verifying accel_1 and accel_2
double brake_val;
double deltaCurrent; // This is max DC current limit - current current
double motorSpeed;

// In Nm. The motor is rated for 102Nm, but due to the uncertainty around battery capacity, we have capped the value to this value.
// This value should be adjusted after physical testing
double max_safe_torque = 80; 

// TODO: magic number 7
//y = -4570.8x6 + 14346x5 - 16327x4 + 7827.7x3 - 1323.3x2 + 127.54x - 0.3364
double throttleSensitivityCurve[7] = {-4942.1, 15757, -18538, 9616.5, -2076.3, 272.37, -9.7821};
int throttleSensitivityCurve_N = 7;
double minAccInput = 0.05;
double maxAccInput = 1;

// TODO: magic number 5
double currentDeltaNFCurve[5] = {-75.524, 75.929, -19.345, -1.9054, 1.0115};
int currentDeltaNFCurve_N = 5;
double currentDeltaCurve_inputMultiplier = 0.01; // Needed to get polynomial coefficients to not be too small or big
double minDeltaCurrentInput = 0;
double maxDeltaCurrentInput = 50;

// TODO: magic number 5
double RPMNegativeFeedbackCurve[5] = {-73.1935, 1508.7335, -11652.4883, 39966.6888, -51366.9768};
int RPMCurve_N = 5;
double RPMCurve_inputMultiplier = 0.001; // Needed to get polynomial coefficients to not be too small or big
double minRPMInput = 5000;
double maxRPMInput = 5500;

// TODO: Should be a macro
bool shouldSimulateETCInputs = true;

/**
 * EnableMotor
 * 
 * @param void
 * 
 * @return void
 * 
 * @brief
 * Clears any faults present on the Motor Controller, then sends enable signal.
 * 
 * @todo delays a second, this appeared necessary in testing, but may be problematic
 * in software. 
 * 
 */
void EnableMotor() {
  SendClearFaults();
  delay(1000); // takes a second to clear faults
  SendInverterEnable();
  InverterEnabled = 1;
}

/**
 * ApplyPedalsAbsolute
 * 
 * @param pedal_0   Pedal 0 ADC reading (Non-Inverted pedal)
 * 
 * @return void
 * 
 * @brief
 * Applies pedal as an absolute reading, meaning no ETC model is applied. 
 * THIS FUNCTION HAS NO RESTRICTIONS ON PEDAL POSITION
 * 
 * @todo Compiler warning, and printout on startup when this is enabled 
 * 
 */
void ApplyPedalsAbsolute(int pedal_0) {

  int flip_thing = 937 - pedal_0;
  
  if (flip_thing > 100) {
	  InverterEnabled = 1;
  } else {
    InverterEnabled = 0;
  }

  double percent_pedal_0 = (double)flip_thing * (100.0 / 937.0);

  int new_torque = (int) (percent_pedal_0 * (3.0/100.0));

  double percent_torque_now = (double)TorqueCommand * (100.0 / 3.0);

  if (abs(percent_torque_now - percent_pedal_0) > 5) {
    TorqueCommand = new_torque;
  }

}

/**
 * ValidatePedals
 * 
 * @param pedal_0   Pedal 0 ADC reading (Non-Inverted Pedal)
 * @param pedal_0   Pedal 1 ADC reading (Inverted Pedal)
 * 
 * @return void
 * 
 * @brief
 * Validates pedal position according to FSAE APPS rules.
 * pedal_0 -> normal & 5v, pedal_1 -> reversed & 3.3v
 * 
 */
bool ValidatePedals(int pedal_0, int pedal_1) {
	// convert pedal_1 to (0 - 610 scale)
	int scaled_pedal_1 = 610 - pedal_1;

	// Convert pedal_0 and pedal_1 to a percentage
	double percent_pedal_0 = (double)pedal_0 * (100.0 / 937.0); 
	double percent_pedal_1 = (double)scaled_pedal_1 * (100.0 / 610.0);

	return abs(percent_pedal_0 - percent_pedal_1) <= 10;
}

/**
 * ValidateCurrentDrawn
 * 
 * @param void
 * 
 * @return True/Within Threshold, False/Overdrawn
 * 
 * @brief
 * Checks if PackCurrent is within Discharge Current Limit
 * 
 * @todo Use PASS/FAIL macros for readability
 * 
 */
bool ValidateCurrentDrawn() {
	return DCL < PackCurrent ? false : true; 
}

/**
 * SimulateETCInputs
 * 
 * @param void
 * 
 * @return void
 * 
 * @brief
 * Test Function
 * 
 */
void SimulateETCInputs() {
//  DCL = 200;
//  PackCurrent = 170;

  // motorSpeed = random(5000,5501);
  // accel_ped_pos = ((double)random(11))/10.0;
  // deltaCurrent = random(51);
  //accel_ped_pos = 0.05;
  deltaCurrent = 100;
}

/**
 * ProcessInputParameters
 * 
 * @param void
 * 
 * @return void
 * 
 * @brief
 * This function is responsible for processing input params for ETC
 * 
 */
void ProcessInputParameters() {
  
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
  accel_ped_pos = Min(1.0 - (accel_ped_1_pos)/931.0, 1.0);
 
  deltaCurrent = DCL - PackCurrent; // DCL and PackCurrent are values received from the BMS via CAN
}

/**
 * CapETCInputParameters
 * 
 * @param void
 * 
 * @return void
 * 
 * @brief
 * TODO
 * 
 */
void CapETCInputParameters() {
  accel_ped_pos = CapBetweenRange(accel_ped_pos, minAccInput, maxAccInput);
  deltaCurrent = CapBetweenRange(deltaCurrent, minDeltaCurrentInput, maxDeltaCurrentInput);
  motorSpeed = CapBetweenRange(motorSpeed, minRPMInput, maxRPMInput);
}

/**
 * ETC
 * 
 * @param void
 * 
 * @return void
 * 
 * @brief
 * TODO
 * 
 */
#if 0
// compiler, bad function, this needs burned
bool ETC() {

  ProcessInputParameters();

  if(shouldSimulateETCInputs) {
    SimulateETCInputs();
  }

  CapETCInputParameters();
  
  // NOTE: Don't go beyond 80 col, not everyone has extremely large monitors
  double torque_from_pedal = CapBetweenRange(EvaluatePolynomial(throttleSensitivityCurve, throttleSensitivityCurve_N, accel_ped_pos), 0, max_safe_torque);

  double currentDelta_NF = CapBetweenZeroToOne(EvaluatePolynomial(currentDeltaNFCurve, currentDeltaNFCurve_N, deltaCurrent * currentDeltaCurve_inputMultiplier));
  double rpm_NF = CapBetweenZeroToOne(EvaluatePolynomial(RPMNegativeFeedbackCurve, RPMCurve_N, ((double)motorSpeed * RPMCurve_inputMultiplier)));

  double nf_weights[] = {currentDelta_NF, rpm_NF};
  double NF_weight = GetMax(nf_weights, 2);

  // This is the global parameter that whose value gets sent to the motor controller via CAN
  double finalTorque = (1.0-NF_weight) * torque_from_pedal;

  if(finalTorque == 0) {
    if(InverterEnabled) {
      SendInverterDisable();
      InverterEnabled = 0;
    }
  }
  else {
    if(InverterEnabled == 0) {
      SendInverterEnable();
      InverterEnabled = 1;
    }
  }
  
  TorqueCommand = (int)finalTorque; // This is the variable whose value gets sent to the MC

  String outputString = "acc 1: " + String(accel_ped_1_pos) + " Final Acc_pos:" + String(accel_ped_pos) + " DeltaCurr:" + String(deltaCurrent) + " RPM:" + String(MotorSpeed) + " only_pedal_torque:" + String(torque_from_pedal) + " deltaCurr_nw:" + String(currentDelta_NF) + " rpm_nw:" + String(rpm_NF) + " final_nw:" + String(NF_weight) + " finalTorque:" + String(finalTorque) + " is inverter enabled: " + String(InverterEnabled);
  Serial.println(outputString);
  
  return true;
}
#endif

/**
 * EvaluatePolynomial
 * 
 * @param poly      double array
 * @param n         len of array
 * @param x         value for x
 * 
 * @return result of polynomial evaluation (double)
 * 
 * @brief
 * Uses Horner's method to evaluate polynomials in O(n)
 * https://www.geeksforgeeks.org/horners-method-polynomial-evaluation/
 * 
 */
double EvaluatePolynomial(double poly[], int n, double x) {
  double result = poly[0];
  for (int i = 1; i < n; i++) {
    result = result * x + poly[i];
  }
  return result;
}

#if 0
// Validates EvaluatePolynomial
double EvaluatePolynomial2(double poly[], int n, double x) {
  double result = poly[n-1];
  double xPow = x;

  for (int i = 1; i < n; i++) {
    result += (poly[n-i-1] * xPow);
    xPow *= x;
  }
  return result;
}
#endif

/**
 * CapBetweenRange
 * 
 * @param value         double, numeric under evaluation
 * @param lb            double, lower bound
 * @param ub            double, higher bound
 * 
 * @return bounded value
 * 
 * @brief
 * Bounds value to lb and ub
 * 
 * @todo This is whole bounding should be done at assignment, instead of 
 * having the user unsure if this is a good value ever. Just ensure this 
 * can never be a bad value.
 * 
 */
double CapBetweenRange(double value, double lb, double ub) {
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

/**
 * CapBetweenZeroToOne
 * 
 * @param value         double, numeric under evaluation
 * 
 * @return bounded value
 * 
 * @brief
 * Bounds value to 0 and 1
 * 
 * @todo Not sure why this is it's own function, doesn't add anything the 
 * function itself is very readable. Just wasting memory
 * 
 */
inline double CapBetweenZeroToOne(double value) {
    return CapBetweenRange(value, 0.0, 1.0);
}

/**
 * GetMax
 * 
 * @param values    double array
 * @param val2      len of array
 * 
 * @return Finds Max
 * 
 */
inline double GetMax(double values[], int n) {
  double largest = values[0];
  for(int i = 1;i < n; i++) {
    if(values[i] > largest) {
      largest = values[i];
    }
  }
  return largest;
}

/**
 * Min
 * 
 * @param val1    double numeric
 * @param val2    double numeric
 * 
 * @return higher value, if same returns val1
 * 
 */
inline double Min(double val1, double val2) {
    return (val1 <= val2) ? val1 : val2;
}

/**
 * Max
 * 
 * @param val1    double numeric
 * @param val2    double numeric
 * 
 * @return lower value, if same returns val1
 * 
 */
inline double Max(double val1, double val2) {
    return (val1 >= val2) ? val1 : val2;
}