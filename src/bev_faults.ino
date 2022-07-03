#include "bev_faults.h"
#include "bev_can.h"
#include "bev_state.h"
#include "bev_logger.h"

#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>

const Fault_t PM100DX_POST_FaultMap[32] = {
    {"Hardware Gate/Desaturation Fault", true},
    {"HW Over-current Fault", true},
    {"Accelerator Shorted", true},
    {"Accelerator Open", true},
    {"Current Sensor Low", true},
    {"Current Sensor High", true},
    {"Module Temperature Low", true},
    {"Module Temperature High", true},
    {"Control PCB Temperature Low", true},
    {"Control PCB Temperature High", true},
    {"Gate Drive PCB Temperature Low", true},
    {"Gate Drive PCB Temperature High", true},
    {"5V Sense Voltage Low", true},
    {"5V Sense Voltage High", true},
    {"12V Sense Voltage Low", true},
    {"12V Sense Voltage High", true},
    {"2.5V Sense Voltage Low", true},
    {"2.5V Sense Voltage High", true},
    {"1.5V Sense Voltage Low", true},
    {"1.5V Sense Voltage High", true},
    {"DC Bus Voltage High", true},
    {"DC Bus Voltage Low", true},
    {"Pre-charge Timeout", true},
    {"Pre-charge Voltage Failure", true},
    {"EEPROM Checksum Invalid", true},
    {"EEPROM Data Out of Range", true},
    {"EEPROM Update Required", true},
    {"Reserved", true},
    {"Reserved", true},
    {"Reserved", true},
    {"Brake Shorted", true},
    {"Brake Open", true},
};

const Fault_t PM100DX_RUN_FaultMap[32] = {
    {"Motor Over-speed Fault", true},
    {"Over-Current Fault", true},
    {"Over-voltage Fault", true},
    {"Inverter Over-temperature Fault", true},
    {"Accelerator Input Shorted Fault", true},
    {"Accelerator Input Open Fault", true},
    {"Direction Command Fault", true},
    {"Inverter Response Time-out Fault", true},
    {"Hardware Gate/DesaturationFault", true},
    {"Hardware Over-current Fault", true},
    {"Under-voltage Fault", true},
    {"CAN Command Message Lost Fault", false},
    {"Motor Over-temperatur Fault", true},
    {"Reserved", true},
    {"Reserved", true},
    {"Reserved", true},
    {"Brake Input Shorted Fault", true},
    {"Brake Input Open Fault", true},
    {"Module A Over-temperature Fault", true},
    {"Module B Over-temperaturs Fault", true},
    {"Module C Over-temperature Fault", true},
    {"PCB Over-temperature Fault", true},
    {"Gate Drive Board 1 Over-temperature Fault", true},
    {"Gate Drive Board 2 Over-temperature Fault", true},
    {"Gate Drive Board 3 Over-temperature Fault", true},
    {"Current Sensor Fault", true},
    {"Reserved", true},
    {"Reserved", true},
    {"Reserved", true},
    {"Reserved", true},
    {"Resolver Not Connected", true},
    {"Inverter Discharge Active", true}
};

const Fault_t OrionBMS2_DTCStatus_FaultMap[32] = {
    {"P0A07 (Discharge Limit Enforcement Fault)", true},
    {"P0A08 (Charger Safety Relay Fault)", true},
    {"P0A09 (Internal Hardware Fault)", true},
    {"P0A0A (Internal Heatsink Thermistor Fault)", true},
    {"P0A0B (Internal Software Fault)", true},
    {"P0A0C (Highest Cell Voltage Too High Fault)", true},
    {"P0A0E (Lowest Cell Voltage Too Low Fault)", true},
    {"P0A10 (Pack Too Hot Fault)", true},
    {"RESERVED", false},
    {"RESERVED", false},
    {"RESERVED", false},
    {"RESERVED", false},
    {"RESERVED", false},
    {"RESERVED", false},
    {"RESERVED", false},
    {"RESERVED", false},
    {"P0A1F (Internal Communication Fault)", true},
    {"P0A12 (Cell Balancing Stuck Off Fault)", true},
    {"P0A80 (Weak Cell Fault)", true},
    {"P0AFA (Low Cell Voltage Fault)", true},
    {"P0A04 (Open Wiring Fault)", true},
    {"P0AC0 (Current Sensor Fault)", true},
    {"P0A0D (Highest Cell Voltage Over 5V Fault)", true},
    {"P0A0F (Cell ASIC Fault)", true},
    {"P0A02 (Weak Pack Fault)", true},
    {"P0A81 (Fan Monitor Fault)", true},
    {"P0A9C (Thermistor Fault)", true},
    {"U0100 (External Communication Fault)", true},
    {"P0560 (Redundant Power Supply Fault)", true},
    {"P0AA6 (High Voltage Isolation Fault)", true},
    {"P0A05 (Input Power Supply Fault)", true},
    {"P0A06 (Charge Limit Enforcement Fault)", true},
};

