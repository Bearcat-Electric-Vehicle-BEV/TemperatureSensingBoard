#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// DBC file version
#define VER_BEV_DBC_MAJ (0U)
#define VER_BEV_DBC_MIN (0U)

// include current dbc-driver compilation config
#include "bev_dbc-config.h"

#ifdef BEV_DBC_USE_DIAG_MONITORS
// This file must define:
// base monitor struct
// function signature for HASH calculation: (@GetFrameHash)
// function signature for getting system tick value: (@GetSystemTick)
#include "canmonitorutil.h"

#endif // BEV_DBC_USE_DIAG_MONITORS


// def @M160_Temperature_Set_1 CAN Message (160  0xa0)
#define M160_Temperature_Set_1_IDE (0U)
#define M160_Temperature_Set_1_DLC (8U)
#define M160_Temperature_Set_1_CANID (0xa0)
#define M160_Temperature_Set_1_CYC (100U)
// signal: @D1_Module_A_ro
#define BEV_DBC_D1_Module_A_ro_CovFactor (0.100000)
#define BEV_DBC_D1_Module_A_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D1_Module_A_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D2_Module_B_ro
#define BEV_DBC_D2_Module_B_ro_CovFactor (0.100000)
#define BEV_DBC_D2_Module_B_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D2_Module_B_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D3_Module_C_ro
#define BEV_DBC_D3_Module_C_ro_CovFactor (0.100000)
#define BEV_DBC_D3_Module_C_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D3_Module_C_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D4_Gate_Driver_Board_ro
#define BEV_DBC_D4_Gate_Driver_Board_ro_CovFactor (0.100000)
#define BEV_DBC_D4_Gate_Driver_Board_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D4_Gate_Driver_Board_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  int16_t D1_Module_A_ro;                    //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Module_A_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Module_B_ro;                    //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Module_B_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_Module_C_ro;                    //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Module_C_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_Gate_Driver_Board_ro;           //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Gate_Driver_Board_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#else

  int16_t D1_Module_A_ro;                    //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Module_A_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Module_B_ro;                    //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Module_B_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_Module_C_ro;                    //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Module_C_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_Gate_Driver_Board_ro;           //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Gate_Driver_Board_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M160_Temperature_Set_1_t;

// def @M161_Temperature_Set_2 CAN Message (161  0xa1)
#define M161_Temperature_Set_2_IDE (0U)
#define M161_Temperature_Set_2_DLC (8U)
#define M161_Temperature_Set_2_CANID (0xa1)
#define M161_Temperature_Set_2_CYC (100U)
// signal: @D1_Control_Board_Temperature_ro
#define BEV_DBC_D1_Control_Board_Temperature_ro_CovFactor (0.100000)
#define BEV_DBC_D1_Control_Board_Temperature_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D1_Control_Board_Temperature_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D2_RTD1_Temperature_ro
#define BEV_DBC_D2_RTD1_Temperature_ro_CovFactor (0.100000)
#define BEV_DBC_D2_RTD1_Temperature_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D2_RTD1_Temperature_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D3_RTD2_Temperature_ro
#define BEV_DBC_D3_RTD2_Temperature_ro_CovFactor (0.100000)
#define BEV_DBC_D3_RTD2_Temperature_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D3_RTD2_Temperature_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D4_RTD3_Temperature_ro
#define BEV_DBC_D4_RTD3_Temperature_ro_CovFactor (0.100000)
#define BEV_DBC_D4_RTD3_Temperature_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D4_RTD3_Temperature_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  int16_t D1_Control_Board_Temperature_ro;       //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Control_Board_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_RTD1_Temperature_ro;                //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_RTD1_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_RTD2_Temperature_ro;                //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_RTD2_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_RTD3_Temperature_ro;                //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_RTD3_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#else

  int16_t D1_Control_Board_Temperature_ro;       //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Control_Board_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_RTD1_Temperature_ro;                //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_RTD1_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_RTD2_Temperature_ro;                //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_RTD2_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_RTD3_Temperature_ro;                //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_RTD3_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M161_Temperature_Set_2_t;

// def @M162_Temperature_Set_3 CAN Message (162  0xa2)
#define M162_Temperature_Set_3_IDE (0U)
#define M162_Temperature_Set_3_DLC (8U)
#define M162_Temperature_Set_3_CANID (0xa2)
#define M162_Temperature_Set_3_CYC (100U)
// signal: @D1_RTD4_Temperature_ro
#define BEV_DBC_D1_RTD4_Temperature_ro_CovFactor (0.100000)
#define BEV_DBC_D1_RTD4_Temperature_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D1_RTD4_Temperature_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D2_RTD5_Temperature_ro
#define BEV_DBC_D2_RTD5_Temperature_ro_CovFactor (0.100000)
#define BEV_DBC_D2_RTD5_Temperature_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D2_RTD5_Temperature_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D3_Motor_Temperature_ro
#define BEV_DBC_D3_Motor_Temperature_ro_CovFactor (0.100000)
#define BEV_DBC_D3_Motor_Temperature_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D3_Motor_Temperature_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D4_Torque_Shudder_ro
#define BEV_DBC_D4_Torque_Shudder_ro_CovFactor (0.100000)
#define BEV_DBC_D4_Torque_Shudder_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D4_Torque_Shudder_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  int16_t D1_RTD4_Temperature_ro;            //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_RTD4_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_RTD5_Temperature_ro;            //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_RTD5_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_Motor_Temperature_ro;           //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Motor_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_Torque_Shudder_ro;              //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Torque_Shudder_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#else

  int16_t D1_RTD4_Temperature_ro;            //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_RTD4_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_RTD5_Temperature_ro;            //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_RTD5_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_Motor_Temperature_ro;           //  [-] Bits=16 Factor= 0.100000        Unit:'degC'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Motor_Temperature_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_Torque_Shudder_ro;              //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Torque_Shudder_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M162_Temperature_Set_3_t;

