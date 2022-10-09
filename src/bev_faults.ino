#include "bev_faults.h"
#include "bev_can.h"
#include "bev_state.h"
#include "bev_logger.h"

#include <FreeRTOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>

/**
 * @brief Fault Maps for PM100DX and Orion BMS 2
 * 
 * @paragraph FaultMaps CAN Fault Maps
 * The following structs contain fault maps for the PM100DX and Orion BMS 2, 
 * their faults are sent and parsed over CAN. The structs are used to improve
 * logging imformation, and determine whether a fault is critical. There do 
 * exist faults that the vehicle could continue operation, such as PM100DX
 * timeout, if this occurs the fault is logged and then attempted to be 
 * cleared. Fault manager takes this boolean "for it's word" and will
 * continue to clear the fault over and over again. It's important that if
 * the fault is critical, then it's labeled as so.
 */
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

/**
 * @brief Fault Checking API
 * 
 * @paragraph CheckFaults Fault Manager Fault Handling
 * The API checks the HighWord and LowWord individually, then if
 * the word is evaluated as non-zero it's bits are checked. Once a
 * raised bit is found, the fault map is used to determine if it's 
 * critical and log a readable message. If the fault is critical the
 * function returns a bad return code, THIS FUNCTION WILL NOT CHANGE
 * STATE. If the fault was non-critical, faults are cleared (assuming
 * no other faults were raised, if so then faults will not be cleared).
 *  
 * 
 * @return code_t 
 */


code_t IFaultManager::CheckFaults()
{
    Fault_t fault;
    code_t ret = OK;
    bool clearFaults = false;

    uint16_t *wordPtr;
    uint16_t *words[2] = {HighWord, LowWord};
    uint32_t *flags_raised = Flags;

    Serial.println(*HighWord);
    Serial.println(*LowWord);

    for (int j=0; j<2; j++){
        wordPtr = words[j];

        // Checks if at least one fault is present
        if (*wordPtr)
        {
            // Finds which fault(s) present
            for (int i=0; i<16; i++)
            {
                // Bitwise 'and' comparrison. If true, index 'i' is a '1'
                if (*wordPtr & (0x1 << i))
                {
                    // Decode fault using fault map
                    fault = FaultMap[i + (j*16)];
                    Serial.println("here");
                    Log.error(fault.string);

                    // Testing writing to SD functionality
                    WriteToSD(fault.string, "FAULTS.txt");

                    // Need to switch states if fault persists for 2 cycles
                    if (*flags_raised & (0x1 << i)){
                        if (fault.critical){
                            // Ensure critical fault has priority over non-critical
                            ret = TO_SHUTDOWN;
                            return ret;
                        } else {
                            ret = TO_TS_DISABLE;
                        }
                    }
                    // Raise flag for this fault
                    *flags_raised = *flags_raised | (0x1 << i);
                    ClearFaults(); // TODO: Handle clearning better
                } else { 
                    // Lower flag if fault not present
                    *flags_raised = *flags_raised & (0x0 << i);
                }
            }
        }
    }

    // TODO: fix how faults are cleared (check for persistence)

    /** Always clear faults to be simple */
    // ClearFaults();

    /** Changing the error state will be done by the task */

    return ret;
}

/**
 * @brief Construct a new pm100dx faultmanager::pm100dx faultmanager object
 * 
 * @param _HighWord 
 * @param _LowWord 
 * @param _FaultMap 
 * @param _Flags
 */
PM100DX_FaultManager::PM100DX_FaultManager(uint16_t *_HighWord, uint16_t *_LowWord, 
        const Fault_t *_FaultMap, uint32_t *_Flags)
{
    this->HighWord = _HighWord;
    this->LowWord = _LowWord;
    this->FaultMap = _FaultMap;
    this->Flags = _Flags;
}

/**
 * @brief PM100DX Clear Faults
 * 
 * @return code_t 
 * 
 * @paragraph PM100DX ClearFaults PM100DX Clearing Faults
 * To clear faults, the clear faults command is sent using the param command message.
 * The Fault Manager is running in it's own task, so it should be noted when trying to
 * enabled the inverter, that a ClearFaults command is already being sent if no other
 * critical faults are present. This pertains to "CAN Command Message Lost Fault", which 
 * is raised when a heartbeat message isn't being sent.
 * 
 */
