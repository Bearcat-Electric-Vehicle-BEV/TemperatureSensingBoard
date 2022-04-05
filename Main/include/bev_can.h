#ifndef BEV_CAN_H
#define BEV_CAN_H

#include <FlexCAN_T4.h>

/*
 * CAN Library Used
 * https://github.com/tonton81/FlexCAN_T4
 */

#define BAUD_RATE 1000000
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

// TODO: implement signals

/*
 * BMS Specific Addresses
 * Messages are in 11-bit format, there exists an extended 29-bit
 * and J1939 format. These are located in the data sheet. In order to
 * disable a parameter in the broadcast message, a specifc configuration
 * needs sent in the parameter command message.
 */

#define BMS_ADDR_LOW 0x6B1
#define BMS_ADDR_HIGH 0x6B1

// BMS Signals 
int SOC;
int DCL;
int CCL; 
int InternalTemperature;
int HighestCellVoltage;
int PackCurrent;
int AverageTemperature;
int CheckSum;

int* BmsMsg1[8] {
	&SOC, &DCL, &CCL, &InternalTemperature, &HighestCellVoltage, 
	&PackCurrent, &AverageTemperature, &CheckSum
};

int** BmsMsgs[BMS_ADDR_HIGH-BMS_ADDR_LOW] {
	BmsMsg1
};

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
CAN_message_t cmdMsg;

void canSniff(const CAN_message_t &msg);
void printCANMsg(const CAN_message_t &msg);
void sendInverterEnable();
void sendRMSHeartbeat();


#endif // BEV_CAN_H