// def @M163_Analog_Input_Voltages CAN Message (163  0xa3)
#define M163_Analog_Input_Voltages_IDE (0U)
#define M163_Analog_Input_Voltages_DLC (8U)
#define M163_Analog_Input_Voltages_CANID (0xa3)
#define M163_Analog_Input_Voltages_CYC (10U)
// signal: @D1_Analog_Input_1_ro
#define BEV_DBC_D1_Analog_Input_1_ro_CovFactor (0.010000)
#define BEV_DBC_D1_Analog_Input_1_ro_toS(x) ( (uint16_t) (((x) - (0.000000)) / (0.010000)) )
#define BEV_DBC_D1_Analog_Input_1_ro_fromS(x) ( (((x) * (0.010000)) + (0.000000)) )
// signal: @D2_Analog_Input_2_ro
#define BEV_DBC_D2_Analog_Input_2_ro_CovFactor (0.010000)
#define BEV_DBC_D2_Analog_Input_2_ro_toS(x) ( (uint16_t) (((x) - (0.000000)) / (0.010000)) )
#define BEV_DBC_D2_Analog_Input_2_ro_fromS(x) ( (((x) * (0.010000)) + (0.000000)) )
// signal: @D3_Analog_Input_3_ro
#define BEV_DBC_D3_Analog_Input_3_ro_CovFactor (0.010000)
#define BEV_DBC_D3_Analog_Input_3_ro_toS(x) ( (uint16_t) (((x) - (0.000000)) / (0.010000)) )
#define BEV_DBC_D3_Analog_Input_3_ro_fromS(x) ( (((x) * (0.010000)) + (0.000000)) )
// signal: @D4_Analog_Input_4_ro
#define BEV_DBC_D4_Analog_Input_4_ro_CovFactor (0.010000)
#define BEV_DBC_D4_Analog_Input_4_ro_toS(x) ( (uint16_t) (((x) - (0.000000)) / (0.010000)) )
#define BEV_DBC_D4_Analog_Input_4_ro_fromS(x) ( (((x) * (0.010000)) + (0.000000)) )
// signal: @D5_Analog_Input_5_ro
#define BEV_DBC_D5_Analog_Input_5_ro_CovFactor (0.010000)
#define BEV_DBC_D5_Analog_Input_5_ro_toS(x) ( (uint16_t) (((x) - (0.000000)) / (0.010000)) )
#define BEV_DBC_D5_Analog_Input_5_ro_fromS(x) ( (((x) * (0.010000)) + (0.000000)) )
// signal: @D6_Analog_Input_6_ro
#define BEV_DBC_D6_Analog_Input_6_ro_CovFactor (0.010000)
#define BEV_DBC_D6_Analog_Input_6_ro_toS(x) ( (uint16_t) (((x) - (0.000000)) / (0.010000)) )
#define BEV_DBC_D6_Analog_Input_6_ro_fromS(x) ( (((x) * (0.010000)) + (0.000000)) )

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  uint16_t D1_Analog_Input_1_ro;             //      Bits=10 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Analog_Input_1_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  uint16_t D2_Analog_Input_2_ro;             //      Bits=10 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Analog_Input_2_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  uint16_t D3_Analog_Input_3_ro;             //      Bits=10 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Analog_Input_3_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  uint16_t D4_Analog_Input_4_ro;             //      Bits=10 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Analog_Input_4_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  uint16_t D5_Analog_Input_5_ro;             //      Bits=10 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D5_Analog_Input_5_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  uint16_t D6_Analog_Input_6_ro;             //      Bits=10 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D6_Analog_Input_6_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#else

  uint16_t D1_Analog_Input_1_ro;             //      Bits=10 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Analog_Input_1_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  uint16_t D2_Analog_Input_2_ro;             //      Bits=10 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Analog_Input_2_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  uint16_t D3_Analog_Input_3_ro;             //      Bits=10 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Analog_Input_3_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  uint16_t D4_Analog_Input_4_ro;             //      Bits=10 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Analog_Input_4_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  uint16_t D5_Analog_Input_5_ro;             //      Bits=10 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D5_Analog_Input_5_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  uint16_t D6_Analog_Input_6_ro;             //      Bits=10 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D6_Analog_Input_6_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M163_Analog_Input_Voltages_t;

// def @M164_Digital_Input_Status CAN Message (164  0xa4)
#define M164_Digital_Input_Status_IDE (0U)
#define M164_Digital_Input_Status_DLC (8U)
#define M164_Digital_Input_Status_CANID (0xa4)
#define M164_Digital_Input_Status_CYC (10U)

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  // Status of Digital Input #1
  uint8_t D1_Digital_Input_1 : 1;            //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #2
  uint8_t D2_Digital_Input_2 : 1;            //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #3
  uint8_t D3_Digital_Input_3 : 1;            //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #4
  uint8_t D4_Digital_Input_4 : 1;            //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #5
  uint8_t D5_Digital_Input_5 : 1;            //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #6
  uint8_t D6_Digital_Input_6 : 1;            //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #7
  uint8_t D7_Digital_Input_7 : 1;            //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #8
  uint8_t D8_Digital_Input_8 : 1;            //      Bits= 1 Unit:'boolean'

#else

  // Status of Digital Input #1
  uint8_t D1_Digital_Input_1;                //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #2
  uint8_t D2_Digital_Input_2;                //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #3
  uint8_t D3_Digital_Input_3;                //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #4
  uint8_t D4_Digital_Input_4;                //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #5
  uint8_t D5_Digital_Input_5;                //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #6
  uint8_t D6_Digital_Input_6;                //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #7
  uint8_t D7_Digital_Input_7;                //      Bits= 1 Unit:'boolean'

  // Status of Digital Input #8
  uint8_t D8_Digital_Input_8;                //      Bits= 1 Unit:'boolean'

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M164_Digital_Input_Status_t;

// def @M165_Motor_Position_Info CAN Message (165  0xa5)
#define M165_Motor_Position_Info_IDE (0U)
#define M165_Motor_Position_Info_DLC (8U)
#define M165_Motor_Position_Info_CANID (0xa5)
#define M165_Motor_Position_Info_CYC (10U)
// signal: @D1_Motor_Angle_Electrical_ro
#define BEV_DBC_D1_Motor_Angle_Electrical_ro_CovFactor (0.100000)
#define BEV_DBC_D1_Motor_Angle_Electrical_ro_toS(x) ( (uint16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D1_Motor_Angle_Electrical_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D3_Electrical_Output_Frequency_ro
#define BEV_DBC_D3_Electrical_Output_Frequency_ro_CovFactor (0.100000)
#define BEV_DBC_D3_Electrical_Output_Frequency_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D3_Electrical_Output_Frequency_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D4_Delta_Resolver_Filtered_ro
#define BEV_DBC_D4_Delta_Resolver_Filtered_ro_CovFactor (0.100000)
#define BEV_DBC_D4_Delta_Resolver_Filtered_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D4_Delta_Resolver_Filtered_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  uint16_t D1_Motor_Angle_Electrical_ro;           //      Bits=16 Factor= 0.100000        Unit:'deg'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Motor_Angle_Electrical_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  // The measured speed of the motor
  int16_t D2_Motor_Speed;                          //  [-] Bits=16 Unit:'rpm'

  int16_t D3_Electrical_Output_Frequency_ro;       //  [-] Bits=16 Factor= 0.100000        Unit:'hz'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Electrical_Output_Frequency_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_Delta_Resolver_Filtered_ro;           //  [-] Bits=16 Factor= 0.100000        Unit:'deg'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Delta_Resolver_Filtered_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#else

  uint16_t D1_Motor_Angle_Electrical_ro;           //      Bits=16 Factor= 0.100000        Unit:'deg'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Motor_Angle_Electrical_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  // The measured speed of the motor
  int16_t D2_Motor_Speed;                          //  [-] Bits=16 Unit:'rpm'

  int16_t D3_Electrical_Output_Frequency_ro;       //  [-] Bits=16 Factor= 0.100000        Unit:'hz'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Electrical_Output_Frequency_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_Delta_Resolver_Filtered_ro;           //  [-] Bits=16 Factor= 0.100000        Unit:'deg'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Delta_Resolver_Filtered_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M165_Motor_Position_Info_t;

