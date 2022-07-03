#include "bev_dbc.h"


#ifdef BEV_DBC_USE_DIAG_MONITORS
// Function prototypes to be called each time CAN frame is unpacked
// FMon function may detect RC, CRC or DLC violation
#include "bev_dbc-fmon.h"

#endif // BEV_DBC_USE_DIAG_MONITORS


uint32_t Unpack_M160_Temperature_Set_1_bev_dbc(M160_Temperature_Set_1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Module_A_ro = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Module_A_phys = (sigfloat_t)(BEV_DBC_D1_Module_A_ro_fromS(_m->D1_Module_A_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D2_Module_B_ro = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D2_Module_B_phys = (sigfloat_t)(BEV_DBC_D2_Module_B_ro_fromS(_m->D2_Module_B_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D3_Module_C_ro = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D3_Module_C_phys = (sigfloat_t)(BEV_DBC_D3_Module_C_ro_fromS(_m->D3_Module_C_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D4_Gate_Driver_Board_ro = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D4_Gate_Driver_Board_phys = (sigfloat_t)(BEV_DBC_D4_Gate_Driver_Board_ro_fromS(_m->D4_Gate_Driver_Board_ro));
#endif // BEV_DBC_USE_SIGFLOAT

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M160_Temperature_Set_1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M160_Temperature_Set_1_bev_dbc(&_m->mon1, M160_Temperature_Set_1_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M160_Temperature_Set_1_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M160_Temperature_Set_1_bev_dbc(M160_Temperature_Set_1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M160_Temperature_Set_1_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Module_A_ro = BEV_DBC_D1_Module_A_ro_toS(_m->D1_Module_A_phys);
  _m->D2_Module_B_ro = BEV_DBC_D2_Module_B_ro_toS(_m->D2_Module_B_phys);
  _m->D3_Module_C_ro = BEV_DBC_D3_Module_C_ro_toS(_m->D3_Module_C_phys);
  _m->D4_Gate_Driver_Board_ro = BEV_DBC_D4_Gate_Driver_Board_ro_toS(_m->D4_Gate_Driver_Board_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (_m->D1_Module_A_ro & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Module_A_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_Module_B_ro & (0xFFU));
  cframe->Data[3] |= ((_m->D2_Module_B_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->D3_Module_C_ro & (0xFFU));
  cframe->Data[5] |= ((_m->D3_Module_C_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->D4_Gate_Driver_Board_ro & (0xFFU));
  cframe->Data[7] |= ((_m->D4_Gate_Driver_Board_ro >> 8) & (0xFFU));

  cframe->MsgId = M160_Temperature_Set_1_CANID;
  cframe->DLC = M160_Temperature_Set_1_DLC;
  cframe->IDE = M160_Temperature_Set_1_IDE;
  return M160_Temperature_Set_1_CANID;
}

#else

uint32_t Pack_M160_Temperature_Set_1_bev_dbc(M160_Temperature_Set_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M160_Temperature_Set_1_DLC) && (i < 8); _d[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Module_A_ro = BEV_DBC_D1_Module_A_ro_toS(_m->D1_Module_A_phys);
  _m->D2_Module_B_ro = BEV_DBC_D2_Module_B_ro_toS(_m->D2_Module_B_phys);
  _m->D3_Module_C_ro = BEV_DBC_D3_Module_C_ro_toS(_m->D3_Module_C_phys);
  _m->D4_Gate_Driver_Board_ro = BEV_DBC_D4_Gate_Driver_Board_ro_toS(_m->D4_Gate_Driver_Board_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  _d[0] |= (_m->D1_Module_A_ro & (0xFFU));
  _d[1] |= ((_m->D1_Module_A_ro >> 8) & (0xFFU));
  _d[2] |= (_m->D2_Module_B_ro & (0xFFU));
  _d[3] |= ((_m->D2_Module_B_ro >> 8) & (0xFFU));
  _d[4] |= (_m->D3_Module_C_ro & (0xFFU));
  _d[5] |= ((_m->D3_Module_C_ro >> 8) & (0xFFU));
  _d[6] |= (_m->D4_Gate_Driver_Board_ro & (0xFFU));
  _d[7] |= ((_m->D4_Gate_Driver_Board_ro >> 8) & (0xFFU));

  *_len = M160_Temperature_Set_1_DLC;
  *_ide = M160_Temperature_Set_1_IDE;
  return M160_Temperature_Set_1_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M161_Temperature_Set_2_bev_dbc(M161_Temperature_Set_2_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Control_Board_Temperature_ro = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Control_Board_Temperature_phys = (sigfloat_t)(BEV_DBC_D1_Control_Board_Temperature_ro_fromS(_m->D1_Control_Board_Temperature_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D2_RTD1_Temperature_ro = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D2_RTD1_Temperature_phys = (sigfloat_t)(BEV_DBC_D2_RTD1_Temperature_ro_fromS(_m->D2_RTD1_Temperature_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D3_RTD2_Temperature_ro = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D3_RTD2_Temperature_phys = (sigfloat_t)(BEV_DBC_D3_RTD2_Temperature_ro_fromS(_m->D3_RTD2_Temperature_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D4_RTD3_Temperature_ro = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D4_RTD3_Temperature_phys = (sigfloat_t)(BEV_DBC_D4_RTD3_Temperature_ro_fromS(_m->D4_RTD3_Temperature_ro));
#endif // BEV_DBC_USE_SIGFLOAT

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M161_Temperature_Set_2_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M161_Temperature_Set_2_bev_dbc(&_m->mon1, M161_Temperature_Set_2_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M161_Temperature_Set_2_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M161_Temperature_Set_2_bev_dbc(M161_Temperature_Set_2_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M161_Temperature_Set_2_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Control_Board_Temperature_ro = BEV_DBC_D1_Control_Board_Temperature_ro_toS(_m->D1_Control_Board_Temperature_phys);
  _m->D2_RTD1_Temperature_ro = BEV_DBC_D2_RTD1_Temperature_ro_toS(_m->D2_RTD1_Temperature_phys);
  _m->D3_RTD2_Temperature_ro = BEV_DBC_D3_RTD2_Temperature_ro_toS(_m->D3_RTD2_Temperature_phys);
  _m->D4_RTD3_Temperature_ro = BEV_DBC_D4_RTD3_Temperature_ro_toS(_m->D4_RTD3_Temperature_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (_m->D1_Control_Board_Temperature_ro & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Control_Board_Temperature_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_RTD1_Temperature_ro & (0xFFU));
  cframe->Data[3] |= ((_m->D2_RTD1_Temperature_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->D3_RTD2_Temperature_ro & (0xFFU));
  cframe->Data[5] |= ((_m->D3_RTD2_Temperature_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->D4_RTD3_Temperature_ro & (0xFFU));
  cframe->Data[7] |= ((_m->D4_RTD3_Temperature_ro >> 8) & (0xFFU));

  cframe->MsgId = M161_Temperature_Set_2_CANID;
  cframe->DLC = M161_Temperature_Set_2_DLC;
  cframe->IDE = M161_Temperature_Set_2_IDE;
  return M161_Temperature_Set_2_CANID;
}

#else

uint32_t Pack_M161_Temperature_Set_2_bev_dbc(M161_Temperature_Set_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M161_Temperature_Set_2_DLC) && (i < 8); _d[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Control_Board_Temperature_ro = BEV_DBC_D1_Control_Board_Temperature_ro_toS(_m->D1_Control_Board_Temperature_phys);
  _m->D2_RTD1_Temperature_ro = BEV_DBC_D2_RTD1_Temperature_ro_toS(_m->D2_RTD1_Temperature_phys);
  _m->D3_RTD2_Temperature_ro = BEV_DBC_D3_RTD2_Temperature_ro_toS(_m->D3_RTD2_Temperature_phys);
  _m->D4_RTD3_Temperature_ro = BEV_DBC_D4_RTD3_Temperature_ro_toS(_m->D4_RTD3_Temperature_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  _d[0] |= (_m->D1_Control_Board_Temperature_ro & (0xFFU));
  _d[1] |= ((_m->D1_Control_Board_Temperature_ro >> 8) & (0xFFU));
  _d[2] |= (_m->D2_RTD1_Temperature_ro & (0xFFU));
  _d[3] |= ((_m->D2_RTD1_Temperature_ro >> 8) & (0xFFU));
  _d[4] |= (_m->D3_RTD2_Temperature_ro & (0xFFU));
  _d[5] |= ((_m->D3_RTD2_Temperature_ro >> 8) & (0xFFU));
  _d[6] |= (_m->D4_RTD3_Temperature_ro & (0xFFU));
  _d[7] |= ((_m->D4_RTD3_Temperature_ro >> 8) & (0xFFU));

  *_len = M161_Temperature_Set_2_DLC;
  *_ide = M161_Temperature_Set_2_IDE;
  return M161_Temperature_Set_2_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M162_Temperature_Set_3_bev_dbc(M162_Temperature_Set_3_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_RTD4_Temperature_ro = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_RTD4_Temperature_phys = (sigfloat_t)(BEV_DBC_D1_RTD4_Temperature_ro_fromS(_m->D1_RTD4_Temperature_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D2_RTD5_Temperature_ro = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D2_RTD5_Temperature_phys = (sigfloat_t)(BEV_DBC_D2_RTD5_Temperature_ro_fromS(_m->D2_RTD5_Temperature_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D3_Motor_Temperature_ro = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D3_Motor_Temperature_phys = (sigfloat_t)(BEV_DBC_D3_Motor_Temperature_ro_fromS(_m->D3_Motor_Temperature_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D4_Torque_Shudder_ro = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D4_Torque_Shudder_phys = (sigfloat_t)(BEV_DBC_D4_Torque_Shudder_ro_fromS(_m->D4_Torque_Shudder_ro));
#endif // BEV_DBC_USE_SIGFLOAT

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M162_Temperature_Set_3_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M162_Temperature_Set_3_bev_dbc(&_m->mon1, M162_Temperature_Set_3_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M162_Temperature_Set_3_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M162_Temperature_Set_3_bev_dbc(M162_Temperature_Set_3_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M162_Temperature_Set_3_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_RTD4_Temperature_ro = BEV_DBC_D1_RTD4_Temperature_ro_toS(_m->D1_RTD4_Temperature_phys);
  _m->D2_RTD5_Temperature_ro = BEV_DBC_D2_RTD5_Temperature_ro_toS(_m->D2_RTD5_Temperature_phys);
  _m->D3_Motor_Temperature_ro = BEV_DBC_D3_Motor_Temperature_ro_toS(_m->D3_Motor_Temperature_phys);
  _m->D4_Torque_Shudder_ro = BEV_DBC_D4_Torque_Shudder_ro_toS(_m->D4_Torque_Shudder_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (_m->D1_RTD4_Temperature_ro & (0xFFU));
  cframe->Data[1] |= ((_m->D1_RTD4_Temperature_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_RTD5_Temperature_ro & (0xFFU));
  cframe->Data[3] |= ((_m->D2_RTD5_Temperature_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->D3_Motor_Temperature_ro & (0xFFU));
  cframe->Data[5] |= ((_m->D3_Motor_Temperature_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->D4_Torque_Shudder_ro & (0xFFU));
  cframe->Data[7] |= ((_m->D4_Torque_Shudder_ro >> 8) & (0xFFU));

  cframe->MsgId = M162_Temperature_Set_3_CANID;
  cframe->DLC = M162_Temperature_Set_3_DLC;
  cframe->IDE = M162_Temperature_Set_3_IDE;
  return M162_Temperature_Set_3_CANID;
}

#else

uint32_t Pack_M162_Temperature_Set_3_bev_dbc(M162_Temperature_Set_3_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M162_Temperature_Set_3_DLC) && (i < 8); _d[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_RTD4_Temperature_ro = BEV_DBC_D1_RTD4_Temperature_ro_toS(_m->D1_RTD4_Temperature_phys);
  _m->D2_RTD5_Temperature_ro = BEV_DBC_D2_RTD5_Temperature_ro_toS(_m->D2_RTD5_Temperature_phys);
  _m->D3_Motor_Temperature_ro = BEV_DBC_D3_Motor_Temperature_ro_toS(_m->D3_Motor_Temperature_phys);
  _m->D4_Torque_Shudder_ro = BEV_DBC_D4_Torque_Shudder_ro_toS(_m->D4_Torque_Shudder_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  _d[0] |= (_m->D1_RTD4_Temperature_ro & (0xFFU));
  _d[1] |= ((_m->D1_RTD4_Temperature_ro >> 8) & (0xFFU));
  _d[2] |= (_m->D2_RTD5_Temperature_ro & (0xFFU));
  _d[3] |= ((_m->D2_RTD5_Temperature_ro >> 8) & (0xFFU));
  _d[4] |= (_m->D3_Motor_Temperature_ro & (0xFFU));
  _d[5] |= ((_m->D3_Motor_Temperature_ro >> 8) & (0xFFU));
  _d[6] |= (_m->D4_Torque_Shudder_ro & (0xFFU));
  _d[7] |= ((_m->D4_Torque_Shudder_ro >> 8) & (0xFFU));

  *_len = M162_Temperature_Set_3_DLC;
  *_ide = M162_Temperature_Set_3_IDE;
  return M162_Temperature_Set_3_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M163_Analog_Input_Voltages_bev_dbc(M163_Analog_Input_Voltages_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Analog_Input_1_ro = ((_d[1] & (0x03U)) << 8) | (_d[0] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Analog_Input_1_phys = (sigfloat_t)(BEV_DBC_D1_Analog_Input_1_ro_fromS(_m->D1_Analog_Input_1_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D2_Analog_Input_2_ro = ((_d[2] & (0x0FU)) << 6) | ((_d[1] >> 2) & (0x3FU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D2_Analog_Input_2_phys = (sigfloat_t)(BEV_DBC_D2_Analog_Input_2_ro_fromS(_m->D2_Analog_Input_2_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D3_Analog_Input_3_ro = ((_d[3] & (0x3FU)) << 4) | ((_d[2] >> 4) & (0x0FU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D3_Analog_Input_3_phys = (sigfloat_t)(BEV_DBC_D3_Analog_Input_3_ro_fromS(_m->D3_Analog_Input_3_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D4_Analog_Input_4_ro = ((_d[5] & (0x03U)) << 8) | (_d[4] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D4_Analog_Input_4_phys = (sigfloat_t)(BEV_DBC_D4_Analog_Input_4_ro_fromS(_m->D4_Analog_Input_4_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D5_Analog_Input_5_ro = ((_d[6] & (0x0FU)) << 6) | ((_d[5] >> 2) & (0x3FU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D5_Analog_Input_5_phys = (sigfloat_t)(BEV_DBC_D5_Analog_Input_5_ro_fromS(_m->D5_Analog_Input_5_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D6_Analog_Input_6_ro = ((_d[7] & (0x3FU)) << 4) | ((_d[6] >> 4) & (0x0FU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D6_Analog_Input_6_phys = (sigfloat_t)(BEV_DBC_D6_Analog_Input_6_ro_fromS(_m->D6_Analog_Input_6_ro));
#endif // BEV_DBC_USE_SIGFLOAT

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M163_Analog_Input_Voltages_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M163_Analog_Input_Voltages_bev_dbc(&_m->mon1, M163_Analog_Input_Voltages_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M163_Analog_Input_Voltages_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M163_Analog_Input_Voltages_bev_dbc(M163_Analog_Input_Voltages_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M163_Analog_Input_Voltages_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Analog_Input_1_ro = BEV_DBC_D1_Analog_Input_1_ro_toS(_m->D1_Analog_Input_1_phys);
  _m->D2_Analog_Input_2_ro = BEV_DBC_D2_Analog_Input_2_ro_toS(_m->D2_Analog_Input_2_phys);
  _m->D3_Analog_Input_3_ro = BEV_DBC_D3_Analog_Input_3_ro_toS(_m->D3_Analog_Input_3_phys);
  _m->D4_Analog_Input_4_ro = BEV_DBC_D4_Analog_Input_4_ro_toS(_m->D4_Analog_Input_4_phys);
  _m->D5_Analog_Input_5_ro = BEV_DBC_D5_Analog_Input_5_ro_toS(_m->D5_Analog_Input_5_phys);
  _m->D6_Analog_Input_6_ro = BEV_DBC_D6_Analog_Input_6_ro_toS(_m->D6_Analog_Input_6_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (_m->D1_Analog_Input_1_ro & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Analog_Input_1_ro >> 8) & (0x03U)) | ((_m->D2_Analog_Input_2_ro & (0x3FU)) << 2);
  cframe->Data[2] |= ((_m->D2_Analog_Input_2_ro >> 6) & (0x0FU)) | ((_m->D3_Analog_Input_3_ro & (0x0FU)) << 4);
  cframe->Data[3] |= ((_m->D3_Analog_Input_3_ro >> 4) & (0x3FU));
  cframe->Data[4] |= (_m->D4_Analog_Input_4_ro & (0xFFU));
  cframe->Data[5] |= ((_m->D4_Analog_Input_4_ro >> 8) & (0x03U)) | ((_m->D5_Analog_Input_5_ro & (0x3FU)) << 2);
  cframe->Data[6] |= ((_m->D5_Analog_Input_5_ro >> 6) & (0x0FU)) | ((_m->D6_Analog_Input_6_ro & (0x0FU)) << 4);
  cframe->Data[7] |= ((_m->D6_Analog_Input_6_ro >> 4) & (0x3FU));

  cframe->MsgId = M163_Analog_Input_Voltages_CANID;
  cframe->DLC = M163_Analog_Input_Voltages_DLC;
  cframe->IDE = M163_Analog_Input_Voltages_IDE;
  return M163_Analog_Input_Voltages_CANID;
}

#else

uint32_t Pack_M163_Analog_Input_Voltages_bev_dbc(M163_Analog_Input_Voltages_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M163_Analog_Input_Voltages_DLC) && (i < 8); _d[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Analog_Input_1_ro = BEV_DBC_D1_Analog_Input_1_ro_toS(_m->D1_Analog_Input_1_phys);
  _m->D2_Analog_Input_2_ro = BEV_DBC_D2_Analog_Input_2_ro_toS(_m->D2_Analog_Input_2_phys);
  _m->D3_Analog_Input_3_ro = BEV_DBC_D3_Analog_Input_3_ro_toS(_m->D3_Analog_Input_3_phys);
  _m->D4_Analog_Input_4_ro = BEV_DBC_D4_Analog_Input_4_ro_toS(_m->D4_Analog_Input_4_phys);
  _m->D5_Analog_Input_5_ro = BEV_DBC_D5_Analog_Input_5_ro_toS(_m->D5_Analog_Input_5_phys);
  _m->D6_Analog_Input_6_ro = BEV_DBC_D6_Analog_Input_6_ro_toS(_m->D6_Analog_Input_6_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  _d[0] |= (_m->D1_Analog_Input_1_ro & (0xFFU));
  _d[1] |= ((_m->D1_Analog_Input_1_ro >> 8) & (0x03U)) | ((_m->D2_Analog_Input_2_ro & (0x3FU)) << 2);
  _d[2] |= ((_m->D2_Analog_Input_2_ro >> 6) & (0x0FU)) | ((_m->D3_Analog_Input_3_ro & (0x0FU)) << 4);
  _d[3] |= ((_m->D3_Analog_Input_3_ro >> 4) & (0x3FU));
  _d[4] |= (_m->D4_Analog_Input_4_ro & (0xFFU));
  _d[5] |= ((_m->D4_Analog_Input_4_ro >> 8) & (0x03U)) | ((_m->D5_Analog_Input_5_ro & (0x3FU)) << 2);
  _d[6] |= ((_m->D5_Analog_Input_5_ro >> 6) & (0x0FU)) | ((_m->D6_Analog_Input_6_ro & (0x0FU)) << 4);
  _d[7] |= ((_m->D6_Analog_Input_6_ro >> 4) & (0x3FU));

  *_len = M163_Analog_Input_Voltages_DLC;
  *_ide = M163_Analog_Input_Voltages_IDE;
  return M163_Analog_Input_Voltages_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M164_Digital_Input_Status_bev_dbc(M164_Digital_Input_Status_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Digital_Input_1 = (_d[0] & (0x01U));
  _m->D2_Digital_Input_2 = (_d[1] & (0x01U));
  _m->D3_Digital_Input_3 = (_d[2] & (0x01U));
  _m->D4_Digital_Input_4 = (_d[3] & (0x01U));
  _m->D5_Digital_Input_5 = (_d[4] & (0x01U));
  _m->D6_Digital_Input_6 = (_d[5] & (0x01U));
  _m->D7_Digital_Input_7 = (_d[6] & (0x01U));
  _m->D8_Digital_Input_8 = (_d[7] & (0x01U));

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M164_Digital_Input_Status_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M164_Digital_Input_Status_bev_dbc(&_m->mon1, M164_Digital_Input_Status_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M164_Digital_Input_Status_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M164_Digital_Input_Status_bev_dbc(M164_Digital_Input_Status_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M164_Digital_Input_Status_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->D1_Digital_Input_1 & (0x01U));
  cframe->Data[1] |= (_m->D2_Digital_Input_2 & (0x01U));
  cframe->Data[2] |= (_m->D3_Digital_Input_3 & (0x01U));
  cframe->Data[3] |= (_m->D4_Digital_Input_4 & (0x01U));
  cframe->Data[4] |= (_m->D5_Digital_Input_5 & (0x01U));
  cframe->Data[5] |= (_m->D6_Digital_Input_6 & (0x01U));
  cframe->Data[6] |= (_m->D7_Digital_Input_7 & (0x01U));
  cframe->Data[7] |= (_m->D8_Digital_Input_8 & (0x01U));

  cframe->MsgId = M164_Digital_Input_Status_CANID;
  cframe->DLC = M164_Digital_Input_Status_DLC;
  cframe->IDE = M164_Digital_Input_Status_IDE;
  return M164_Digital_Input_Status_CANID;
}

#else

uint32_t Pack_M164_Digital_Input_Status_bev_dbc(M164_Digital_Input_Status_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M164_Digital_Input_Status_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->D1_Digital_Input_1 & (0x01U));
  _d[1] |= (_m->D2_Digital_Input_2 & (0x01U));
  _d[2] |= (_m->D3_Digital_Input_3 & (0x01U));
  _d[3] |= (_m->D4_Digital_Input_4 & (0x01U));
  _d[4] |= (_m->D5_Digital_Input_5 & (0x01U));
  _d[5] |= (_m->D6_Digital_Input_6 & (0x01U));
  _d[6] |= (_m->D7_Digital_Input_7 & (0x01U));
  _d[7] |= (_m->D8_Digital_Input_8 & (0x01U));

  *_len = M164_Digital_Input_Status_DLC;
  *_ide = M164_Digital_Input_Status_IDE;
  return M164_Digital_Input_Status_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M165_Motor_Position_Info_bev_dbc(M165_Motor_Position_Info_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Motor_Angle_Electrical_ro = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Motor_Angle_Electrical_phys = (sigfloat_t)(BEV_DBC_D1_Motor_Angle_Electrical_ro_fromS(_m->D1_Motor_Angle_Electrical_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D2_Motor_Speed = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->D3_Electrical_Output_Frequency_ro = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D3_Electrical_Output_Frequency_phys = (sigfloat_t)(BEV_DBC_D3_Electrical_Output_Frequency_ro_fromS(_m->D3_Electrical_Output_Frequency_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D4_Delta_Resolver_Filtered_ro = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D4_Delta_Resolver_Filtered_phys = (sigfloat_t)(BEV_DBC_D4_Delta_Resolver_Filtered_ro_fromS(_m->D4_Delta_Resolver_Filtered_ro));
#endif // BEV_DBC_USE_SIGFLOAT

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M165_Motor_Position_Info_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M165_Motor_Position_Info_bev_dbc(&_m->mon1, M165_Motor_Position_Info_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M165_Motor_Position_Info_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M165_Motor_Position_Info_bev_dbc(M165_Motor_Position_Info_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M165_Motor_Position_Info_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Motor_Angle_Electrical_ro = BEV_DBC_D1_Motor_Angle_Electrical_ro_toS(_m->D1_Motor_Angle_Electrical_phys);
  _m->D3_Electrical_Output_Frequency_ro = BEV_DBC_D3_Electrical_Output_Frequency_ro_toS(_m->D3_Electrical_Output_Frequency_phys);
  _m->D4_Delta_Resolver_Filtered_ro = BEV_DBC_D4_Delta_Resolver_Filtered_ro_toS(_m->D4_Delta_Resolver_Filtered_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (_m->D1_Motor_Angle_Electrical_ro & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Motor_Angle_Electrical_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_Motor_Speed & (0xFFU));
  cframe->Data[3] |= ((_m->D2_Motor_Speed >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->D3_Electrical_Output_Frequency_ro & (0xFFU));
  cframe->Data[5] |= ((_m->D3_Electrical_Output_Frequency_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->D4_Delta_Resolver_Filtered_ro & (0xFFU));
  cframe->Data[7] |= ((_m->D4_Delta_Resolver_Filtered_ro >> 8) & (0xFFU));

  cframe->MsgId = M165_Motor_Position_Info_CANID;
  cframe->DLC = M165_Motor_Position_Info_DLC;
  cframe->IDE = M165_Motor_Position_Info_IDE;
  return M165_Motor_Position_Info_CANID;
}

#else

uint32_t Pack_M165_Motor_Position_Info_bev_dbc(M165_Motor_Position_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M165_Motor_Position_Info_DLC) && (i < 8); _d[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Motor_Angle_Electrical_ro = BEV_DBC_D1_Motor_Angle_Electrical_ro_toS(_m->D1_Motor_Angle_Electrical_phys);
  _m->D3_Electrical_Output_Frequency_ro = BEV_DBC_D3_Electrical_Output_Frequency_ro_toS(_m->D3_Electrical_Output_Frequency_phys);
  _m->D4_Delta_Resolver_Filtered_ro = BEV_DBC_D4_Delta_Resolver_Filtered_ro_toS(_m->D4_Delta_Resolver_Filtered_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  _d[0] |= (_m->D1_Motor_Angle_Electrical_ro & (0xFFU));
  _d[1] |= ((_m->D1_Motor_Angle_Electrical_ro >> 8) & (0xFFU));
  _d[2] |= (_m->D2_Motor_Speed & (0xFFU));
  _d[3] |= ((_m->D2_Motor_Speed >> 8) & (0xFFU));
  _d[4] |= (_m->D3_Electrical_Output_Frequency_ro & (0xFFU));
  _d[5] |= ((_m->D3_Electrical_Output_Frequency_ro >> 8) & (0xFFU));
  _d[6] |= (_m->D4_Delta_Resolver_Filtered_ro & (0xFFU));
  _d[7] |= ((_m->D4_Delta_Resolver_Filtered_ro >> 8) & (0xFFU));

  *_len = M165_Motor_Position_Info_DLC;
  *_ide = M165_Motor_Position_Info_IDE;
  return M165_Motor_Position_Info_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M166_Current_Info_bev_dbc(M166_Current_Info_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Phase_A_Current_ro = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Phase_A_Current_phys = (sigfloat_t)(BEV_DBC_D1_Phase_A_Current_ro_fromS(_m->D1_Phase_A_Current_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D2_Phase_B_Current_ro = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D2_Phase_B_Current_phys = (sigfloat_t)(BEV_DBC_D2_Phase_B_Current_ro_fromS(_m->D2_Phase_B_Current_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D3_Phase_C_Current_ro = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D3_Phase_C_Current_phys = (sigfloat_t)(BEV_DBC_D3_Phase_C_Current_ro_fromS(_m->D3_Phase_C_Current_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D4_DC_Bus_Current_ro = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D4_DC_Bus_Current_phys = (sigfloat_t)(BEV_DBC_D4_DC_Bus_Current_ro_fromS(_m->D4_DC_Bus_Current_ro));
#endif // BEV_DBC_USE_SIGFLOAT

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M166_Current_Info_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M166_Current_Info_bev_dbc(&_m->mon1, M166_Current_Info_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M166_Current_Info_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M166_Current_Info_bev_dbc(M166_Current_Info_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M166_Current_Info_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Phase_A_Current_ro = BEV_DBC_D1_Phase_A_Current_ro_toS(_m->D1_Phase_A_Current_phys);
  _m->D2_Phase_B_Current_ro = BEV_DBC_D2_Phase_B_Current_ro_toS(_m->D2_Phase_B_Current_phys);
  _m->D3_Phase_C_Current_ro = BEV_DBC_D3_Phase_C_Current_ro_toS(_m->D3_Phase_C_Current_phys);
  _m->D4_DC_Bus_Current_ro = BEV_DBC_D4_DC_Bus_Current_ro_toS(_m->D4_DC_Bus_Current_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (_m->D1_Phase_A_Current_ro & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Phase_A_Current_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_Phase_B_Current_ro & (0xFFU));
  cframe->Data[3] |= ((_m->D2_Phase_B_Current_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->D3_Phase_C_Current_ro & (0xFFU));
  cframe->Data[5] |= ((_m->D3_Phase_C_Current_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->D4_DC_Bus_Current_ro & (0xFFU));
  cframe->Data[7] |= ((_m->D4_DC_Bus_Current_ro >> 8) & (0xFFU));

  cframe->MsgId = M166_Current_Info_CANID;
  cframe->DLC = M166_Current_Info_DLC;
  cframe->IDE = M166_Current_Info_IDE;
  return M166_Current_Info_CANID;
}

#else

uint32_t Pack_M166_Current_Info_bev_dbc(M166_Current_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M166_Current_Info_DLC) && (i < 8); _d[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Phase_A_Current_ro = BEV_DBC_D1_Phase_A_Current_ro_toS(_m->D1_Phase_A_Current_phys);
  _m->D2_Phase_B_Current_ro = BEV_DBC_D2_Phase_B_Current_ro_toS(_m->D2_Phase_B_Current_phys);
  _m->D3_Phase_C_Current_ro = BEV_DBC_D3_Phase_C_Current_ro_toS(_m->D3_Phase_C_Current_phys);
  _m->D4_DC_Bus_Current_ro = BEV_DBC_D4_DC_Bus_Current_ro_toS(_m->D4_DC_Bus_Current_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  _d[0] |= (_m->D1_Phase_A_Current_ro & (0xFFU));
  _d[1] |= ((_m->D1_Phase_A_Current_ro >> 8) & (0xFFU));
  _d[2] |= (_m->D2_Phase_B_Current_ro & (0xFFU));
  _d[3] |= ((_m->D2_Phase_B_Current_ro >> 8) & (0xFFU));
  _d[4] |= (_m->D3_Phase_C_Current_ro & (0xFFU));
  _d[5] |= ((_m->D3_Phase_C_Current_ro >> 8) & (0xFFU));
  _d[6] |= (_m->D4_DC_Bus_Current_ro & (0xFFU));
  _d[7] |= ((_m->D4_DC_Bus_Current_ro >> 8) & (0xFFU));

  *_len = M166_Current_Info_DLC;
  *_ide = M166_Current_Info_IDE;
  return M166_Current_Info_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M167_Voltage_Info_bev_dbc(M167_Voltage_Info_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_DC_Bus_Voltage_ro = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_DC_Bus_Voltage_phys = (sigfloat_t)(BEV_DBC_D1_DC_Bus_Voltage_ro_fromS(_m->D1_DC_Bus_Voltage_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D2_Output_Voltage_ro = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D2_Output_Voltage_phys = (sigfloat_t)(BEV_DBC_D2_Output_Voltage_ro_fromS(_m->D2_Output_Voltage_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D3_VAB_Vd_Voltage_ro = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D3_VAB_Vd_Voltage_phys = (sigfloat_t)(BEV_DBC_D3_VAB_Vd_Voltage_ro_fromS(_m->D3_VAB_Vd_Voltage_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D4_VBC_Vq_Voltage_ro = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D4_VBC_Vq_Voltage_phys = (sigfloat_t)(BEV_DBC_D4_VBC_Vq_Voltage_ro_fromS(_m->D4_VBC_Vq_Voltage_ro));
#endif // BEV_DBC_USE_SIGFLOAT

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M167_Voltage_Info_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M167_Voltage_Info_bev_dbc(&_m->mon1, M167_Voltage_Info_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M167_Voltage_Info_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M167_Voltage_Info_bev_dbc(M167_Voltage_Info_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M167_Voltage_Info_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_DC_Bus_Voltage_ro = BEV_DBC_D1_DC_Bus_Voltage_ro_toS(_m->D1_DC_Bus_Voltage_phys);
  _m->D2_Output_Voltage_ro = BEV_DBC_D2_Output_Voltage_ro_toS(_m->D2_Output_Voltage_phys);
  _m->D3_VAB_Vd_Voltage_ro = BEV_DBC_D3_VAB_Vd_Voltage_ro_toS(_m->D3_VAB_Vd_Voltage_phys);
  _m->D4_VBC_Vq_Voltage_ro = BEV_DBC_D4_VBC_Vq_Voltage_ro_toS(_m->D4_VBC_Vq_Voltage_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (_m->D1_DC_Bus_Voltage_ro & (0xFFU));
  cframe->Data[1] |= ((_m->D1_DC_Bus_Voltage_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_Output_Voltage_ro & (0xFFU));
  cframe->Data[3] |= ((_m->D2_Output_Voltage_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->D3_VAB_Vd_Voltage_ro & (0xFFU));
  cframe->Data[5] |= ((_m->D3_VAB_Vd_Voltage_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->D4_VBC_Vq_Voltage_ro & (0xFFU));
  cframe->Data[7] |= ((_m->D4_VBC_Vq_Voltage_ro >> 8) & (0xFFU));

  cframe->MsgId = M167_Voltage_Info_CANID;
  cframe->DLC = M167_Voltage_Info_DLC;
  cframe->IDE = M167_Voltage_Info_IDE;
  return M167_Voltage_Info_CANID;
}

#else

uint32_t Pack_M167_Voltage_Info_bev_dbc(M167_Voltage_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M167_Voltage_Info_DLC) && (i < 8); _d[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_DC_Bus_Voltage_ro = BEV_DBC_D1_DC_Bus_Voltage_ro_toS(_m->D1_DC_Bus_Voltage_phys);
  _m->D2_Output_Voltage_ro = BEV_DBC_D2_Output_Voltage_ro_toS(_m->D2_Output_Voltage_phys);
  _m->D3_VAB_Vd_Voltage_ro = BEV_DBC_D3_VAB_Vd_Voltage_ro_toS(_m->D3_VAB_Vd_Voltage_phys);
  _m->D4_VBC_Vq_Voltage_ro = BEV_DBC_D4_VBC_Vq_Voltage_ro_toS(_m->D4_VBC_Vq_Voltage_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  _d[0] |= (_m->D1_DC_Bus_Voltage_ro & (0xFFU));
  _d[1] |= ((_m->D1_DC_Bus_Voltage_ro >> 8) & (0xFFU));
  _d[2] |= (_m->D2_Output_Voltage_ro & (0xFFU));
  _d[3] |= ((_m->D2_Output_Voltage_ro >> 8) & (0xFFU));
  _d[4] |= (_m->D3_VAB_Vd_Voltage_ro & (0xFFU));
  _d[5] |= ((_m->D3_VAB_Vd_Voltage_ro >> 8) & (0xFFU));
  _d[6] |= (_m->D4_VBC_Vq_Voltage_ro & (0xFFU));
  _d[7] |= ((_m->D4_VBC_Vq_Voltage_ro >> 8) & (0xFFU));

  *_len = M167_Voltage_Info_DLC;
  *_ide = M167_Voltage_Info_IDE;
  return M167_Voltage_Info_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M168_Flux_ID_IQ_Info_bev_dbc(M168_Flux_ID_IQ_Info_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Flux_Command_ro = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Flux_Command_phys = (sigfloat_t)(BEV_DBC_D1_Flux_Command_ro_fromS(_m->D1_Flux_Command_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D2_Flux_Feedback_ro = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D2_Flux_Feedback_phys = (sigfloat_t)(BEV_DBC_D2_Flux_Feedback_ro_fromS(_m->D2_Flux_Feedback_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D3_Id_ro = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D3_Id_phys = (sigfloat_t)(BEV_DBC_D3_Id_ro_fromS(_m->D3_Id_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D4_Iq_ro = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D4_Iq_phys = (sigfloat_t)(BEV_DBC_D4_Iq_ro_fromS(_m->D4_Iq_ro));
#endif // BEV_DBC_USE_SIGFLOAT

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M168_Flux_ID_IQ_Info_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M168_Flux_ID_IQ_Info_bev_dbc(&_m->mon1, M168_Flux_ID_IQ_Info_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M168_Flux_ID_IQ_Info_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M168_Flux_ID_IQ_Info_bev_dbc(M168_Flux_ID_IQ_Info_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M168_Flux_ID_IQ_Info_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Flux_Command_ro = BEV_DBC_D1_Flux_Command_ro_toS(_m->D1_Flux_Command_phys);
  _m->D2_Flux_Feedback_ro = BEV_DBC_D2_Flux_Feedback_ro_toS(_m->D2_Flux_Feedback_phys);
  _m->D3_Id_ro = BEV_DBC_D3_Id_ro_toS(_m->D3_Id_phys);
  _m->D4_Iq_ro = BEV_DBC_D4_Iq_ro_toS(_m->D4_Iq_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (_m->D1_Flux_Command_ro & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Flux_Command_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_Flux_Feedback_ro & (0xFFU));
  cframe->Data[3] |= ((_m->D2_Flux_Feedback_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->D3_Id_ro & (0xFFU));
  cframe->Data[5] |= ((_m->D3_Id_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->D4_Iq_ro & (0xFFU));
  cframe->Data[7] |= ((_m->D4_Iq_ro >> 8) & (0xFFU));

  cframe->MsgId = M168_Flux_ID_IQ_Info_CANID;
  cframe->DLC = M168_Flux_ID_IQ_Info_DLC;
  cframe->IDE = M168_Flux_ID_IQ_Info_IDE;
  return M168_Flux_ID_IQ_Info_CANID;
}

#else

uint32_t Pack_M168_Flux_ID_IQ_Info_bev_dbc(M168_Flux_ID_IQ_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M168_Flux_ID_IQ_Info_DLC) && (i < 8); _d[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Flux_Command_ro = BEV_DBC_D1_Flux_Command_ro_toS(_m->D1_Flux_Command_phys);
  _m->D2_Flux_Feedback_ro = BEV_DBC_D2_Flux_Feedback_ro_toS(_m->D2_Flux_Feedback_phys);
  _m->D3_Id_ro = BEV_DBC_D3_Id_ro_toS(_m->D3_Id_phys);
  _m->D4_Iq_ro = BEV_DBC_D4_Iq_ro_toS(_m->D4_Iq_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  _d[0] |= (_m->D1_Flux_Command_ro & (0xFFU));
  _d[1] |= ((_m->D1_Flux_Command_ro >> 8) & (0xFFU));
  _d[2] |= (_m->D2_Flux_Feedback_ro & (0xFFU));
  _d[3] |= ((_m->D2_Flux_Feedback_ro >> 8) & (0xFFU));
  _d[4] |= (_m->D3_Id_ro & (0xFFU));
  _d[5] |= ((_m->D3_Id_ro >> 8) & (0xFFU));
  _d[6] |= (_m->D4_Iq_ro & (0xFFU));
  _d[7] |= ((_m->D4_Iq_ro >> 8) & (0xFFU));

  *_len = M168_Flux_ID_IQ_Info_DLC;
  *_ide = M168_Flux_ID_IQ_Info_IDE;
  return M168_Flux_ID_IQ_Info_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M169_Internal_Voltages_bev_dbc(M169_Internal_Voltages_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Reference_Voltage_1_5_ro = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Reference_Voltage_1_5_phys = (sigfloat_t)(BEV_DBC_D1_Reference_Voltage_1_5_ro_fromS(_m->D1_Reference_Voltage_1_5_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D2_Reference_Voltage_2_5_ro = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D2_Reference_Voltage_2_5_phys = (sigfloat_t)(BEV_DBC_D2_Reference_Voltage_2_5_ro_fromS(_m->D2_Reference_Voltage_2_5_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D3_Reference_Voltage_5_0_ro = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D3_Reference_Voltage_5_0_phys = (sigfloat_t)(BEV_DBC_D3_Reference_Voltage_5_0_ro_fromS(_m->D3_Reference_Voltage_5_0_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D4_Reference_Voltage_12_0_ro = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D4_Reference_Voltage_12_0_phys = (sigfloat_t)(BEV_DBC_D4_Reference_Voltage_12_0_ro_fromS(_m->D4_Reference_Voltage_12_0_ro));
#endif // BEV_DBC_USE_SIGFLOAT

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M169_Internal_Voltages_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M169_Internal_Voltages_bev_dbc(&_m->mon1, M169_Internal_Voltages_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M169_Internal_Voltages_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M169_Internal_Voltages_bev_dbc(M169_Internal_Voltages_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M169_Internal_Voltages_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Reference_Voltage_1_5_ro = BEV_DBC_D1_Reference_Voltage_1_5_ro_toS(_m->D1_Reference_Voltage_1_5_phys);
  _m->D2_Reference_Voltage_2_5_ro = BEV_DBC_D2_Reference_Voltage_2_5_ro_toS(_m->D2_Reference_Voltage_2_5_phys);
  _m->D3_Reference_Voltage_5_0_ro = BEV_DBC_D3_Reference_Voltage_5_0_ro_toS(_m->D3_Reference_Voltage_5_0_phys);
  _m->D4_Reference_Voltage_12_0_ro = BEV_DBC_D4_Reference_Voltage_12_0_ro_toS(_m->D4_Reference_Voltage_12_0_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (_m->D1_Reference_Voltage_1_5_ro & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Reference_Voltage_1_5_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_Reference_Voltage_2_5_ro & (0xFFU));
  cframe->Data[3] |= ((_m->D2_Reference_Voltage_2_5_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->D3_Reference_Voltage_5_0_ro & (0xFFU));
  cframe->Data[5] |= ((_m->D3_Reference_Voltage_5_0_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->D4_Reference_Voltage_12_0_ro & (0xFFU));
  cframe->Data[7] |= ((_m->D4_Reference_Voltage_12_0_ro >> 8) & (0xFFU));

  cframe->MsgId = M169_Internal_Voltages_CANID;
  cframe->DLC = M169_Internal_Voltages_DLC;
  cframe->IDE = M169_Internal_Voltages_IDE;
  return M169_Internal_Voltages_CANID;
}

#else

uint32_t Pack_M169_Internal_Voltages_bev_dbc(M169_Internal_Voltages_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M169_Internal_Voltages_DLC) && (i < 8); _d[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Reference_Voltage_1_5_ro = BEV_DBC_D1_Reference_Voltage_1_5_ro_toS(_m->D1_Reference_Voltage_1_5_phys);
  _m->D2_Reference_Voltage_2_5_ro = BEV_DBC_D2_Reference_Voltage_2_5_ro_toS(_m->D2_Reference_Voltage_2_5_phys);
  _m->D3_Reference_Voltage_5_0_ro = BEV_DBC_D3_Reference_Voltage_5_0_ro_toS(_m->D3_Reference_Voltage_5_0_phys);
  _m->D4_Reference_Voltage_12_0_ro = BEV_DBC_D4_Reference_Voltage_12_0_ro_toS(_m->D4_Reference_Voltage_12_0_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  _d[0] |= (_m->D1_Reference_Voltage_1_5_ro & (0xFFU));
  _d[1] |= ((_m->D1_Reference_Voltage_1_5_ro >> 8) & (0xFFU));
  _d[2] |= (_m->D2_Reference_Voltage_2_5_ro & (0xFFU));
  _d[3] |= ((_m->D2_Reference_Voltage_2_5_ro >> 8) & (0xFFU));
  _d[4] |= (_m->D3_Reference_Voltage_5_0_ro & (0xFFU));
  _d[5] |= ((_m->D3_Reference_Voltage_5_0_ro >> 8) & (0xFFU));
  _d[6] |= (_m->D4_Reference_Voltage_12_0_ro & (0xFFU));
  _d[7] |= ((_m->D4_Reference_Voltage_12_0_ro >> 8) & (0xFFU));

  *_len = M169_Internal_Voltages_DLC;
  *_ide = M169_Internal_Voltages_IDE;
  return M169_Internal_Voltages_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M170_Internal_States_bev_dbc(M170_Internal_States_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_VSM_State = (_d[0] & (0xFFU));
  _m->D1_PWM_Frequency = (_d[1] & (0xFFU));
  _m->D2_Inverter_State = (_d[2] & (0xFFU));
  _m->D3_Relay_1_Status = (_d[3] & (0x01U));
  _m->D3_Relay_2_Status = ((_d[3] >> 1) & (0x01U));
  _m->D3_Relay_3_Status = ((_d[3] >> 2) & (0x01U));
  _m->D3_Relay_4_Status = ((_d[3] >> 3) & (0x01U));
  _m->D3_Relay_5_Status = ((_d[3] >> 4) & (0x01U));
  _m->D3_Relay_6_Status = ((_d[3] >> 5) & (0x01U));
  _m->D4_Inverter_Run_Mode = (_d[4] & (0x01U));
  _m->D4_Inverter_Discharge_State = ((_d[4] >> 5) & (0x07U));
  _m->D5_Inverter_Command_Mode = (_d[5] & (0x01U));
  _m->D5_Rolling_Counter = ((_d[5] >> 4) & (0x0FU));
  _m->D6_Inverter_Enable_State = (_d[6] & (0x01U));
  _m->D6_Start_Mode_Active = ((_d[6] >> 6) & (0x01U));
  _m->D6_Inverter_Enable_Lockout = ((_d[6] >> 7) & (0x01U));
  _m->D7_Direction_Command = (_d[7] & (0x01U));
  _m->D7_BMS_Active = ((_d[7] >> 1) & (0x01U));
  _m->D7_BMS_Torque_Limiting = ((_d[7] >> 2) & (0x01U));
  _m->D7_Max_Speed_Limiting = ((_d[7] >> 3) & (0x01U));
  _m->D7_Low_Speed_Limiting = ((_d[7] >> 5) & (0x01U));

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M170_Internal_States_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M170_Internal_States_bev_dbc(&_m->mon1, M170_Internal_States_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M170_Internal_States_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M170_Internal_States_bev_dbc(M170_Internal_States_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M170_Internal_States_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->D1_VSM_State & (0xFFU));
  cframe->Data[1] |= (_m->D1_PWM_Frequency & (0xFFU));
  cframe->Data[2] |= (_m->D2_Inverter_State & (0xFFU));
  cframe->Data[3] |= (_m->D3_Relay_1_Status & (0x01U)) | ((_m->D3_Relay_2_Status & (0x01U)) << 1) | ((_m->D3_Relay_3_Status & (0x01U)) << 2) | ((_m->D3_Relay_4_Status & (0x01U)) << 3) | ((_m->D3_Relay_5_Status & (0x01U)) << 4) | ((_m->D3_Relay_6_Status & (0x01U)) << 5);
  cframe->Data[4] |= (_m->D4_Inverter_Run_Mode & (0x01U)) | ((_m->D4_Inverter_Discharge_State & (0x07U)) << 5);
  cframe->Data[5] |= (_m->D5_Inverter_Command_Mode & (0x01U)) | ((_m->D5_Rolling_Counter & (0x0FU)) << 4);
  cframe->Data[6] |= (_m->D6_Inverter_Enable_State & (0x01U)) | ((_m->D6_Start_Mode_Active & (0x01U)) << 6) | ((_m->D6_Inverter_Enable_Lockout & (0x01U)) << 7);
  cframe->Data[7] |= (_m->D7_Direction_Command & (0x01U)) | ((_m->D7_BMS_Active & (0x01U)) << 1) | ((_m->D7_BMS_Torque_Limiting & (0x01U)) << 2) | ((_m->D7_Max_Speed_Limiting & (0x01U)) << 3) | ((_m->D7_Low_Speed_Limiting & (0x01U)) << 5);

  cframe->MsgId = M170_Internal_States_CANID;
  cframe->DLC = M170_Internal_States_DLC;
  cframe->IDE = M170_Internal_States_IDE;
  return M170_Internal_States_CANID;
}

#else

uint32_t Pack_M170_Internal_States_bev_dbc(M170_Internal_States_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M170_Internal_States_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->D1_VSM_State & (0xFFU));
  _d[1] |= (_m->D1_PWM_Frequency & (0xFFU));
  _d[2] |= (_m->D2_Inverter_State & (0xFFU));
  _d[3] |= (_m->D3_Relay_1_Status & (0x01U)) | ((_m->D3_Relay_2_Status & (0x01U)) << 1) | ((_m->D3_Relay_3_Status & (0x01U)) << 2) | ((_m->D3_Relay_4_Status & (0x01U)) << 3) | ((_m->D3_Relay_5_Status & (0x01U)) << 4) | ((_m->D3_Relay_6_Status & (0x01U)) << 5);
  _d[4] |= (_m->D4_Inverter_Run_Mode & (0x01U)) | ((_m->D4_Inverter_Discharge_State & (0x07U)) << 5);
  _d[5] |= (_m->D5_Inverter_Command_Mode & (0x01U)) | ((_m->D5_Rolling_Counter & (0x0FU)) << 4);
  _d[6] |= (_m->D6_Inverter_Enable_State & (0x01U)) | ((_m->D6_Start_Mode_Active & (0x01U)) << 6) | ((_m->D6_Inverter_Enable_Lockout & (0x01U)) << 7);
  _d[7] |= (_m->D7_Direction_Command & (0x01U)) | ((_m->D7_BMS_Active & (0x01U)) << 1) | ((_m->D7_BMS_Torque_Limiting & (0x01U)) << 2) | ((_m->D7_Max_Speed_Limiting & (0x01U)) << 3) | ((_m->D7_Low_Speed_Limiting & (0x01U)) << 5);

  *_len = M170_Internal_States_DLC;
  *_ide = M170_Internal_States_IDE;
  return M170_Internal_States_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M171_Fault_Codes_bev_dbc(M171_Fault_Codes_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Post_Fault_Lo = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
  _m->D2_Post_Fault_Hi = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->D3_Run_Fault_Lo = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
  _m->D4_Run_Fault_Hi = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M171_Fault_Codes_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M171_Fault_Codes_bev_dbc(&_m->mon1, M171_Fault_Codes_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M171_Fault_Codes_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M171_Fault_Codes_bev_dbc(M171_Fault_Codes_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M171_Fault_Codes_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->D1_Post_Fault_Lo & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Post_Fault_Lo >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_Post_Fault_Hi & (0xFFU));
  cframe->Data[3] |= ((_m->D2_Post_Fault_Hi >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->D3_Run_Fault_Lo & (0xFFU));
  cframe->Data[5] |= ((_m->D3_Run_Fault_Lo >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->D4_Run_Fault_Hi & (0xFFU));
  cframe->Data[7] |= ((_m->D4_Run_Fault_Hi >> 8) & (0xFFU));

  cframe->MsgId = M171_Fault_Codes_CANID;
  cframe->DLC = M171_Fault_Codes_DLC;
  cframe->IDE = M171_Fault_Codes_IDE;
  return M171_Fault_Codes_CANID;
}

#else

uint32_t Pack_M171_Fault_Codes_bev_dbc(M171_Fault_Codes_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M171_Fault_Codes_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->D1_Post_Fault_Lo & (0xFFU));
  _d[1] |= ((_m->D1_Post_Fault_Lo >> 8) & (0xFFU));
  _d[2] |= (_m->D2_Post_Fault_Hi & (0xFFU));
  _d[3] |= ((_m->D2_Post_Fault_Hi >> 8) & (0xFFU));
  _d[4] |= (_m->D3_Run_Fault_Lo & (0xFFU));
  _d[5] |= ((_m->D3_Run_Fault_Lo >> 8) & (0xFFU));
  _d[6] |= (_m->D4_Run_Fault_Hi & (0xFFU));
  _d[7] |= ((_m->D4_Run_Fault_Hi >> 8) & (0xFFU));

  *_len = M171_Fault_Codes_DLC;
  *_ide = M171_Fault_Codes_IDE;
  return M171_Fault_Codes_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M172_Torque_And_Timer_Info_bev_dbc(M172_Torque_And_Timer_Info_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Commanded_Torque_ro = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Commanded_Torque_phys = (sigfloat_t)(BEV_DBC_D1_Commanded_Torque_ro_fromS(_m->D1_Commanded_Torque_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D2_Torque_Feedback_ro = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D2_Torque_Feedback_phys = (sigfloat_t)(BEV_DBC_D2_Torque_Feedback_ro_fromS(_m->D2_Torque_Feedback_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D3_Power_On_Timer_ro = ((_d[7] & (0xFFU)) << 24) | ((_d[6] & (0xFFU)) << 16) | ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D3_Power_On_Timer_phys = (sigfloat_t)(BEV_DBC_D3_Power_On_Timer_ro_fromS(_m->D3_Power_On_Timer_ro));
#endif // BEV_DBC_USE_SIGFLOAT

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M172_Torque_And_Timer_Info_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M172_Torque_And_Timer_Info_bev_dbc(&_m->mon1, M172_Torque_And_Timer_Info_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M172_Torque_And_Timer_Info_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M172_Torque_And_Timer_Info_bev_dbc(M172_Torque_And_Timer_Info_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M172_Torque_And_Timer_Info_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Commanded_Torque_ro = BEV_DBC_D1_Commanded_Torque_ro_toS(_m->D1_Commanded_Torque_phys);
  _m->D2_Torque_Feedback_ro = BEV_DBC_D2_Torque_Feedback_ro_toS(_m->D2_Torque_Feedback_phys);
  _m->D3_Power_On_Timer_ro = BEV_DBC_D3_Power_On_Timer_ro_toS(_m->D3_Power_On_Timer_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (_m->D1_Commanded_Torque_ro & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Commanded_Torque_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_Torque_Feedback_ro & (0xFFU));
  cframe->Data[3] |= ((_m->D2_Torque_Feedback_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->D3_Power_On_Timer_ro & (0xFFU));
  cframe->Data[5] |= ((_m->D3_Power_On_Timer_ro >> 8) & (0xFFU));
  cframe->Data[6] |= ((_m->D3_Power_On_Timer_ro >> 16) & (0xFFU));
  cframe->Data[7] |= ((_m->D3_Power_On_Timer_ro >> 24) & (0xFFU));

  cframe->MsgId = M172_Torque_And_Timer_Info_CANID;
  cframe->DLC = M172_Torque_And_Timer_Info_DLC;
  cframe->IDE = M172_Torque_And_Timer_Info_IDE;
  return M172_Torque_And_Timer_Info_CANID;
}

#else

uint32_t Pack_M172_Torque_And_Timer_Info_bev_dbc(M172_Torque_And_Timer_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M172_Torque_And_Timer_Info_DLC) && (i < 8); _d[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Commanded_Torque_ro = BEV_DBC_D1_Commanded_Torque_ro_toS(_m->D1_Commanded_Torque_phys);
  _m->D2_Torque_Feedback_ro = BEV_DBC_D2_Torque_Feedback_ro_toS(_m->D2_Torque_Feedback_phys);
  _m->D3_Power_On_Timer_ro = BEV_DBC_D3_Power_On_Timer_ro_toS(_m->D3_Power_On_Timer_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  _d[0] |= (_m->D1_Commanded_Torque_ro & (0xFFU));
  _d[1] |= ((_m->D1_Commanded_Torque_ro >> 8) & (0xFFU));
  _d[2] |= (_m->D2_Torque_Feedback_ro & (0xFFU));
  _d[3] |= ((_m->D2_Torque_Feedback_ro >> 8) & (0xFFU));
  _d[4] |= (_m->D3_Power_On_Timer_ro & (0xFFU));
  _d[5] |= ((_m->D3_Power_On_Timer_ro >> 8) & (0xFFU));
  _d[6] |= ((_m->D3_Power_On_Timer_ro >> 16) & (0xFFU));
  _d[7] |= ((_m->D3_Power_On_Timer_ro >> 24) & (0xFFU));

  *_len = M172_Torque_And_Timer_Info_DLC;
  *_ide = M172_Torque_And_Timer_Info_IDE;
  return M172_Torque_And_Timer_Info_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M173_Modulation_And_Flux_Info_bev_dbc(M173_Modulation_And_Flux_Info_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Modulation_Index_ro = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Modulation_Index_phys = (sigfloat_t)(BEV_DBC_D1_Modulation_Index_ro_fromS(_m->D1_Modulation_Index_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D2_Flux_Weakening_Output_ro = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D2_Flux_Weakening_Output_phys = (sigfloat_t)(BEV_DBC_D2_Flux_Weakening_Output_ro_fromS(_m->D2_Flux_Weakening_Output_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D3_Id_Command_ro = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D3_Id_Command_phys = (sigfloat_t)(BEV_DBC_D3_Id_Command_ro_fromS(_m->D3_Id_Command_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->D4_Iq_Command_ro = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D4_Iq_Command_phys = (sigfloat_t)(BEV_DBC_D4_Iq_Command_ro_fromS(_m->D4_Iq_Command_ro));
#endif // BEV_DBC_USE_SIGFLOAT

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M173_Modulation_And_Flux_Info_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M173_Modulation_And_Flux_Info_bev_dbc(&_m->mon1, M173_Modulation_And_Flux_Info_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M173_Modulation_And_Flux_Info_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M173_Modulation_And_Flux_Info_bev_dbc(M173_Modulation_And_Flux_Info_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M173_Modulation_And_Flux_Info_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Modulation_Index_ro = BEV_DBC_D1_Modulation_Index_ro_toS(_m->D1_Modulation_Index_phys);
  _m->D2_Flux_Weakening_Output_ro = BEV_DBC_D2_Flux_Weakening_Output_ro_toS(_m->D2_Flux_Weakening_Output_phys);
  _m->D3_Id_Command_ro = BEV_DBC_D3_Id_Command_ro_toS(_m->D3_Id_Command_phys);
  _m->D4_Iq_Command_ro = BEV_DBC_D4_Iq_Command_ro_toS(_m->D4_Iq_Command_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (_m->D1_Modulation_Index_ro & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Modulation_Index_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_Flux_Weakening_Output_ro & (0xFFU));
  cframe->Data[3] |= ((_m->D2_Flux_Weakening_Output_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->D3_Id_Command_ro & (0xFFU));
  cframe->Data[5] |= ((_m->D3_Id_Command_ro >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->D4_Iq_Command_ro & (0xFFU));
  cframe->Data[7] |= ((_m->D4_Iq_Command_ro >> 8) & (0xFFU));

  cframe->MsgId = M173_Modulation_And_Flux_Info_CANID;
  cframe->DLC = M173_Modulation_And_Flux_Info_DLC;
  cframe->IDE = M173_Modulation_And_Flux_Info_IDE;
  return M173_Modulation_And_Flux_Info_CANID;
}

#else

uint32_t Pack_M173_Modulation_And_Flux_Info_bev_dbc(M173_Modulation_And_Flux_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M173_Modulation_And_Flux_Info_DLC) && (i < 8); _d[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->D1_Modulation_Index_ro = BEV_DBC_D1_Modulation_Index_ro_toS(_m->D1_Modulation_Index_phys);
  _m->D2_Flux_Weakening_Output_ro = BEV_DBC_D2_Flux_Weakening_Output_ro_toS(_m->D2_Flux_Weakening_Output_phys);
  _m->D3_Id_Command_ro = BEV_DBC_D3_Id_Command_ro_toS(_m->D3_Id_Command_phys);
  _m->D4_Iq_Command_ro = BEV_DBC_D4_Iq_Command_ro_toS(_m->D4_Iq_Command_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  _d[0] |= (_m->D1_Modulation_Index_ro & (0xFFU));
  _d[1] |= ((_m->D1_Modulation_Index_ro >> 8) & (0xFFU));
  _d[2] |= (_m->D2_Flux_Weakening_Output_ro & (0xFFU));
  _d[3] |= ((_m->D2_Flux_Weakening_Output_ro >> 8) & (0xFFU));
  _d[4] |= (_m->D3_Id_Command_ro & (0xFFU));
  _d[5] |= ((_m->D3_Id_Command_ro >> 8) & (0xFFU));
  _d[6] |= (_m->D4_Iq_Command_ro & (0xFFU));
  _d[7] |= ((_m->D4_Iq_Command_ro >> 8) & (0xFFU));

  *_len = M173_Modulation_And_Flux_Info_DLC;
  *_ide = M173_Modulation_And_Flux_Info_IDE;
  return M173_Modulation_And_Flux_Info_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M174_Firmware_Info_bev_dbc(M174_Firmware_Info_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Project_Code_EEP_Ver = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
  _m->D2_SW_Version = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->D3_DateCode_MMDD = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
  _m->D4_DateCode_YYYY = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M174_Firmware_Info_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M174_Firmware_Info_bev_dbc(&_m->mon1, M174_Firmware_Info_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M174_Firmware_Info_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M174_Firmware_Info_bev_dbc(M174_Firmware_Info_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M174_Firmware_Info_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->D1_Project_Code_EEP_Ver & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Project_Code_EEP_Ver >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_SW_Version & (0xFFU));
  cframe->Data[3] |= ((_m->D2_SW_Version >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->D3_DateCode_MMDD & (0xFFU));
  cframe->Data[5] |= ((_m->D3_DateCode_MMDD >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->D4_DateCode_YYYY & (0xFFU));
  cframe->Data[7] |= ((_m->D4_DateCode_YYYY >> 8) & (0xFFU));

  cframe->MsgId = M174_Firmware_Info_CANID;
  cframe->DLC = M174_Firmware_Info_DLC;
  cframe->IDE = M174_Firmware_Info_IDE;
  return M174_Firmware_Info_CANID;
}

#else

uint32_t Pack_M174_Firmware_Info_bev_dbc(M174_Firmware_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M174_Firmware_Info_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->D1_Project_Code_EEP_Ver & (0xFFU));
  _d[1] |= ((_m->D1_Project_Code_EEP_Ver >> 8) & (0xFFU));
  _d[2] |= (_m->D2_SW_Version & (0xFFU));
  _d[3] |= ((_m->D2_SW_Version >> 8) & (0xFFU));
  _d[4] |= (_m->D3_DateCode_MMDD & (0xFFU));
  _d[5] |= ((_m->D3_DateCode_MMDD >> 8) & (0xFFU));
  _d[6] |= (_m->D4_DateCode_YYYY & (0xFFU));
  _d[7] |= ((_m->D4_DateCode_YYYY >> 8) & (0xFFU));

  *_len = M174_Firmware_Info_DLC;
  *_ide = M174_Firmware_Info_IDE;
  return M174_Firmware_Info_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M175_Diag_Data_bev_dbc(M175_Diag_Data_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Buffer_Record = (_d[0] & (0xFFU));
  _m->D2_Buffer_Segment = (_d[1] & (0xFFU));
  _m->D3_Diag_Data_1 = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->D4_Diag_Data_2 = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
  _m->D5_Diag_Data_3 = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M175_Diag_Data_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M175_Diag_Data_bev_dbc(&_m->mon1, M175_Diag_Data_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M175_Diag_Data_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M175_Diag_Data_bev_dbc(M175_Diag_Data_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M175_Diag_Data_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->D1_Buffer_Record & (0xFFU));
  cframe->Data[1] |= (_m->D2_Buffer_Segment & (0xFFU));
  cframe->Data[2] |= (_m->D3_Diag_Data_1 & (0xFFU));
  cframe->Data[3] |= ((_m->D3_Diag_Data_1 >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->D4_Diag_Data_2 & (0xFFU));
  cframe->Data[5] |= ((_m->D4_Diag_Data_2 >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->D5_Diag_Data_3 & (0xFFU));
  cframe->Data[7] |= ((_m->D5_Diag_Data_3 >> 8) & (0xFFU));

  cframe->MsgId = M175_Diag_Data_CANID;
  cframe->DLC = M175_Diag_Data_DLC;
  cframe->IDE = M175_Diag_Data_IDE;
  return M175_Diag_Data_CANID;
}

#else

uint32_t Pack_M175_Diag_Data_bev_dbc(M175_Diag_Data_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M175_Diag_Data_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->D1_Buffer_Record & (0xFFU));
  _d[1] |= (_m->D2_Buffer_Segment & (0xFFU));
  _d[2] |= (_m->D3_Diag_Data_1 & (0xFFU));
  _d[3] |= ((_m->D3_Diag_Data_1 >> 8) & (0xFFU));
  _d[4] |= (_m->D4_Diag_Data_2 & (0xFFU));
  _d[5] |= ((_m->D4_Diag_Data_2 >> 8) & (0xFFU));
  _d[6] |= (_m->D5_Diag_Data_3 & (0xFFU));
  _d[7] |= ((_m->D5_Diag_Data_3 >> 8) & (0xFFU));

  *_len = M175_Diag_Data_DLC;
  *_ide = M175_Diag_Data_IDE;
  return M175_Diag_Data_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M176_Fast_Info_bev_dbc(M176_Fast_Info_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->Fast_Torque_Command_ro = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->Fast_Torque_Command_phys = (sigfloat_t)(BEV_DBC_Fast_Torque_Command_ro_fromS(_m->Fast_Torque_Command_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->Fast_Torque_Feedback_ro = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->Fast_Torque_Feedback_phys = (sigfloat_t)(BEV_DBC_Fast_Torque_Feedback_ro_fromS(_m->Fast_Torque_Feedback_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->Fast_Motor_Speed = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));
  _m->Fast_DC_Bus_Voltage_ro = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->Fast_DC_Bus_Voltage_phys = (sigfloat_t)(BEV_DBC_Fast_DC_Bus_Voltage_ro_fromS(_m->Fast_DC_Bus_Voltage_ro));
#endif // BEV_DBC_USE_SIGFLOAT

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M176_Fast_Info_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M176_Fast_Info_bev_dbc(&_m->mon1, M176_Fast_Info_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M176_Fast_Info_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M176_Fast_Info_bev_dbc(M176_Fast_Info_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M176_Fast_Info_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->Fast_Torque_Command_ro = BEV_DBC_Fast_Torque_Command_ro_toS(_m->Fast_Torque_Command_phys);
  _m->Fast_Torque_Feedback_ro = BEV_DBC_Fast_Torque_Feedback_ro_toS(_m->Fast_Torque_Feedback_phys);
  _m->Fast_DC_Bus_Voltage_ro = BEV_DBC_Fast_DC_Bus_Voltage_ro_toS(_m->Fast_DC_Bus_Voltage_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (_m->Fast_Torque_Command_ro & (0xFFU));
  cframe->Data[1] |= ((_m->Fast_Torque_Command_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->Fast_Torque_Feedback_ro & (0xFFU));
  cframe->Data[3] |= ((_m->Fast_Torque_Feedback_ro >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->Fast_Motor_Speed & (0xFFU));
  cframe->Data[5] |= ((_m->Fast_Motor_Speed >> 8) & (0xFFU));
  cframe->Data[6] |= (_m->Fast_DC_Bus_Voltage_ro & (0xFFU));
  cframe->Data[7] |= ((_m->Fast_DC_Bus_Voltage_ro >> 8) & (0xFFU));

  cframe->MsgId = M176_Fast_Info_CANID;
  cframe->DLC = M176_Fast_Info_DLC;
  cframe->IDE = M176_Fast_Info_IDE;
  return M176_Fast_Info_CANID;
}

#else

uint32_t Pack_M176_Fast_Info_bev_dbc(M176_Fast_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M176_Fast_Info_DLC) && (i < 8); _d[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->Fast_Torque_Command_ro = BEV_DBC_Fast_Torque_Command_ro_toS(_m->Fast_Torque_Command_phys);
  _m->Fast_Torque_Feedback_ro = BEV_DBC_Fast_Torque_Feedback_ro_toS(_m->Fast_Torque_Feedback_phys);
  _m->Fast_DC_Bus_Voltage_ro = BEV_DBC_Fast_DC_Bus_Voltage_ro_toS(_m->Fast_DC_Bus_Voltage_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  _d[0] |= (_m->Fast_Torque_Command_ro & (0xFFU));
  _d[1] |= ((_m->Fast_Torque_Command_ro >> 8) & (0xFFU));
  _d[2] |= (_m->Fast_Torque_Feedback_ro & (0xFFU));
  _d[3] |= ((_m->Fast_Torque_Feedback_ro >> 8) & (0xFFU));
  _d[4] |= (_m->Fast_Motor_Speed & (0xFFU));
  _d[5] |= ((_m->Fast_Motor_Speed >> 8) & (0xFFU));
  _d[6] |= (_m->Fast_DC_Bus_Voltage_ro & (0xFFU));
  _d[7] |= ((_m->Fast_DC_Bus_Voltage_ro >> 8) & (0xFFU));

  *_len = M176_Fast_Info_DLC;
  *_ide = M176_Fast_Info_IDE;
  return M176_Fast_Info_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M192_Command_Message_bev_dbc(M192_Command_Message_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->Torque_Command_ro = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->Torque_Command_phys = (sigfloat_t)(BEV_DBC_Torque_Command_ro_fromS(_m->Torque_Command_ro));
#endif // BEV_DBC_USE_SIGFLOAT

  _m->Speed_Command = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));
  _m->Direction_Command = (_d[4] & (0x01U));
  _m->Inverter_Enable = (_d[5] & (0x01U));
  _m->Inverter_Discharge = ((_d[5] >> 1) & (0x01U));
  _m->Speed_Mode_Enable = ((_d[5] >> 2) & (0x01U));
  _m->RollingCounter = ((_d[5] >> 4) & (0x0FU));
  _m->Torque_Limit_Command_ro = ((_d[7] & (0xFFU)) << 8) | (_d[6] & (0xFFU));
#ifdef BEV_DBC_USE_SIGFLOAT
  _m->Torque_Limit_Command_phys = (sigfloat_t)(BEV_DBC_Torque_Limit_Command_ro_fromS(_m->Torque_Limit_Command_ro));
#endif // BEV_DBC_USE_SIGFLOAT

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M192_Command_Message_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M192_Command_Message_bev_dbc(&_m->mon1, M192_Command_Message_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M192_Command_Message_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M192_Command_Message_bev_dbc(M192_Command_Message_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M192_Command_Message_DLC) && (i < 8); cframe->Data[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->Torque_Command_ro = BEV_DBC_Torque_Command_ro_toS(_m->Torque_Command_phys);
  _m->Torque_Limit_Command_ro = BEV_DBC_Torque_Limit_Command_ro_toS(_m->Torque_Limit_Command_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  cframe->Data[0] |= (_m->Torque_Command_ro & (0xFFU));
  cframe->Data[1] |= ((_m->Torque_Command_ro >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->Speed_Command & (0xFFU));
  cframe->Data[3] |= ((_m->Speed_Command >> 8) & (0xFFU));
  cframe->Data[4] |= (_m->Direction_Command & (0x01U));
  cframe->Data[5] |= (_m->Inverter_Enable & (0x01U)) | ((_m->Inverter_Discharge & (0x01U)) << 1) | ((_m->Speed_Mode_Enable & (0x01U)) << 2) | ((_m->RollingCounter & (0x0FU)) << 4);
  cframe->Data[6] |= (_m->Torque_Limit_Command_ro & (0xFFU));
  cframe->Data[7] |= ((_m->Torque_Limit_Command_ro >> 8) & (0xFFU));

  cframe->MsgId = M192_Command_Message_CANID;
  cframe->DLC = M192_Command_Message_DLC;
  cframe->IDE = M192_Command_Message_IDE;
  return M192_Command_Message_CANID;
}

#else

uint32_t Pack_M192_Command_Message_bev_dbc(M192_Command_Message_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M192_Command_Message_DLC) && (i < 8); _d[i++] = 0);

#ifdef BEV_DBC_USE_SIGFLOAT
  _m->Torque_Command_ro = BEV_DBC_Torque_Command_ro_toS(_m->Torque_Command_phys);
  _m->Torque_Limit_Command_ro = BEV_DBC_Torque_Limit_Command_ro_toS(_m->Torque_Limit_Command_phys);
#endif // BEV_DBC_USE_SIGFLOAT

  _d[0] |= (_m->Torque_Command_ro & (0xFFU));
  _d[1] |= ((_m->Torque_Command_ro >> 8) & (0xFFU));
  _d[2] |= (_m->Speed_Command & (0xFFU));
  _d[3] |= ((_m->Speed_Command >> 8) & (0xFFU));
  _d[4] |= (_m->Direction_Command & (0x01U));
  _d[5] |= (_m->Inverter_Enable & (0x01U)) | ((_m->Inverter_Discharge & (0x01U)) << 1) | ((_m->Speed_Mode_Enable & (0x01U)) << 2) | ((_m->RollingCounter & (0x0FU)) << 4);
  _d[6] |= (_m->Torque_Limit_Command_ro & (0xFFU));
  _d[7] |= ((_m->Torque_Limit_Command_ro >> 8) & (0xFFU));

  *_len = M192_Command_Message_DLC;
  *_ide = M192_Command_Message_IDE;
  return M192_Command_Message_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M193_Read_Write_Param_Command_bev_dbc(M193_Read_Write_Param_Command_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Parameter_Address_Command = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
  _m->D2_Read_Write_Command = (_d[2] & (0x01U));
  _m->D3_Data_Command = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M193_Read_Write_Param_Command_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M193_Read_Write_Param_Command_bev_dbc(&_m->mon1, M193_Read_Write_Param_Command_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M193_Read_Write_Param_Command_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M193_Read_Write_Param_Command_bev_dbc(M193_Read_Write_Param_Command_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M193_Read_Write_Param_Command_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->D1_Parameter_Address_Command & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Parameter_Address_Command >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_Read_Write_Command & (0x01U));
  cframe->Data[4] |= (_m->D3_Data_Command & (0xFFU));
  cframe->Data[5] |= ((_m->D3_Data_Command >> 8) & (0xFFU));

  cframe->MsgId = M193_Read_Write_Param_Command_CANID;
  cframe->DLC = M193_Read_Write_Param_Command_DLC;
  cframe->IDE = M193_Read_Write_Param_Command_IDE;
  return M193_Read_Write_Param_Command_CANID;
}

#else

uint32_t Pack_M193_Read_Write_Param_Command_bev_dbc(M193_Read_Write_Param_Command_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M193_Read_Write_Param_Command_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->D1_Parameter_Address_Command & (0xFFU));
  _d[1] |= ((_m->D1_Parameter_Address_Command >> 8) & (0xFFU));
  _d[2] |= (_m->D2_Read_Write_Command & (0x01U));
  _d[4] |= (_m->D3_Data_Command & (0xFFU));
  _d[5] |= ((_m->D3_Data_Command >> 8) & (0xFFU));

  *_len = M193_Read_Write_Param_Command_DLC;
  *_ide = M193_Read_Write_Param_Command_IDE;
  return M193_Read_Write_Param_Command_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M194_Read_Write_Param_Response_bev_dbc(M194_Read_Write_Param_Response_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Parameter_Address_Response = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
  _m->D2_Write_Success = (_d[2] & (0x01U));
  _m->D3_Data_Response = ((_d[5] & (0xFFU)) << 8) | (_d[4] & (0xFFU));

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M194_Read_Write_Param_Response_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M194_Read_Write_Param_Response_bev_dbc(&_m->mon1, M194_Read_Write_Param_Response_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M194_Read_Write_Param_Response_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M194_Read_Write_Param_Response_bev_dbc(M194_Read_Write_Param_Response_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M194_Read_Write_Param_Response_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->D1_Parameter_Address_Response & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Parameter_Address_Response >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_Write_Success & (0x01U));
  cframe->Data[4] |= (_m->D3_Data_Response & (0xFFU));
  cframe->Data[5] |= ((_m->D3_Data_Response >> 8) & (0xFFU));

  cframe->MsgId = M194_Read_Write_Param_Response_CANID;
  cframe->DLC = M194_Read_Write_Param_Response_DLC;
  cframe->IDE = M194_Read_Write_Param_Response_IDE;
  return M194_Read_Write_Param_Response_CANID;
}

#else

uint32_t Pack_M194_Read_Write_Param_Response_bev_dbc(M194_Read_Write_Param_Response_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M194_Read_Write_Param_Response_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->D1_Parameter_Address_Response & (0xFFU));
  _d[1] |= ((_m->D1_Parameter_Address_Response >> 8) & (0xFFU));
  _d[2] |= (_m->D2_Write_Success & (0x01U));
  _d[4] |= (_m->D3_Data_Response & (0xFFU));
  _d[5] |= ((_m->D3_Data_Response >> 8) & (0xFFU));

  *_len = M194_Read_Write_Param_Response_DLC;
  *_ide = M194_Read_Write_Param_Response_IDE;
  return M194_Read_Write_Param_Response_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M188_U2C_Message_Rxd_bev_dbc(M188_U2C_Message_Rxd_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_HV_Input_Current_Sensor_Validity = ((_d[0] >> 4) & (0x01U));
  _m->D2_14V_Master_Fault = ((_d[0] >> 7) & (0x01U));
  _m->D3_HV_Input_Current = (_d[1] & (0xFFU));
  _m->D4_DTC_Status = (_d[2] & (0x07U));
  _m->D5_DTC_Index = ((_d[2] >> 3) & (0x1FU));
  _m->D6_14V_Monitor = (_d[3] & (0xFFU));
  _m->D7_14V_Conditional = ((_d[4] >> 7) & (0x01U));
  _m->D8_14V_Current_Monitor = (_d[6] & (0x7FU));

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M188_U2C_Message_Rxd_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M188_U2C_Message_Rxd_bev_dbc(&_m->mon1, M188_U2C_Message_Rxd_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M188_U2C_Message_Rxd_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M188_U2C_Message_Rxd_bev_dbc(M188_U2C_Message_Rxd_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M188_U2C_Message_Rxd_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= ((_m->D1_HV_Input_Current_Sensor_Validity & (0x01U)) << 4) | ((_m->D2_14V_Master_Fault & (0x01U)) << 7);
  cframe->Data[1] |= (_m->D3_HV_Input_Current & (0xFFU));
  cframe->Data[2] |= (_m->D4_DTC_Status & (0x07U)) | ((_m->D5_DTC_Index & (0x1FU)) << 3);
  cframe->Data[3] |= (_m->D6_14V_Monitor & (0xFFU));
  cframe->Data[4] |= ((_m->D7_14V_Conditional & (0x01U)) << 7);
  cframe->Data[6] |= (_m->D8_14V_Current_Monitor & (0x7FU));

  cframe->MsgId = M188_U2C_Message_Rxd_CANID;
  cframe->DLC = M188_U2C_Message_Rxd_DLC;
  cframe->IDE = M188_U2C_Message_Rxd_IDE;
  return M188_U2C_Message_Rxd_CANID;
}

#else

uint32_t Pack_M188_U2C_Message_Rxd_bev_dbc(M188_U2C_Message_Rxd_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M188_U2C_Message_Rxd_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= ((_m->D1_HV_Input_Current_Sensor_Validity & (0x01U)) << 4) | ((_m->D2_14V_Master_Fault & (0x01U)) << 7);
  _d[1] |= (_m->D3_HV_Input_Current & (0xFFU));
  _d[2] |= (_m->D4_DTC_Status & (0x07U)) | ((_m->D5_DTC_Index & (0x1FU)) << 3);
  _d[3] |= (_m->D6_14V_Monitor & (0xFFU));
  _d[4] |= ((_m->D7_14V_Conditional & (0x01U)) << 7);
  _d[6] |= (_m->D8_14V_Current_Monitor & (0x7FU));

  *_len = M188_U2C_Message_Rxd_DLC;
  *_ide = M188_U2C_Message_Rxd_IDE;
  return M188_U2C_Message_Rxd_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M187_U2C_Command_Txd_bev_dbc(M187_U2C_Command_Txd_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_ID_Byte = (_d[0] & (0xFFU));
  _m->D2_Setpoint_Calc = (_d[1] & (0xFFU));

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < M187_U2C_Command_Txd_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_M187_U2C_Command_Txd_bev_dbc(&_m->mon1, M187_U2C_Command_Txd_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return M187_U2C_Command_Txd_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_M187_U2C_Command_Txd_bev_dbc(M187_U2C_Command_Txd_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < M187_U2C_Command_Txd_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->D1_ID_Byte & (0xFFU));
  cframe->Data[1] |= (_m->D2_Setpoint_Calc & (0xFFU));

  cframe->MsgId = M187_U2C_Command_Txd_CANID;
  cframe->DLC = M187_U2C_Command_Txd_DLC;
  cframe->IDE = M187_U2C_Command_Txd_IDE;
  return M187_U2C_Command_Txd_CANID;
}

#else

uint32_t Pack_M187_U2C_Command_Txd_bev_dbc(M187_U2C_Command_Txd_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < M187_U2C_Command_Txd_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->D1_ID_Byte & (0xFFU));
  _d[1] |= (_m->D2_Setpoint_Calc & (0xFFU));

  *_len = M187_U2C_Command_Txd_DLC;
  *_ide = M187_U2C_Command_Txd_IDE;
  return M187_U2C_Command_Txd_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_BMS_Current_Limit_bev_dbc(BMS_Current_Limit_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->D1_Max_Discharge_Current = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
  _m->D2_Max_Charge_Current = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BMS_Current_Limit_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BMS_Current_Limit_bev_dbc(&_m->mon1, BMS_Current_Limit_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return BMS_Current_Limit_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_BMS_Current_Limit_bev_dbc(BMS_Current_Limit_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BMS_Current_Limit_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->D1_Max_Discharge_Current & (0xFFU));
  cframe->Data[1] |= ((_m->D1_Max_Discharge_Current >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->D2_Max_Charge_Current & (0xFFU));
  cframe->Data[3] |= ((_m->D2_Max_Charge_Current >> 8) & (0xFFU));

  cframe->MsgId = BMS_Current_Limit_CANID;
  cframe->DLC = BMS_Current_Limit_DLC;
  cframe->IDE = BMS_Current_Limit_IDE;
  return BMS_Current_Limit_CANID;
}

#else

uint32_t Pack_BMS_Current_Limit_bev_dbc(BMS_Current_Limit_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BMS_Current_Limit_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->D1_Max_Discharge_Current & (0xFFU));
  _d[1] |= ((_m->D1_Max_Discharge_Current >> 8) & (0xFFU));
  _d[2] |= (_m->D2_Max_Charge_Current & (0xFFU));
  _d[3] |= ((_m->D2_Max_Charge_Current >> 8) & (0xFFU));

  *_len = BMS_Current_Limit_DLC;
  *_ide = BMS_Current_Limit_IDE;
  return BMS_Current_Limit_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_BMS_Msg1_bev_dbc(BMS_Msg1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->SOC = (_d[0] & (0xFFU));
  _m->DCL = (_d[1] & (0xFFU));
  _m->CCL = (_d[2] & (0xFFU));
  _m->Internal_Temperature = (_d[3] & (0xFFU));
  _m->Highest_Cell_Voltage = (_d[4] & (0xFFU));
  _m->Pack_Current = (_d[5] & (0xFFU));
  _m->Populated_Cells = (_d[6] & (0xFFU));
  _m->Checksum = (_d[7] & (0xFFU));

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BMS_Msg1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BMS_Msg1_bev_dbc(&_m->mon1, BMS_Msg1_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return BMS_Msg1_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_BMS_Msg1_bev_dbc(BMS_Msg1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BMS_Msg1_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->SOC & (0xFFU));
  cframe->Data[1] |= (_m->DCL & (0xFFU));
  cframe->Data[2] |= (_m->CCL & (0xFFU));
  cframe->Data[3] |= (_m->Internal_Temperature & (0xFFU));
  cframe->Data[4] |= (_m->Highest_Cell_Voltage & (0xFFU));
  cframe->Data[5] |= (_m->Pack_Current & (0xFFU));
  cframe->Data[6] |= (_m->Populated_Cells & (0xFFU));
  cframe->Data[7] |= (_m->Checksum & (0xFFU));

  cframe->MsgId = BMS_Msg1_CANID;
  cframe->DLC = BMS_Msg1_DLC;
  cframe->IDE = BMS_Msg1_IDE;
  return BMS_Msg1_CANID;
}

#else

uint32_t Pack_BMS_Msg1_bev_dbc(BMS_Msg1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BMS_Msg1_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->SOC & (0xFFU));
  _d[1] |= (_m->DCL & (0xFFU));
  _d[2] |= (_m->CCL & (0xFFU));
  _d[3] |= (_m->Internal_Temperature & (0xFFU));
  _d[4] |= (_m->Highest_Cell_Voltage & (0xFFU));
  _d[5] |= (_m->Pack_Current & (0xFFU));
  _d[6] |= (_m->Populated_Cells & (0xFFU));
  _d[7] |= (_m->Checksum & (0xFFU));

  *_len = BMS_Msg1_DLC;
  *_ide = BMS_Msg1_IDE;
  return BMS_Msg1_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_BMS_Faults1_bev_dbc(BMS_Faults1_t* _m, const uint8_t* _d, uint8_t dlc_)
{
  (void)dlc_;
  _m->DTCStatus1 = ((_d[1] & (0xFFU)) << 8) | (_d[0] & (0xFFU));
  _m->DTCStatus2 = ((_d[3] & (0xFFU)) << 8) | (_d[2] & (0xFFU));

#ifdef BEV_DBC_USE_DIAG_MONITORS
  _m->mon1.dlc_error = (dlc_ < BMS_Faults1_DLC);
  _m->mon1.last_cycle = GetSystemTick();
  _m->mon1.frame_cnt++;

  FMon_BMS_Faults1_bev_dbc(&_m->mon1, BMS_Faults1_CANID);
#endif // BEV_DBC_USE_DIAG_MONITORS

  return BMS_Faults1_CANID;
}

#ifdef BEV_DBC_USE_CANSTRUCT

uint32_t Pack_BMS_Faults1_bev_dbc(BMS_Faults1_t* _m, __CoderDbcCanFrame_t__* cframe)
{
  uint8_t i; for (i = 0; (i < BMS_Faults1_DLC) && (i < 8); cframe->Data[i++] = 0);

  cframe->Data[0] |= (_m->DTCStatus1 & (0xFFU));
  cframe->Data[1] |= ((_m->DTCStatus1 >> 8) & (0xFFU));
  cframe->Data[2] |= (_m->DTCStatus2 & (0xFFU));
  cframe->Data[3] |= ((_m->DTCStatus2 >> 8) & (0xFFU));

  cframe->MsgId = BMS_Faults1_CANID;
  cframe->DLC = BMS_Faults1_DLC;
  cframe->IDE = BMS_Faults1_IDE;
  return BMS_Faults1_CANID;
}

#else

uint32_t Pack_BMS_Faults1_bev_dbc(BMS_Faults1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)
{
  uint8_t i; for (i = 0; (i < BMS_Faults1_DLC) && (i < 8); _d[i++] = 0);

  _d[0] |= (_m->DTCStatus1 & (0xFFU));
  _d[1] |= ((_m->DTCStatus1 >> 8) & (0xFFU));
  _d[2] |= (_m->DTCStatus2 & (0xFFU));
  _d[3] |= ((_m->DTCStatus2 >> 8) & (0xFFU));

  *_len = BMS_Faults1_DLC;
  *_ide = BMS_Faults1_IDE;
  return BMS_Faults1_CANID;
}

#endif // BEV_DBC_USE_CANSTRUCT

