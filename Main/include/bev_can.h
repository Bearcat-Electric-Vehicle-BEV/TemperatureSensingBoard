#ifndef BEV_CAN_H
#define BEV_CAN_H

#include <FlexCAN_T4.h>

/*
 * CAN Library Used
 * https://github.com/tonton81/FlexCAN_T4
 */

#define BAUD_RATE 1000000
#define NUM_RX_MAILBOXES 2
#define NUM_TX_MAILBOXES 2

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

/*
 * Motor Controller Specific Addresses
 * Messages are in 11-bit format, there exists an extended 29-bit
 * and J1939 format. These are located in the data sheet. In order to
 * disable a parameter in the broadcast message, a specifc configuration
 * needs sent in the parameter command message.
 */
#define TEMPERATURES_1 0x0A0
#define TEMPERATURES_2 0x0A1
#define TEMPERATURES_3 0x0A2
#define ANALOG_INPUT_VOLTAGE 0x0A3
#define DIGITAL_INPUT_STATUS 0x0A4
#define MOTOR_POSITION_INFO 0x0A5
#define CURRENT_INFORMATION 0x0A6
#define VOLTAGE_INFORMATION 0x0A7
#define FLUX_INFORMATION 0x0A8
#define INTERNAL_VOLTAGES 0x0A9
#define INTERNAL_STATES 0x0AA
#define FAULT_CODES 0x0AB
#define TORQUE_AND_TIMER_INFORMATION 0x0AC
#define MODULATION_INDEX_AND_FLUX_WEAKENING_OUTPUT_INFORMATION 0x0AD
#define FIRMWARE_INFORMATION 0x0AE
#define DIAGNOSTIC_DATA 0x0AF

// Rinehart Specifics
#define HEART_BEAT 500000


// Function Prototypes
void canSniff(const CAN_message_t &msg);
void printCANMsg(const CAN_message_t &msg);
bool sendInverterEnable();
void sendRinehartHeartBeat();


#endif // BEV_CAN_H