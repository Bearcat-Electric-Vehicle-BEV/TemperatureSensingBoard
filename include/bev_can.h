#ifndef BEV_CAN_H
#define BEV_CAN_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <FlexCAN_T4.h>

/*
 * CAN Library Used
 * https://github.com/tonton81/FlexCAN_T4
 */

#define BAUD_RATE 250000
#define HEARTBEAT 500000
#define NUM_RX_MAILBOXES 2
#define NUM_TX_MAILBOXES 2

/*
 * Rinehart Motor Controller Specific Addresses
 * Messages are in 11-bit format, there exists an extended 29-bit
 * and J1939 format. These are located in the data sheet. In order to
 * disable a parameter in the broadcast message, a specifc configuration
 * needs sent in the parameter command message.
 */
#define RMS_ADDR_LOW 0x0A0
#define RMS_TEMPERATURES_1 0x0A0
#define RMS_TEMPERATURES_2 0x0A1
#define RMS_TEMPERATURES_3 0x0A2
#define RMS_ANALOG_INPUT_VOLTAGE 0x0A3
#define RMS_DIGITAL_INPUT_STATUS 0x0A4
#define RMS_MOTOR_POSITION_INFO 0x0A5
#define RMS_CURRENT_INFORMATION 0x0A6
#define RMS_VOLTAGE_INFORMATION 0x0A7
#define RMS_FLUX_INFORMATION 0x0A8
#define RMS_INTERNAL_VOLTAGES 0x0A9
#define RMS_INTERNAL_STATES 0x0AA
#define RMS_FAULT_CODES 0x0AB
#define RMS_TORQUE_AND_TIMER_INFORMATION 0x0AC
#define RMS_MODULATION_INDEX_AND_FLUX_WEAKENING_OUTPUT_INFORMATION 0x0AD
#define RMS_FIRMWARE_INFORMATION 0x0AE
#define RMS_DIAGNOSTIC_DATA 0x0AF
#define RMS_COMMAND_MESSGE_ADDR 0x0C0
#define RMS_PARAMETER_MSG1 0x0C1
#define RMS_PARAMETER_MSG2 0x0C2
#define RMS_ADDR_HIGH 0x0C2

extern uint16_t ModuleATemperature, ModuleBTemperature, ModuleCTemperature, GateDriverBoardTemperature;
extern uint16_t ControlBoardTemperature, RTD1Temperature, RTD2Temperature, RTD3Temperature;
extern uint16_t RTD4Temperature, RTD5Temperature, MotorTemperature, TorqueShudder;
extern uint16_t AnalogInput1, AnalogInput2, AnalogInput3, AnalogInput4;
extern uint8_t DigitalInput1, DigitalInput2, DigitalInput3, DigitalInput4, DigitalInput5, DigitalInput6;
extern uint16_t MotorAngle, MotorSpeed, ElectricalOutputFreq, DeltaResolver;
extern uint16_t PhaseACurrent, PhaseBCurrent, PhaseCCurrent, DCBusCurrent;
extern uint16_t DCBusVoltage, OutputVoltage, PhaseABVoltage, PhaseBCVoltage;
extern uint16_t FluxCommand, FluxFeedback, idFeedback, iqFeedback;
extern uint16_t ReferenceVoltage15, ReferenceVoltage25, ReferenceVoltage50, SystemVoltage12;
extern uint16_t VSMState; extern uint8_t InverterState, RelayState, InverterRunMode, InverterCommandMode, InverterEnableState, InverterEnableLockout, DirectionCommand;
extern uint16_t POSTFaultLo, POSTFaultHi, RunFaultLo, RunFaultHi;
extern uint16_t CommandedTorque, TorqueFeedback; extern uint32_t PowerOnTimer;
extern uint16_t ModulationIndex, FluxWeakeningOutput, IdCommand, IqCommand;
extern uint16_t EEPROMVersion, SoftwareVersion, DataCode_mmdd, DataCode_yyyy;
extern uint16_t gamma_resolver, gamm_observer, sin_corr;
extern uint16_t cos_corr, la_corr, lb_corr;
extern uint16_t lc_corr, vdc, iq_cmd;
extern uint16_t id_cmd, modulation, flux_weak_out;
extern uint16_t vq_cmd, vd_cmd, vqs_cmd;
extern uint16_t voltage12_pwmfreq, run_faults_lo, run_faults_hi;


/*
 * BMS Specific Addresses
 * Messages are in 11-bit format, there exists an extended 29-bit
 * and J1939 format. These are located in the data sheet. In order to
 * disable a parameter in the broadcast message, a specifc configuration
 * needs sent in the parameter command message.
 */

#define BMS_ADDR_LOW 0x6B1
#define BMS_MSG1 0x6B1
#define BMS_FAULTS1 0x6B2
#define BMS_FAULTS2 0x6B3
#define BMS_FAULTS3 0x6B4
#define BMS_ADDR_HIGH 0x6B4

// BMS Parameter Signals 
extern unsigned SOC, DCL, CCL, InternalTemperature, HighestCellVoltage, PackCurrent, AverageTemperature, CheckSum;

// BMS Fault Signals
extern uint32_t bms_faults[3];

extern bool faultPersistant;

extern int TorqueCommand;
extern int SpeedCommand;
extern int Direction;
extern int InverterEnabled;
extern int Duration;

extern FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
extern CAN_message_t cmdMsg;

void dump_fault_codes();
bool checkFaultCodes();
void send_clear_faults();
void sendMessage(unsigned id, unsigned *buffer, unsigned len);
void canSniff(const CAN_message_t &msg);
void printCANMsg(const CAN_message_t &msg);
void sendInverterDisable();
void sendInverterEnable();
void sendRMSHeartbeat();
void can_2_str(const CAN_message_t &msg, char *buffer, size_t len);


#endif // BEV_CAN_H