#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "dbccodeconf.h"

#include "bev_dbc.h"

// This version definition comes from main driver version and
// can be compared in user code space for strict compatibility test
#define VER_BEV_DBC_MAJ (0U)
#define VER_BEV_DBC_MIN (0U)

typedef struct
{
  M160_Temperature_Set_1_t M160_Temperature_Set_1;
  M161_Temperature_Set_2_t M161_Temperature_Set_2;
  M162_Temperature_Set_3_t M162_Temperature_Set_3;
  M163_Analog_Input_Voltages_t M163_Analog_Input_Voltages;
  M164_Digital_Input_Status_t M164_Digital_Input_Status;
  M165_Motor_Position_Info_t M165_Motor_Position_Info;
  M166_Current_Info_t M166_Current_Info;
  M167_Voltage_Info_t M167_Voltage_Info;
  M168_Flux_ID_IQ_Info_t M168_Flux_ID_IQ_Info;
  M169_Internal_Voltages_t M169_Internal_Voltages;
  M170_Internal_States_t M170_Internal_States;
  M171_Fault_Codes_t M171_Fault_Codes;
  M172_Torque_And_Timer_Info_t M172_Torque_And_Timer_Info;
  M173_Modulation_And_Flux_Info_t M173_Modulation_And_Flux_Info;
  M174_Firmware_Info_t M174_Firmware_Info;
  M175_Diag_Data_t M175_Diag_Data;
  M176_Fast_Info_t M176_Fast_Info;
  M192_Command_Message_t M192_Command_Message;
  M193_Read_Write_Param_Command_t M193_Read_Write_Param_Command;
  M194_Read_Write_Param_Response_t M194_Read_Write_Param_Response;
  M188_U2C_Message_Rxd_t M188_U2C_Message_Rxd;
  M187_U2C_Command_Txd_t M187_U2C_Command_Txd;
  BMS_Current_Limit_t BMS_Current_Limit;
  BMS_Msg1_t BMS_Msg1;
  BMS_Faults1_t BMS_Faults1;
} bev_dbc_rx_t;

// There is no any TX mapped massage.

uint32_t bev_dbc_Receive(bev_dbc_rx_t* m, const uint8_t* d, uint32_t msgid, uint8_t dlc);

#ifdef __DEF_BEV_DBC__

extern bev_dbc_rx_t bev_dbc_rx;

#endif // __DEF_BEV_DBC__

#ifdef __cplusplus
}
#endif