// def @M166_Current_Info CAN Message (166  0xa6)
#define M166_Current_Info_IDE (0U)
#define M166_Current_Info_DLC (8U)
#define M166_Current_Info_CANID (0xa6)
#define M166_Current_Info_CYC (10U)
// signal: @D1_Phase_A_Current_ro
#define BEV_DBC_D1_Phase_A_Current_ro_CovFactor (0.100000)
#define BEV_DBC_D1_Phase_A_Current_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D1_Phase_A_Current_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D2_Phase_B_Current_ro
#define BEV_DBC_D2_Phase_B_Current_ro_CovFactor (0.100000)
#define BEV_DBC_D2_Phase_B_Current_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D2_Phase_B_Current_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D3_Phase_C_Current_ro
#define BEV_DBC_D3_Phase_C_Current_ro_CovFactor (0.100000)
#define BEV_DBC_D3_Phase_C_Current_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D3_Phase_C_Current_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D4_DC_Bus_Current_ro
#define BEV_DBC_D4_DC_Bus_Current_ro_CovFactor (0.100000)
#define BEV_DBC_D4_DC_Bus_Current_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D4_DC_Bus_Current_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  int16_t D1_Phase_A_Current_ro;             //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Phase_A_Current_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Phase_B_Current_ro;             //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Phase_B_Current_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_Phase_C_Current_ro;             //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Phase_C_Current_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_DC_Bus_Current_ro;              //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_DC_Bus_Current_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#else

  int16_t D1_Phase_A_Current_ro;             //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Phase_A_Current_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Phase_B_Current_ro;             //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Phase_B_Current_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_Phase_C_Current_ro;             //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Phase_C_Current_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_DC_Bus_Current_ro;              //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_DC_Bus_Current_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M166_Current_Info_t;

// def @M167_Voltage_Info CAN Message (167  0xa7)
#define M167_Voltage_Info_IDE (0U)
#define M167_Voltage_Info_DLC (8U)
#define M167_Voltage_Info_CANID (0xa7)
#define M167_Voltage_Info_CYC (10U)
// signal: @D1_DC_Bus_Voltage_ro
#define BEV_DBC_D1_DC_Bus_Voltage_ro_CovFactor (0.100000)
#define BEV_DBC_D1_DC_Bus_Voltage_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D1_DC_Bus_Voltage_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D2_Output_Voltage_ro
#define BEV_DBC_D2_Output_Voltage_ro_CovFactor (0.100000)
#define BEV_DBC_D2_Output_Voltage_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D2_Output_Voltage_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D3_VAB_Vd_Voltage_ro
#define BEV_DBC_D3_VAB_Vd_Voltage_ro_CovFactor (0.100000)
#define BEV_DBC_D3_VAB_Vd_Voltage_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D3_VAB_Vd_Voltage_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D4_VBC_Vq_Voltage_ro
#define BEV_DBC_D4_VBC_Vq_Voltage_ro_CovFactor (0.100000)
#define BEV_DBC_D4_VBC_Vq_Voltage_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D4_VBC_Vq_Voltage_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  int16_t D1_DC_Bus_Voltage_ro;              //  [-] Bits=16 Factor= 0.100000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_DC_Bus_Voltage_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Output_Voltage_ro;              //  [-] Bits=16 Factor= 0.100000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Output_Voltage_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_VAB_Vd_Voltage_ro;              //  [-] Bits=16 Factor= 0.100000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_VAB_Vd_Voltage_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_VBC_Vq_Voltage_ro;              //  [-] Bits=16 Factor= 0.100000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_VBC_Vq_Voltage_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#else

  int16_t D1_DC_Bus_Voltage_ro;              //  [-] Bits=16 Factor= 0.100000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_DC_Bus_Voltage_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Output_Voltage_ro;              //  [-] Bits=16 Factor= 0.100000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Output_Voltage_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_VAB_Vd_Voltage_ro;              //  [-] Bits=16 Factor= 0.100000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_VAB_Vd_Voltage_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_VBC_Vq_Voltage_ro;              //  [-] Bits=16 Factor= 0.100000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_VBC_Vq_Voltage_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M167_Voltage_Info_t;

// def @M168_Flux_ID_IQ_Info CAN Message (168  0xa8)
#define M168_Flux_ID_IQ_Info_IDE (0U)
#define M168_Flux_ID_IQ_Info_DLC (8U)
#define M168_Flux_ID_IQ_Info_CANID (0xa8)
#define M168_Flux_ID_IQ_Info_CYC (10U)
// signal: @D1_Flux_Command_ro
#define BEV_DBC_D1_Flux_Command_ro_CovFactor (0.001000)
#define BEV_DBC_D1_Flux_Command_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.001000)) )
#define BEV_DBC_D1_Flux_Command_ro_fromS(x) ( (((x) * (0.001000)) + (0.000000)) )
// signal: @D2_Flux_Feedback_ro
#define BEV_DBC_D2_Flux_Feedback_ro_CovFactor (0.001000)
#define BEV_DBC_D2_Flux_Feedback_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.001000)) )
#define BEV_DBC_D2_Flux_Feedback_ro_fromS(x) ( (((x) * (0.001000)) + (0.000000)) )
// signal: @D3_Id_ro
#define BEV_DBC_D3_Id_ro_CovFactor (0.100000)
#define BEV_DBC_D3_Id_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D3_Id_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D4_Iq_ro
#define BEV_DBC_D4_Iq_ro_CovFactor (0.100000)
#define BEV_DBC_D4_Iq_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D4_Iq_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  int16_t D1_Flux_Command_ro;                //  [-] Bits=16 Factor= 0.001000        Unit:'Wb'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Flux_Command_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Flux_Feedback_ro;               //  [-] Bits=16 Factor= 0.001000        Unit:'Wb'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Flux_Feedback_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_Id_ro;                          //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Id_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_Iq_ro;                          //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Iq_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#else

  int16_t D1_Flux_Command_ro;                //  [-] Bits=16 Factor= 0.001000        Unit:'Wb'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Flux_Command_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Flux_Feedback_ro;               //  [-] Bits=16 Factor= 0.001000        Unit:'Wb'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Flux_Feedback_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_Id_ro;                          //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Id_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_Iq_ro;                          //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Iq_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M168_Flux_ID_IQ_Info_t;

// def @M169_Internal_Voltages CAN Message (169  0xa9)
#define M169_Internal_Voltages_IDE (0U)
#define M169_Internal_Voltages_DLC (8U)
#define M169_Internal_Voltages_CANID (0xa9)
#define M169_Internal_Voltages_CYC (100U)
// signal: @D1_Reference_Voltage_1_5_ro
#define BEV_DBC_D1_Reference_Voltage_1_5_ro_CovFactor (0.010000)
#define BEV_DBC_D1_Reference_Voltage_1_5_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.010000)) )
#define BEV_DBC_D1_Reference_Voltage_1_5_ro_fromS(x) ( (((x) * (0.010000)) + (0.000000)) )
// signal: @D2_Reference_Voltage_2_5_ro
#define BEV_DBC_D2_Reference_Voltage_2_5_ro_CovFactor (0.010000)
#define BEV_DBC_D2_Reference_Voltage_2_5_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.010000)) )
#define BEV_DBC_D2_Reference_Voltage_2_5_ro_fromS(x) ( (((x) * (0.010000)) + (0.000000)) )
// signal: @D3_Reference_Voltage_5_0_ro
#define BEV_DBC_D3_Reference_Voltage_5_0_ro_CovFactor (0.010000)
#define BEV_DBC_D3_Reference_Voltage_5_0_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.010000)) )
#define BEV_DBC_D3_Reference_Voltage_5_0_ro_fromS(x) ( (((x) * (0.010000)) + (0.000000)) )
// signal: @D4_Reference_Voltage_12_0_ro
#define BEV_DBC_D4_Reference_Voltage_12_0_ro_CovFactor (0.010000)
#define BEV_DBC_D4_Reference_Voltage_12_0_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.010000)) )
#define BEV_DBC_D4_Reference_Voltage_12_0_ro_fromS(x) ( (((x) * (0.010000)) + (0.000000)) )

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  int16_t D1_Reference_Voltage_1_5_ro;        //  [-] Bits=16 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Reference_Voltage_1_5_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Reference_Voltage_2_5_ro;        //  [-] Bits=16 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Reference_Voltage_2_5_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_Reference_Voltage_5_0_ro;        //  [-] Bits=16 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Reference_Voltage_5_0_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_Reference_Voltage_12_0_ro;       //  [-] Bits=16 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Reference_Voltage_12_0_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#else

  int16_t D1_Reference_Voltage_1_5_ro;        //  [-] Bits=16 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Reference_Voltage_1_5_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Reference_Voltage_2_5_ro;        //  [-] Bits=16 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Reference_Voltage_2_5_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_Reference_Voltage_5_0_ro;        //  [-] Bits=16 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Reference_Voltage_5_0_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_Reference_Voltage_12_0_ro;       //  [-] Bits=16 Factor= 0.010000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Reference_Voltage_12_0_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M169_Internal_Voltages_t;