code_t IFaultManager::CheckFaults()
{
    Fault_t fault;
    code_t ret = OK;
    bool clearFaults = false;

    uint16_t *wordPtr;
    uint16_t *words[2] = {HighWord, LowWord};

    for (int j=0; j<2; j++){
        wordPtr = words[j];

        if (*wordPtr)
        {
            for (int i=0; i<16; i++)
            {
                if (*wordPtr & (0x1 < i))
                {
                    fault = FaultMap[i + (j*16)];
                    Log.error(fault.string);

                    if (fault.critical)
                        ret = FAIL;
                    else 
                        clearFaults = true;
                }
            }

        }
    }

    /** Changing the error state will be done by the task */
    // if (ret != OK)
    // {
    //     // ChangeState(ERROR_STATE);
    //     return ret;
    // }
    
    if (clearFaults && ret == OK) 
    {
        ClearFaults();
    }

    return ret;
}

PM100DX_FaultManager::PM100DX_FaultManager(uint16_t *_HighWord, uint16_t *_LowWord, 
        const Fault_t *_FaultMap)
{
    this->HighWord = _HighWord;
    this->LowWord = _LowWord;
    this->FaultMap = _FaultMap;
}

code_t PM100DX_FaultManager::ClearFaults()
{
    static unsigned buffer[M193_Read_Write_Param_Command_DLC] = {
        20, 0, 1, 0, 0, 0, 0, 0
    };

    SendMessage(M193_Read_Write_Param_Command_CANID, buffer, 
        M193_Read_Write_Param_Command_DLC);
}

OrionBMS2_FaultManager::OrionBMS2_FaultManager(uint16_t *_HighWord, uint16_t *_LowWord, 
        const Fault_t *_FaultMap)
{
    this->HighWord = _HighWord;
    this->LowWord = _LowWord;
    this->FaultMap = _FaultMap;
}

code_t OrionBMS2_FaultManager::ClearFaults()
{
    static unsigned buffer[M193_Read_Write_Param_Command_DLC] = {
        20, 0, 1, 0, 0, 0, 0, 0
    };

    SendMessage(M193_Read_Write_Param_Command_CANID, buffer, 
        M193_Read_Write_Param_Command_DLC);
}

TaskHandle_t pxFaultManagerHandle;

void vFaultManager(__attribute__((unused)) void * pvParameters)
{
    static PM100DX_FaultManager rmsPostMgr = PM100DX_FaultManager(
                &DBCParser.M171_Fault_Codes.D2_Post_Fault_Hi, 
                &DBCParser.M171_Fault_Codes.D1_Post_Fault_Lo, 
                PM100DX_POST_FaultMap);

    static PM100DX_FaultManager rmsRunMgr = PM100DX_FaultManager(
                &DBCParser.M171_Fault_Codes.D4_Run_Fault_Hi, 
                &DBCParser.M171_Fault_Codes.D3_Run_Fault_Lo, 
                PM100DX_RUN_FaultMap);

    static OrionBMS2_FaultManager bmsDtcMgr = OrionBMS2_FaultManager(
                &DBCParser.BMS_Faults1.DTCStatus1, 
                &DBCParser.M171_Fault_Codes.D3_Run_Fault_Lo, 
                OrionBMS2_DTCStatus_FaultMap);
 	
    TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(1000);

     // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    for( ;; )
    {

        if (rmsPostMgr.CheckFaults() != OK)
        {
            ChangeState(ERROR_STATE);
        }
        
        if (rmsRunMgr.CheckFaults() != OK)
        {
            ChangeState(ERROR_STATE);
        }
        
        if (bmsDtcMgr.CheckFaults() != OK)
        {
            ChangeState(ERROR_STATE);
        }

        // Wait for the next cycle.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
 
    configASSERT(NULL);
 
}
