#ifndef BEV_ETC_H
#define BEV_ETC_H

extern int ACCEL_MAXPOS;
extern int ACCEL_MINPOS;

extern uint16_t accel_ped_1_pos;
extern uint16_t accel_ped_2_pos;
extern double accel_ped_pos; // This is the resultant value after verifying accel_1 and accel_2
extern double brake_val;
extern double deltaCurrent; // This is max DC current limit - current current
extern double motorSpeed;
extern double max_safe_torque; 
extern double throttleSensitivityCurve[7];
extern int throttleSensitivityCurve_N;
extern double minAccInput;
extern double maxAccInput;
extern double currentDeltaNFCurve[5];
extern int currentDeltaNFCurve_N;
extern double currentDeltaCurve_inputMultiplier; // Needed to get polynomial coefficients to not be too small or big
extern double minDeltaCurrentInput;
extern double maxDeltaCurrentInput;
extern double RPMNegativeFeedbackCurve[5];
extern int RPMCurve_N;
extern double RPMCurve_inputMultiplier; // Needed to get polynomial coefficients to not be too small or big
extern double minRPMInput;
extern double maxRPMInput;
extern bool shouldSimulateETCInputs;

// Function prototypes
void EnableMotor();
void ApplyPedalsAbsolute(int pedal_0);
bool ValidatePedals(int pedal_0, int pedal_1);
bool ValidateCurrentDrawn();
void SimulateETCInputs();
void ProcessInputParameters();
void CapETCInputParameters();
bool ETC();
double EvaluatePolynomial(double poly[], int n, double x);
double EvaluatePolynomial2(double poly[], int n, double x);
double GetMax(double values[], int n);
double CapBetweenZeroToOne(double value);
double CapBetweenRange(double value, double lb, double ub);
inline double Min(double val1, double val2);
inline double Max(double val1, double val2);

#endif // BEV_ETC_H