// def @M170_Internal_States CAN Message (170  0xaa)
#define M170_Internal_States_IDE (0U)
#define M170_Internal_States_DLC (8U)
#define M170_Internal_States_CANID (0xaa)
#define M170_Internal_States_CYC (100U)

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  // Different states for the vehicle state machine
  //  0 : "VSM Start State"
  //  1 : "Pre-Charge Init state"
  //  2 : "pre-charge active state"
  //  3 : "pre-charge complete state"
  //  4 : "VSM wait state"
  //  5 : "VSM ready state"
  //  6 : "Motor Running State"
  //  7 : "blink fault code state"
  //  14 : "Shutdown state for Key Switch Mode 1"
  //  15 : "Reset the inverter"
  uint8_t D1_VSM_State;                      //      Bits= 8

  // The inverter PWM frequency
  uint8_t D1_PWM_Frequency;                  //      Bits= 8 Unit:'kHz'

  // Different states for the inverter state machine
  //  0 : "Power up"
  //  1 : "Stop"
  //  2 : "Open Loop"
  //  3 : "Closed Loop"
  //  4 : "Internal State"
  //  5 : "Internal State"
  //  6 : "Internal State"
  //  7 : "Internal State"
  //  8 : "Idle Run"
  //  9 : "Idle Stop"
  //  10 : "Internal State"
  //  11 : "Intern State"
  //  12 : "Internal State"
  uint8_t D2_Inverter_State;                 //      Bits= 8

  // 0=OFF, 1=ON
  uint8_t D3_Relay_1_Status : 1;             //      Bits= 1

  // 0=OFF, 1=ON
  uint8_t D3_Relay_2_Status : 1;             //      Bits= 1

  // 0=OFF, 1=ON
  uint8_t D3_Relay_3_Status : 1;             //      Bits= 1

  // 0=OFF, 1=ON
  uint8_t D3_Relay_4_Status : 1;             //      Bits= 1

  // 0=OFF, 1=ON
  uint8_t D3_Relay_5_Status : 1;             //      Bits= 1

  // 0=OFF, 1=ON
  uint8_t D3_Relay_6_Status : 1;             //      Bits= 1

  // 0=Torque Mode, 1=Speed Mode
  uint8_t D4_Inverter_Run_Mode : 1;          //      Bits= 1

  // 0 = Disabled, 1 = Enabled, 2 = Speed Check, 3 = Active, 4 = Complete
  uint8_t D4_Inverter_Discharge_State : 3;   //      Bits= 3

  // 0=CAN mode, 1=VSM mode
  uint8_t D5_Inverter_Command_Mode : 1;      //      Bits= 1

  // The current rolling counter value.
  uint8_t D5_Rolling_Counter : 4;            //      Bits= 4

  // 0=Inverter Disabled,
  // 1=Inverter Enabled
  uint8_t D6_Inverter_Enable_State : 1;      //      Bits= 1

  // If in Key Switch Mode 1 then indicates status of Start input being applied.  0 = not active, 1 = active
  uint8_t D6_Start_Mode_Active : 1;          //      Bits= 1

  // 0=Lockout Disabled, 1=Lockout Enabled
  uint8_t D6_Inverter_Enable_Lockout : 1;    //      Bits= 1

  // 1 = Forward
  // 0 = 'Reverse' if inverter enabled  & 'Stopped' if inverter is disabled
  uint8_t D7_Direction_Command : 1;          //      Bits= 1

  // 0 = BMS Not Active, 1 = BMS Active
  uint8_t D7_BMS_Active : 1;                 //      Bits= 1

  // 0 = Not Limiting, 1 = Limiting
  uint8_t D7_BMS_Torque_Limiting : 1;        //      Bits= 1

  // 0 = Not Limiting, 1 = torque limiting due to maximum speed
  uint8_t D7_Max_Speed_Limiting : 1;         //      Bits= 1

  // 0 = Not Limiting, 1 = Current limiting due to low motor speed
  uint8_t D7_Low_Speed_Limiting : 1;         //      Bits= 1

#else

  // Different states for the vehicle state machine
  //  0 : "VSM Start State"
  //  1 : "Pre-Charge Init state"
  //  2 : "pre-charge active state"
  //  3 : "pre-charge complete state"
  //  4 : "VSM wait state"
  //  5 : "VSM ready state"
  //  6 : "Motor Running State"
  //  7 : "blink fault code state"
  //  14 : "Shutdown state for Key Switch Mode 1"
  //  15 : "Reset the inverter"
  uint8_t D1_VSM_State;                      //      Bits= 8

  // The inverter PWM frequency
  uint8_t D1_PWM_Frequency;                  //      Bits= 8 Unit:'kHz'

  // Different states for the inverter state machine
  //  0 : "Power up"
  //  1 : "Stop"
  //  2 : "Open Loop"
  //  3 : "Closed Loop"
  //  4 : "Internal State"
  //  5 : "Internal State"
  //  6 : "Internal State"
  //  7 : "Internal State"
  //  8 : "Idle Run"
  //  9 : "Idle Stop"
  //  10 : "Internal State"
  //  11 : "Intern State"
  //  12 : "Internal State"
  uint8_t D2_Inverter_State;                 //      Bits= 8

  // 0=OFF, 1=ON
  uint8_t D3_Relay_1_Status;                 //      Bits= 1

  // 0=OFF, 1=ON
  uint8_t D3_Relay_2_Status;                 //      Bits= 1

  // 0=OFF, 1=ON
  uint8_t D3_Relay_3_Status;                 //      Bits= 1

  // 0=OFF, 1=ON
  uint8_t D3_Relay_4_Status;                 //      Bits= 1

  // 0=OFF, 1=ON
  uint8_t D3_Relay_5_Status;                 //      Bits= 1

  // 0=OFF, 1=ON
  uint8_t D3_Relay_6_Status;                 //      Bits= 1

  // 0=Torque Mode, 1=Speed Mode
  uint8_t D4_Inverter_Run_Mode;              //      Bits= 1

  // 0 = Disabled, 1 = Enabled, 2 = Speed Check, 3 = Active, 4 = Complete
  uint8_t D4_Inverter_Discharge_State;       //      Bits= 3

  // 0=CAN mode, 1=VSM mode
  uint8_t D5_Inverter_Command_Mode;          //      Bits= 1

  // The current rolling counter value.
  uint8_t D5_Rolling_Counter;                //      Bits= 4

  // 0=Inverter Disabled,
  // 1=Inverter Enabled
  uint8_t D6_Inverter_Enable_State;          //      Bits= 1

  // If in Key Switch Mode 1 then indicates status of Start input being applied.  0 = not active, 1 = active
  uint8_t D6_Start_Mode_Active;              //      Bits= 1

  // 0=Lockout Disabled, 1=Lockout Enabled
  uint8_t D6_Inverter_Enable_Lockout;        //      Bits= 1

  // 1 = Forward
  // 0 = 'Reverse' if inverter enabled  & 'Stopped' if inverter is disabled
  uint8_t D7_Direction_Command;              //      Bits= 1

  // 0 = BMS Not Active, 1 = BMS Active
  uint8_t D7_BMS_Active;                     //      Bits= 1

  // 0 = Not Limiting, 1 = Limiting
  uint8_t D7_BMS_Torque_Limiting;            //      Bits= 1

  // 0 = Not Limiting, 1 = torque limiting due to maximum speed
  uint8_t D7_Max_Speed_Limiting;             //      Bits= 1

  // 0 = Not Limiting, 1 = Current limiting due to low motor speed
  uint8_t D7_Low_Speed_Limiting;             //      Bits= 1

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M170_Internal_States_t;

