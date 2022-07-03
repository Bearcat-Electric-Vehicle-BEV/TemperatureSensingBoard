#include "bev_dbc-binutil.h"

#ifdef __DEF_BEV_DBC__

bev_dbc_rx_t bev_dbc_rx;

#endif // __DEF_BEV_DBC__

uint32_t bev_dbc_Receive(bev_dbc_rx_t* _m, const uint8_t* _d, uint32_t _id, uint8_t dlc_)
{
 uint32_t recid = 0;
 if ((_id >= 0xA0U) && (_id < 0xACU)) {
  if ((_id >= 0xA0U) && (_id < 0xA6U)) {
   if ((_id >= 0xA0U) && (_id < 0xA3U)) {
    if (_id == 0xA0U) {
     recid = Unpack_M160_Temperature_Set_1_bev_dbc(&(_m->M160_Temperature_Set_1), _d, dlc_);
    } else {
     if (_id == 0xA1U) {
      recid = Unpack_M161_Temperature_Set_2_bev_dbc(&(_m->M161_Temperature_Set_2), _d, dlc_);
     } else if (_id == 0xA2U) {
      recid = Unpack_M162_Temperature_Set_3_bev_dbc(&(_m->M162_Temperature_Set_3), _d, dlc_);
     }
    }
   } else {
    if (_id == 0xA3U) {
     recid = Unpack_M163_Analog_Input_Voltages_bev_dbc(&(_m->M163_Analog_Input_Voltages), _d, dlc_);
    } else {
     if (_id == 0xA4U) {
      recid = Unpack_M164_Digital_Input_Status_bev_dbc(&(_m->M164_Digital_Input_Status), _d, dlc_);
     } else if (_id == 0xA5U) {
      recid = Unpack_M165_Motor_Position_Info_bev_dbc(&(_m->M165_Motor_Position_Info), _d, dlc_);
     }
    }
   }
  } else {
   if ((_id >= 0xA6U) && (_id < 0xA9U)) {
    if (_id == 0xA6U) {
     recid = Unpack_M166_Current_Info_bev_dbc(&(_m->M166_Current_Info), _d, dlc_);
    } else {
     if (_id == 0xA7U) {
      recid = Unpack_M167_Voltage_Info_bev_dbc(&(_m->M167_Voltage_Info), _d, dlc_);
     } else if (_id == 0xA8U) {
      recid = Unpack_M168_Flux_ID_IQ_Info_bev_dbc(&(_m->M168_Flux_ID_IQ_Info), _d, dlc_);
     }
    }
   } else {
    if (_id == 0xA9U) {
     recid = Unpack_M169_Internal_Voltages_bev_dbc(&(_m->M169_Internal_Voltages), _d, dlc_);
    } else {
     if (_id == 0xAAU) {
      recid = Unpack_M170_Internal_States_bev_dbc(&(_m->M170_Internal_States), _d, dlc_);
     } else if (_id == 0xABU) {
      recid = Unpack_M171_Fault_Codes_bev_dbc(&(_m->M171_Fault_Codes), _d, dlc_);
     }
    }
   }
  }
 } else {
  if ((_id >= 0xACU) && (_id < 0xC1U)) {
   if ((_id >= 0xACU) && (_id < 0xAFU)) {
    if (_id == 0xACU) {
     recid = Unpack_M172_Torque_And_Timer_Info_bev_dbc(&(_m->M172_Torque_And_Timer_Info), _d, dlc_);
    } else {
     if (_id == 0xADU) {
      recid = Unpack_M173_Modulation_And_Flux_Info_bev_dbc(&(_m->M173_Modulation_And_Flux_Info), _d, dlc_);
     } else if (_id == 0xAEU) {
      recid = Unpack_M174_Firmware_Info_bev_dbc(&(_m->M174_Firmware_Info), _d, dlc_);
     }
    }
   } else {
    if (_id == 0xAFU) {
     recid = Unpack_M175_Diag_Data_bev_dbc(&(_m->M175_Diag_Data), _d, dlc_);
    } else {
     if (_id == 0xB0U) {
      recid = Unpack_M176_Fast_Info_bev_dbc(&(_m->M176_Fast_Info), _d, dlc_);
     } else if (_id == 0xC0U) {
      recid = Unpack_M192_Command_Message_bev_dbc(&(_m->M192_Command_Message), _d, dlc_);
     }
    }
   }
  } else {
   if ((_id >= 0xC1U) && (_id < 0x1D7U)) {
    if (_id == 0xC1U) {
     recid = Unpack_M193_Read_Write_Param_Command_bev_dbc(&(_m->M193_Read_Write_Param_Command), _d, dlc_);
    } else {
     if (_id == 0xC2U) {
      recid = Unpack_M194_Read_Write_Param_Response_bev_dbc(&(_m->M194_Read_Write_Param_Response), _d, dlc_);
     } else if (_id == 0x1D5U) {
      recid = Unpack_M188_U2C_Message_Rxd_bev_dbc(&(_m->M188_U2C_Message_Rxd), _d, dlc_);
     }
    }
   } else {
    if ((_id >= 0x1D7U) && (_id < 0x6B1U)) {
     if (_id == 0x1D7U) {
      recid = Unpack_M187_U2C_Command_Txd_bev_dbc(&(_m->M187_U2C_Command_Txd), _d, dlc_);
     } else if (_id == 0x202U) {
      recid = Unpack_BMS_Current_Limit_bev_dbc(&(_m->BMS_Current_Limit), _d, dlc_);
     }
    } else {
     if (_id == 0x6B1U) {
      recid = Unpack_BMS_Msg1_bev_dbc(&(_m->BMS_Msg1), _d, dlc_);
     } else if (_id == 0x6B2U) {
      recid = Unpack_BMS_Faults1_bev_dbc(&(_m->BMS_Faults1), _d, dlc_);
     }
    }
   }
  }
 }

 return recid;
}

