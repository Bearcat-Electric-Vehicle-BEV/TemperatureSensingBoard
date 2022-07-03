#ifndef BEV_CAN_H
#define BEV_CAN_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <FlexCAN_T4.h>

#include "bev_state.h"
#include "bev_dbc.h"
#include "bev_dbc-binutil.h"

#define BAUD_RATE 250000

// Global CAN Bus and Command Message, and Command Parameters

extern FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

extern bev_dbc_rx_t DBCParser;

/**
 * @brief Struct containing parameters sent in command message
 * 
 */
typedef volatile struct {
    int16_t Torque_Limit_Command;   // BitPos 48 - Len 16
    uint8_t RollingCounter;         // BitPos 44 - Len 4
    uint8_t Speed_Mode_Enabled;     // BitPos 42 - Len 1
    uint8_t Inverter_Discharge;     // BitPos 41 - Len 1
    uint8_t InvertedEnable;         // BitPos 40 - Len 1
    uint8_t Direction_Command;      // BitPos 32 - Len 1
    int16_t Speed_Command;          // BitPos 16 - Len 16
    int16_t Torque_Command;         // BitPos 0  - Len 16
} CmdParameters_t;

/* Function Prototype */

void ServiceCANIdle();
code_t CANInit();
code_t SendMessage(unsigned id, const unsigned *buffer, unsigned len);
void SendInverterDisable();
void SendInverterEnable();
void SendCommandMessage(CmdParameters_t *cmd);
void CanSniff(const CAN_message_t &msg);
void CAN2Str(const CAN_message_t &msg, char *buffer, size_t len);


#endif // BEV_CAN_H