// def @M171_Fault_Codes CAN Message (171  0xab)
#define M171_Fault_Codes_IDE (0U)
#define M171_Fault_Codes_DLC (8U)
#define M171_Fault_Codes_CANID (0xab)
#define M171_Fault_Codes_CYC (100U)

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  // Each bit represents a fault. Please refer to PM100 Users Manual for details.
  uint16_t D1_Post_Fault_Lo;                 //      Bits=16

  // Each bit represents a fault. Please refer to PM100 Users Manual for details.
  uint16_t D2_Post_Fault_Hi;                 //      Bits=16

  // Each bit represents a fault. Please refer to PM100 Users Manual for details.
  uint16_t D3_Run_Fault_Lo;                  //      Bits=16

  // Each bit represents a fault. Please refer to PM100 Users Manual for details.
  uint16_t D4_Run_Fault_Hi;                  //      Bits=16

#else

  // Each bit represents a fault. Please refer to PM100 Users Manual for details.
  uint16_t D1_Post_Fault_Lo;                 //      Bits=16

  // Each bit represents a fault. Please refer to PM100 Users Manual for details.
  uint16_t D2_Post_Fault_Hi;                 //      Bits=16

  // Each bit represents a fault. Please refer to PM100 Users Manual for details.
  uint16_t D3_Run_Fault_Lo;                  //      Bits=16

  // Each bit represents a fault. Please refer to PM100 Users Manual for details.
  uint16_t D4_Run_Fault_Hi;                  //      Bits=16

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M171_Fault_Codes_t;

// def @M172_Torque_And_Timer_Info CAN Message (172  0xac)
#define M172_Torque_And_Timer_Info_IDE (0U)
#define M172_Torque_And_Timer_Info_DLC (8U)
#define M172_Torque_And_Timer_Info_CANID (0xac)
#define M172_Torque_And_Timer_Info_CYC (10U)
// signal: @D1_Commanded_Torque_ro
#define BEV_DBC_D1_Commanded_Torque_ro_CovFactor (0.100000)
#define BEV_DBC_D1_Commanded_Torque_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D1_Commanded_Torque_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D2_Torque_Feedback_ro
#define BEV_DBC_D2_Torque_Feedback_ro_CovFactor (0.100000)
#define BEV_DBC_D2_Torque_Feedback_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D2_Torque_Feedback_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D3_Power_On_Timer_ro
#define BEV_DBC_D3_Power_On_Timer_ro_CovFactor (0.003000)
#define BEV_DBC_D3_Power_On_Timer_ro_toS(x) ( (uint32_t) (((x) - (0.000000)) / (0.003000)) )
#define BEV_DBC_D3_Power_On_Timer_ro_fromS(x) ( (((x) * (0.003000)) + (0.000000)) )

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  int16_t D1_Commanded_Torque_ro;            //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Commanded_Torque_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Torque_Feedback_ro;             //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Torque_Feedback_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  uint32_t D3_Power_On_Timer_ro;             //      Bits=32 Factor= 0.003000        Unit:'Sec'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Power_On_Timer_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#else

  int16_t D1_Commanded_Torque_ro;            //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Commanded_Torque_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Torque_Feedback_ro;             //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Torque_Feedback_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  uint32_t D3_Power_On_Timer_ro;             //      Bits=32 Factor= 0.003000        Unit:'Sec'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Power_On_Timer_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M172_Torque_And_Timer_Info_t;

// def @M173_Modulation_And_Flux_Info CAN Message (173  0xad)
#define M173_Modulation_And_Flux_Info_IDE (0U)
#define M173_Modulation_And_Flux_Info_DLC (8U)
#define M173_Modulation_And_Flux_Info_CANID (0xad)
// signal: @D1_Modulation_Index_ro
#define BEV_DBC_D1_Modulation_Index_ro_CovFactor (0.000100)
#define BEV_DBC_D1_Modulation_Index_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.000100)) )
#define BEV_DBC_D1_Modulation_Index_ro_fromS(x) ( (((x) * (0.000100)) + (0.000000)) )
// signal: @D2_Flux_Weakening_Output_ro
#define BEV_DBC_D2_Flux_Weakening_Output_ro_CovFactor (0.100000)
#define BEV_DBC_D2_Flux_Weakening_Output_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D2_Flux_Weakening_Output_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D3_Id_Command_ro
#define BEV_DBC_D3_Id_Command_ro_CovFactor (0.100000)
#define BEV_DBC_D3_Id_Command_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D3_Id_Command_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @D4_Iq_Command_ro
#define BEV_DBC_D4_Iq_Command_ro_CovFactor (0.100000)
#define BEV_DBC_D4_Iq_Command_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_D4_Iq_Command_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  int16_t D1_Modulation_Index_ro;            //  [-] Bits=16 Factor= 0.000100       

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Modulation_Index_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Flux_Weakening_Output_ro;       //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Flux_Weakening_Output_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_Id_Command_ro;                  //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Id_Command_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_Iq_Command_ro;                  //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Iq_Command_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#else

  int16_t D1_Modulation_Index_ro;            //  [-] Bits=16 Factor= 0.000100       

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D1_Modulation_Index_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D2_Flux_Weakening_Output_ro;       //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D2_Flux_Weakening_Output_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D3_Id_Command_ro;                  //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D3_Id_Command_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t D4_Iq_Command_ro;                  //  [-] Bits=16 Factor= 0.100000        Unit:'A'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t D4_Iq_Command_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M173_Modulation_And_Flux_Info_t;

// def @M174_Firmware_Info CAN Message (174  0xae)
#define M174_Firmware_Info_IDE (0U)
#define M174_Firmware_Info_DLC (8U)
#define M174_Firmware_Info_CANID (0xae)

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  uint16_t D1_Project_Code_EEP_Ver;          //      Bits=16

  uint16_t D2_SW_Version;                    //      Bits=16

  uint16_t D3_DateCode_MMDD;                 //      Bits=16

  uint16_t D4_DateCode_YYYY;                 //      Bits=16