void PM100DX_FaultManager::ClearFaults()
{
    #ifdef DEBUG_BEV
        Serial.println("Clearing faults");
    #endif

    static unsigned buffer[M193_Read_Write_Param_Command_DLC] = {
        20, 0, 1, 0, 0, 0, 0, 0
    };

    SendMessage(M193_Read_Write_Param_Command_CANID, buffer, 
        M193_Read_Write_Param_Command_DLC);
}

/**
 * @brief Construct a new OrionBMS2_FaultManager::OrionBMS2_FaultManager object
 * 
 * @param _HighWord 
 * @param _LowWord 
 * @param _FaultMap 
 * @param _Flags
 */
OrionBMS2_FaultManager::OrionBMS2_FaultManager(uint16_t *_HighWord, uint16_t *_LowWord, 
        const Fault_t *_FaultMap, uint32_t *_Flags)
{
    this->HighWord = _HighWord;
    this->LowWord = _LowWord;
    this->FaultMap = _FaultMap;
    this->Flags = _Flags;
}

/**
 * @brief 
 * 
 * @return code_t 
 * 
 * @todo Need to find the ClearFaults command for the BMS
 */
void OrionBMS2_FaultManager::ClearFaults()
{
    // static unsigned buffer[M193_Read_Write_Param_Command_DLC] = {
    //     20, 0, 1, 0, 0, 0, 0, 0
    // };

    // SendMessage(M193_Read_Write_Param_Command_CANID, buffer, 
    //     M193_Read_Write_Param_Command_DLC);

}

/**
 * @brief FreeRTOS Static Task Structs
 */
TaskHandle_t pxFaultManagerHandle;

/**
 * @brief Fault Manager FreeRTOS Task
 * 
 * Creates instances of Fault Managers, checks faults at low frequency, high priority.
 */
void vFaultManager(__attribute__((unused)) void * pvParameters)
{
    static PM100DX_FaultManager rmsPostMgr = PM100DX_FaultManager(
                &DBCParser.M171_Fault_Codes.D2_Post_Fault_Hi, 
                &DBCParser.M171_Fault_Codes.D1_Post_Fault_Lo, 
                PM100DX_POST_FaultMap, 0);

    static PM100DX_FaultManager rmsRunMgr = PM100DX_FaultManager(
                &DBCParser.M171_Fault_Codes.D4_Run_Fault_Hi, 
                &DBCParser.M171_Fault_Codes.D3_Run_Fault_Lo, 
                PM100DX_RUN_FaultMap, 0);

    static OrionBMS2_FaultManager bmsDtcMgr = OrionBMS2_FaultManager(
                (uint16_t*)&DBCParser.MSGID_0X6B2.DTC_Flags_1, 
                (uint16_t*)&DBCParser.MSGID_0X6B2.DTC_Flags_2, 
                OrionBMS2_DTCStatus_FaultMap, 0);
 	
    TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(2500);

     // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    for( ;; )
    {
        switch(rmsPostMgr.CheckFaults()){
            case TO_SHUTDOWN:
                // Enter shutdown
                Serial.println("Switching to SHUTDOWN..."); // DEBUG
                break;
            case TO_TS_DISABLE:
                // Enter TS disable
                Serial.println("Switching to TS_DISABLE..."); // DEBUG
                break;
            default:
                Serial.println("No POST faults\n");
            
        }

        switch(rmsRunMgr.CheckFaults()){
            case TO_SHUTDOWN:
                // Enter shutdown
                Serial.println("Switching to SHUTDOWN..."); // DEBUG
                break;
            case TO_TS_DISABLE:
                // Enter TS disable
                Serial.println("Switching to TS_DISABLE..."); // DEBUG
                break;
            default:
                Serial.println("No RUN faults\n");
            
        }

        switch(bmsDtcMgr.CheckFaults()){
            case TO_SHUTDOWN:
                // Enter shutdown
                Serial.println("Switching to SHUTDOWN..."); // DEBUG
                break;
            case TO_TS_DISABLE:
                // Enter TS disable
                Serial.println("Switching to TS_DISABLE..."); // DEBUG
                break;
            default:
                Serial.println("No BMS faults\n");
            
        }

        /*
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
        */
        // Wait for the next cycle.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
 
    configASSERT(NULL);
 
}
