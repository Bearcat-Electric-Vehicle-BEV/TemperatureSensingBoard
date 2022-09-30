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

Fault_t fault;
    code_t ret = OK;
    bool clearFaults = false;

    uint16_t *wordPtr;
    //uint16_t *words[2] = {HighWord, LowWord};
    uint16_t  *words[2] = {0b0010000000000000, 0b0000000000000000};

    Serial.println(*HighWord);
    Serial.println(*LowWord);

    for (int j=0; j<2; j++){
        wordPtr = words[j];

        if (*wordPtr)
        {
            for (int i=0; i<16; i++)
            {
                if (*wordPtr & (0x1 < i))
                {
                    fault = FaultMap[i + (j*16)];
                    Serial.println("here");
                    Log.error(fault.string);

                    if (fault.critical)
                        ret = FAIL;
                    else 
                        clearFaults = true;
                }
            }

        }
    }