#else

  uint16_t D1_Project_Code_EEP_Ver;          //      Bits=16

  uint16_t D2_SW_Version;                    //      Bits=16

  uint16_t D3_DateCode_MMDD;                 //      Bits=16

  uint16_t D4_DateCode_YYYY;                 //      Bits=16

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M174_Firmware_Info_t;

// def @M175_Diag_Data CAN Message (175  0xaf)
#define M175_Diag_Data_IDE (0U)
#define M175_Diag_Data_DLC (8U)
#define M175_Diag_Data_CANID (0xaf)

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  uint8_t D1_Buffer_Record;                  //      Bits= 8

  uint8_t D2_Buffer_Segment;                 //      Bits= 8

  int16_t D3_Diag_Data_1;                    //  [-] Bits=16

  int16_t D4_Diag_Data_2;                    //  [-] Bits=16

  int16_t D5_Diag_Data_3;                    //  [-] Bits=16

#else

  uint8_t D1_Buffer_Record;                  //      Bits= 8

  uint8_t D2_Buffer_Segment;                 //      Bits= 8

  int16_t D3_Diag_Data_1;                    //  [-] Bits=16

  int16_t D4_Diag_Data_2;                    //  [-] Bits=16

  int16_t D5_Diag_Data_3;                    //  [-] Bits=16

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M175_Diag_Data_t;

// To enable fast message set CAN ACTIVE MSGS HI WORD to 0xFFFE.  Setting to default value of 0xFFFF will disable the fast message.
// def @M176_Fast_Info CAN Message (176  0xb0)
#define M176_Fast_Info_IDE (0U)
#define M176_Fast_Info_DLC (8U)
#define M176_Fast_Info_CANID (0xb0)
#define M176_Fast_Info_CYC (3U)
// signal: @Fast_Torque_Command_ro
#define BEV_DBC_Fast_Torque_Command_ro_CovFactor (0.100000)
#define BEV_DBC_Fast_Torque_Command_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_Fast_Torque_Command_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @Fast_Torque_Feedback_ro
#define BEV_DBC_Fast_Torque_Feedback_ro_CovFactor (0.100000)
#define BEV_DBC_Fast_Torque_Feedback_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_Fast_Torque_Feedback_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @Fast_DC_Bus_Voltage_ro
#define BEV_DBC_Fast_DC_Bus_Voltage_ro_CovFactor (0.100000)
#define BEV_DBC_Fast_DC_Bus_Voltage_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_Fast_DC_Bus_Voltage_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  int16_t Fast_Torque_Command_ro;            //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t Fast_Torque_Command_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t Fast_Torque_Feedback_ro;           //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t Fast_Torque_Feedback_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  // Motor speed
  int16_t Fast_Motor_Speed;                  //  [-] Bits=16 Unit:'rpm'

  int16_t Fast_DC_Bus_Voltage_ro;            //  [-] Bits=16 Factor= 0.100000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t Fast_DC_Bus_Voltage_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#else

  int16_t Fast_Torque_Command_ro;            //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t Fast_Torque_Command_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  int16_t Fast_Torque_Feedback_ro;           //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t Fast_Torque_Feedback_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  // Motor speed
  int16_t Fast_Motor_Speed;                  //  [-] Bits=16 Unit:'rpm'

  int16_t Fast_DC_Bus_Voltage_ro;            //  [-] Bits=16 Factor= 0.100000        Unit:'V'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t Fast_DC_Bus_Voltage_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M176_Fast_Info_t;

// The command message is used to transmit data to the controller. This message is sent from a user supplied external controller to the PMxxx controller.
// def @M192_Command_Message CAN Message (192  0xc0)
#define M192_Command_Message_IDE (0U)
#define M192_Command_Message_DLC (8U)
#define M192_Command_Message_CANID (0xc0)
#define M192_Command_Message_CYC (5U)
// signal: @Torque_Command_ro
#define BEV_DBC_Torque_Command_ro_CovFactor (0.100000)
#define BEV_DBC_Torque_Command_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_Torque_Command_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )
// signal: @Torque_Limit_Command_ro
#define BEV_DBC_Torque_Limit_Command_ro_CovFactor (0.100000)
#define BEV_DBC_Torque_Limit_Command_ro_toS(x) ( (int16_t) (((x) - (0.000000)) / (0.100000)) )
#define BEV_DBC_Torque_Limit_Command_ro_fromS(x) ( (((x) * (0.100000)) + (0.000000)) )

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  int16_t Torque_Command_ro;                 //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t Torque_Command_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  // Speed commandused when in speed mode
  int16_t Speed_Command;                     //  [-] Bits=16 Unit:'rpm'

  // 0=CW, 1=CCW as veiwed from the shaft end of the motor
  //  0 : "CW"
  //  1 : "CCW"
  uint8_t Direction_Command : 1;             //      Bits= 1 Unit:'Bit'

  // 0=Inverter OFF, 1 = Inverter ON
  //  0 : "Turn the inverter OFF"
  //  1 : "Turn the Inverter ON"
  uint8_t Inverter_Enable : 1;               //      Bits= 1 Unit:'Bit'

  // 0=Discharge Disable,
  // =Discharge Enable
  //  0 : "Discharge Disable"
  //  1 : "Discharge Enable (if EEPROM parameter is set)"
  uint8_t Inverter_Discharge : 1;            //      Bits= 1 Unit:'Bit'

  // 0 = No change to mode, 1 = change to speed mode from torque mode
  uint8_t Speed_Mode_Enable : 1;             //      Bits= 1 Unit:'Bit'

  // Rolling Counter command
  uint8_t RollingCounter : 4;                //      Bits= 4 Unit:'Bits'

  int16_t Torque_Limit_Command_ro;           //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t Torque_Limit_Command_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#else

  int16_t Torque_Command_ro;                 //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t Torque_Command_phys;
#endif // BEV_DBC_USE_SIGFLOAT

  // Speed commandused when in speed mode
  int16_t Speed_Command;                     //  [-] Bits=16 Unit:'rpm'

  // 0=CW, 1=CCW as veiwed from the shaft end of the motor
  //  0 : "CW"
  //  1 : "CCW"
  uint8_t Direction_Command;                 //      Bits= 1 Unit:'Bit'

  // 0=Inverter OFF, 1 = Inverter ON
  //  0 : "Turn the inverter OFF"
  //  1 : "Turn the Inverter ON"
  uint8_t Inverter_Enable;                   //      Bits= 1 Unit:'Bit'

  // 0=Discharge Disable,
  // =Discharge Enable
  //  0 : "Discharge Disable"
  //  1 : "Discharge Enable (if EEPROM parameter is set)"
  uint8_t Inverter_Discharge;                //      Bits= 1 Unit:'Bit'

  // 0 = No change to mode, 1 = change to speed mode from torque mode
  uint8_t Speed_Mode_Enable;                 //      Bits= 1 Unit:'Bit'

  // Rolling Counter command
  uint8_t RollingCounter;                    //      Bits= 4 Unit:'Bits'

  int16_t Torque_Limit_Command_ro;           //  [-] Bits=16 Factor= 0.100000        Unit:'Nm'

#ifdef BEV_DBC_USE_SIGFLOAT
  sigfloat_t Torque_Limit_Command_phys;
#endif // BEV_DBC_USE_SIGFLOAT

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M192_Command_Message_t;

// Parameter Message sent as needed by VCU to request info, change EEPROM, or command a function.
// def @M193_Read_Write_Param_Command CAN Message (193  0xc1)
#define M193_Read_Write_Param_Command_IDE (0U)
#define M193_Read_Write_Param_Command_DLC (8U)
#define M193_Read_Write_Param_Command_CANID (0xc1)

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  // Valid EEPROM Parameter CAN addresses are between 100 and 499.
  uint16_t D1_Parameter_Address_Command;      //      Bits=16

  // 0=Read, 1=Write
  uint8_t D2_Read_Write_Command : 1;          //      Bits= 1

  // All EEPROM data is 16 bits and is contained in bytes 4 and 5.
  int16_t D3_Data_Command;                    //  [-] Bits=16

#else

  // Valid EEPROM Parameter CAN addresses are between 100 and 499.
  uint16_t D1_Parameter_Address_Command;      //      Bits=16

  // 0=Read, 1=Write
  uint8_t D2_Read_Write_Command;              //      Bits= 1

  // All EEPROM data is 16 bits and is contained in bytes 4 and 5.
  int16_t D3_Data_Command;                    //  [-] Bits=16

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M193_Read_Write_Param_Command_t;

// The inverter response to each Parameter message that is received.
// def @M194_Read_Write_Param_Response CAN Message (194  0xc2)
#define M194_Read_Write_Param_Response_IDE (0U)
#define M194_Read_Write_Param_Response_DLC (8U)
#define M194_Read_Write_Param_Response_CANID (0xc2)

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  // Valid EEPROM Parameter CAN addresses are between 100 and 499.
  uint16_t D1_Parameter_Address_Response;      //      Bits=16

  // 0=Write failure, 1=Success
  uint8_t D2_Write_Success : 1;                //      Bits= 1

  // All EEPROM data is 16 bits and is contained in bytes 4 and 5. Bytes 6 and 7 should be ignored.
  int16_t D3_Data_Response;                    //  [-] Bits=16

#else

  // Valid EEPROM Parameter CAN addresses are between 100 and 499.
  uint16_t D1_Parameter_Address_Response;      //      Bits=16

  // 0=Write failure, 1=Success
  uint8_t D2_Write_Success;                    //      Bits= 1

  // All EEPROM data is 16 bits and is contained in bytes 4 and 5. Bytes 6 and 7 should be ignored.
  int16_t D3_Data_Response;                    //  [-] Bits=16

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M194_Read_Write_Param_Response_t;

// Response from Delphi DC/DC converter.
// def @M188_U2C_Message_Rxd CAN Message (469  0x1d5)
#define M188_U2C_Message_Rxd_IDE (0U)
#define M188_U2C_Message_Rxd_DLC (8U)
#define M188_U2C_Message_Rxd_CANID (0x1d5)

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  uint8_t D1_HV_Input_Current_Sensor_Validity : 1;   //      Bits= 1

  uint8_t D2_14V_Master_Fault : 1;                   //      Bits= 1

  uint8_t D3_HV_Input_Current;                       //      Bits= 8

  uint8_t D4_DTC_Status : 3;                         //      Bits= 3

  uint8_t D5_DTC_Index : 5;                          //      Bits= 5

  uint8_t D6_14V_Monitor;                            //      Bits= 8

  uint8_t D7_14V_Conditional : 1;                    //      Bits= 1

  uint8_t D8_14V_Current_Monitor : 7;                //      Bits= 7

#else

  uint8_t D1_HV_Input_Current_Sensor_Validity;       //      Bits= 1

  uint8_t D2_14V_Master_Fault;                       //      Bits= 1

  uint8_t D3_HV_Input_Current;                       //      Bits= 8

  uint8_t D4_DTC_Status;                             //      Bits= 3

  uint8_t D5_DTC_Index;                              //      Bits= 5

  uint8_t D6_14V_Monitor;                            //      Bits= 8

  uint8_t D7_14V_Conditional;                        //      Bits= 1

  uint8_t D8_14V_Current_Monitor;                    //      Bits= 7

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M188_U2C_Message_Rxd_t;

// Enable message sent to Delphi DC/DC converter.
// def @M187_U2C_Command_Txd CAN Message (471  0x1d7)
#define M187_U2C_Command_Txd_IDE (0U)
#define M187_U2C_Command_Txd_DLC (8U)
#define M187_U2C_Command_Txd_CANID (0x1d7)

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  uint8_t D1_ID_Byte;                        //      Bits= 8

  uint8_t D2_Setpoint_Calc;                  //      Bits= 8

#else

  uint8_t D1_ID_Byte;                        //      Bits= 8

  uint8_t D2_Setpoint_Calc;                  //      Bits= 8

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} M187_U2C_Command_Txd_t;

// Message sent by BMS for inverter DC current limiting.
// def @BMS_Current_Limit CAN Message (514  0x202)
#define BMS_Current_Limit_IDE (0U)
#define BMS_Current_Limit_DLC (8U)
#define BMS_Current_Limit_CANID (0x202)

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  // Maximum discharge current from BMS
  uint16_t D1_Max_Discharge_Current;         //      Bits=16 Unit:'A'

  // Maximum charge current from BMS
  uint16_t D2_Max_Charge_Current;            //      Bits=16 Unit:'A'

#else

  // Maximum discharge current from BMS
  uint16_t D1_Max_Discharge_Current;         //      Bits=16 Unit:'A'

  // Maximum charge current from BMS
  uint16_t D2_Max_Charge_Current;            //      Bits=16 Unit:'A'

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} BMS_Current_Limit_t;

// def @BMS_Msg1 CAN Message (1713 0x6b1)
#define BMS_Msg1_IDE (0U)
#define BMS_Msg1_DLC (8U)
#define BMS_Msg1_CANID (0x6b1)

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  // Pack State of Charge
  uint8_t SOC;                               //      Bits= 8 Unit:'%'

  // Pack Discharge Current Limit
  uint8_t DCL;                               //      Bits= 8 Unit:'A'

  // Pack Charge Current Limit
  uint8_t CCL;                               //      Bits= 8 Unit:'A'

  uint8_t Internal_Temperature;              //      Bits= 8 Unit:'C'

  uint8_t Highest_Cell_Voltage;              //      Bits= 8 Unit:'V'

  uint8_t Pack_Current;                      //      Bits= 8 Unit:'A'

  uint8_t Populated_Cells;                   //      Bits= 8

  uint8_t Checksum;                          //      Bits= 8

#else

  // Pack State of Charge
  uint8_t SOC;                               //      Bits= 8 Unit:'%'

  // Pack Discharge Current Limit
  uint8_t DCL;                               //      Bits= 8 Unit:'A'

  // Pack Charge Current Limit
  uint8_t CCL;                               //      Bits= 8 Unit:'A'

  uint8_t Internal_Temperature;              //      Bits= 8 Unit:'C'

  uint8_t Highest_Cell_Voltage;              //      Bits= 8 Unit:'V'

  uint8_t Pack_Current;                      //      Bits= 8 Unit:'A'

  uint8_t Populated_Cells;                   //      Bits= 8

  uint8_t Checksum;                          //      Bits= 8

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} BMS_Msg1_t;

// For all the values in the signals in the message, 1 signifies the signal or relay is enabled or active (high). 0 means inactive or off (low).
// def @BMS_Faults1 CAN Message (1714 0x6b2)
#define BMS_Faults1_IDE (0U)
#define BMS_Faults1_DLC (8U)
#define BMS_Faults1_CANID (0x6b2)

typedef struct
{
#ifdef BEV_DBC_USE_BITS_SIGNAL

  uint16_t DTCStatus1;                       //      Bits=16

  uint16_t DTCStatus2;                       //      Bits=16

#else

  uint16_t DTCStatus1;                       //      Bits=16

  uint16_t DTCStatus2;                       //      Bits=16

#endif // BEV_DBC_USE_BITS_SIGNAL

#ifdef BEV_DBC_USE_DIAG_MONITORS

  FrameMonitor_t mon1;

#endif // BEV_DBC_USE_DIAG_MONITORS

} BMS_Faults1_t;

// Function signatures

uint32_t Unpack_M160_Temperature_Set_1_bev_dbc(M160_Temperature_Set_1_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M160_Temperature_Set_1_bev_dbc(M160_Temperature_Set_1_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M160_Temperature_Set_1_bev_dbc(M160_Temperature_Set_1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M161_Temperature_Set_2_bev_dbc(M161_Temperature_Set_2_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M161_Temperature_Set_2_bev_dbc(M161_Temperature_Set_2_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M161_Temperature_Set_2_bev_dbc(M161_Temperature_Set_2_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M162_Temperature_Set_3_bev_dbc(M162_Temperature_Set_3_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M162_Temperature_Set_3_bev_dbc(M162_Temperature_Set_3_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M162_Temperature_Set_3_bev_dbc(M162_Temperature_Set_3_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M163_Analog_Input_Voltages_bev_dbc(M163_Analog_Input_Voltages_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M163_Analog_Input_Voltages_bev_dbc(M163_Analog_Input_Voltages_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M163_Analog_Input_Voltages_bev_dbc(M163_Analog_Input_Voltages_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M164_Digital_Input_Status_bev_dbc(M164_Digital_Input_Status_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M164_Digital_Input_Status_bev_dbc(M164_Digital_Input_Status_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M164_Digital_Input_Status_bev_dbc(M164_Digital_Input_Status_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M165_Motor_Position_Info_bev_dbc(M165_Motor_Position_Info_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M165_Motor_Position_Info_bev_dbc(M165_Motor_Position_Info_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M165_Motor_Position_Info_bev_dbc(M165_Motor_Position_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M166_Current_Info_bev_dbc(M166_Current_Info_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M166_Current_Info_bev_dbc(M166_Current_Info_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M166_Current_Info_bev_dbc(M166_Current_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M167_Voltage_Info_bev_dbc(M167_Voltage_Info_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M167_Voltage_Info_bev_dbc(M167_Voltage_Info_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M167_Voltage_Info_bev_dbc(M167_Voltage_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M168_Flux_ID_IQ_Info_bev_dbc(M168_Flux_ID_IQ_Info_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M168_Flux_ID_IQ_Info_bev_dbc(M168_Flux_ID_IQ_Info_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M168_Flux_ID_IQ_Info_bev_dbc(M168_Flux_ID_IQ_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M169_Internal_Voltages_bev_dbc(M169_Internal_Voltages_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M169_Internal_Voltages_bev_dbc(M169_Internal_Voltages_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M169_Internal_Voltages_bev_dbc(M169_Internal_Voltages_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M170_Internal_States_bev_dbc(M170_Internal_States_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M170_Internal_States_bev_dbc(M170_Internal_States_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M170_Internal_States_bev_dbc(M170_Internal_States_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M171_Fault_Codes_bev_dbc(M171_Fault_Codes_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M171_Fault_Codes_bev_dbc(M171_Fault_Codes_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M171_Fault_Codes_bev_dbc(M171_Fault_Codes_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M172_Torque_And_Timer_Info_bev_dbc(M172_Torque_And_Timer_Info_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M172_Torque_And_Timer_Info_bev_dbc(M172_Torque_And_Timer_Info_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M172_Torque_And_Timer_Info_bev_dbc(M172_Torque_And_Timer_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M173_Modulation_And_Flux_Info_bev_dbc(M173_Modulation_And_Flux_Info_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M173_Modulation_And_Flux_Info_bev_dbc(M173_Modulation_And_Flux_Info_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M173_Modulation_And_Flux_Info_bev_dbc(M173_Modulation_And_Flux_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M174_Firmware_Info_bev_dbc(M174_Firmware_Info_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M174_Firmware_Info_bev_dbc(M174_Firmware_Info_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M174_Firmware_Info_bev_dbc(M174_Firmware_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M175_Diag_Data_bev_dbc(M175_Diag_Data_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M175_Diag_Data_bev_dbc(M175_Diag_Data_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M175_Diag_Data_bev_dbc(M175_Diag_Data_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M176_Fast_Info_bev_dbc(M176_Fast_Info_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M176_Fast_Info_bev_dbc(M176_Fast_Info_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M176_Fast_Info_bev_dbc(M176_Fast_Info_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M192_Command_Message_bev_dbc(M192_Command_Message_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M192_Command_Message_bev_dbc(M192_Command_Message_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M192_Command_Message_bev_dbc(M192_Command_Message_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M193_Read_Write_Param_Command_bev_dbc(M193_Read_Write_Param_Command_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M193_Read_Write_Param_Command_bev_dbc(M193_Read_Write_Param_Command_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M193_Read_Write_Param_Command_bev_dbc(M193_Read_Write_Param_Command_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M194_Read_Write_Param_Response_bev_dbc(M194_Read_Write_Param_Response_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M194_Read_Write_Param_Response_bev_dbc(M194_Read_Write_Param_Response_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M194_Read_Write_Param_Response_bev_dbc(M194_Read_Write_Param_Response_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M188_U2C_Message_Rxd_bev_dbc(M188_U2C_Message_Rxd_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M188_U2C_Message_Rxd_bev_dbc(M188_U2C_Message_Rxd_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M188_U2C_Message_Rxd_bev_dbc(M188_U2C_Message_Rxd_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_M187_U2C_Command_Txd_bev_dbc(M187_U2C_Command_Txd_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_M187_U2C_Command_Txd_bev_dbc(M187_U2C_Command_Txd_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_M187_U2C_Command_Txd_bev_dbc(M187_U2C_Command_Txd_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_BMS_Current_Limit_bev_dbc(BMS_Current_Limit_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_BMS_Current_Limit_bev_dbc(BMS_Current_Limit_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_BMS_Current_Limit_bev_dbc(BMS_Current_Limit_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_BMS_Msg1_bev_dbc(BMS_Msg1_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_BMS_Msg1_bev_dbc(BMS_Msg1_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_BMS_Msg1_bev_dbc(BMS_Msg1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

uint32_t Unpack_BMS_Faults1_bev_dbc(BMS_Faults1_t* _m, const uint8_t* _d, uint8_t dlc_);
#ifdef BEV_DBC_USE_CANSTRUCT
uint32_t Pack_BMS_Faults1_bev_dbc(BMS_Faults1_t* _m, __CoderDbcCanFrame_t__* cframe);
#else
uint32_t Pack_BMS_Faults1_bev_dbc(BMS_Faults1_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide);
#endif // BEV_DBC_USE_CANSTRUCT

#ifdef __cplusplus
}
#endif
