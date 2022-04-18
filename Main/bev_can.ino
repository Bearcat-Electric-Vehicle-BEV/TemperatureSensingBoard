#include "include/bev_can.h"

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
CAN_message_t cmdMsg;

uint16_t ModuleATemperature=0, ModuleBTemperature=0, ModuleCTemperature=0, GateDriverBoardTemperature=0;
uint16_t ControlBoardTemperature=0, RTD1Temperature=0, RTD2Temperature=0, RTD3Temperature=0;
uint16_t RTD4Temperature=0, RTD5Temperature=0, MotorTemperature=0, TorqueShudder=0;
uint16_t AnalogInput1=0, AnalogInput2=0, AnalogInput3=0, AnalogInput4=0;
uint8_t DigitalInput1=0, DigitalInput2=0, DigitalInput3=0, DigitalInput4=0, DigitalInput5=0, DigitalInput6=0;
uint16_t MotorAngle=0, MotorSpeed=0, ElectricalOutputFreq=0, DeltaResolver=0;
uint16_t PhaseACurrent=0, PhaseBCurrent=0, PhaseCCurrent=0, DCBusCurrent=0;
uint16_t DCBusVoltage=0, OutputVoltage=0, PhaseABVoltage=0, PhaseBCVoltage=0;
uint16_t FluxCommand=0, FluxFeedback=0, idFeedback=0, iqFeedback=0;
uint16_t ReferenceVoltage15=0, ReferenceVoltage25=0, ReferenceVoltage50=0, SystemVoltage12=0;
uint16_t VSMState=0; uint8_t InverterState=0, RelayState=0, InverterRunMode=0, InverterCommandMode=0, InverterEnableState=0, InverterEnableLockout=0, DirectionCommand=0;
uint16_t POSTFaultLo=0, POSTFaultHi=0, RunFaultLo=0, RunFaultHi=0;
uint16_t CommandedTorque=0, TorqueFeedback=0; uint32_t PowerOnTimer=0;
uint16_t ModulationIndex=0, FluxWeakeningOutput=0, IdCommand=0, IqCommand=0;
uint16_t EEPROMVersion=0, SoftwareVersion=0, DataCode_mmdd=0, DataCode_yyyy=0;
uint16_t gamma_resolver=0, gamm_observer=0, sin_corr=0;
uint16_t cos_corr=0, la_corr=0, lb_corr=0;
uint16_t lc_corr=0, vdc=0, iq_cmd=0;
uint16_t id_cmd=0, modulation=0, flux_weak_out=0;
uint16_t vq_cmd=0, vd_cmd=0, vqs_cmd=0;
uint16_t voltage12_pwmfreq=0, run_faults_lo=0, run_faults_hi=0;

void sendMessage(unsigned id, unsigned *buffer, unsigned len) {

    if (buffer == nullptr)
        return;
    
    CAN_message_t msg;
    msg.id = id;
    msg.flags.extended = 0;
    
    for (unsigned i=0; i<len; i++){
        msg.buf[i] = buffer[i];
    }

    Can0.write(msg);

    Serial.print("Wrote: ");
    Serial.println(id);
}

/*
 * sendInverterEnable
 *
 * Before the inverter can be ran, must send a disable command.
 * For more information see Section 2.2.1 Inverter Enable Safety Options
 * of the RMS CAN Protocol Document
 */
void sendInverterEnable() {
    cmdMsg.id = RMS_COMMAND_MESSGE_ADDR;
    cmdMsg.flags.extended = 0;
    cmdMsg.len = 8;

    cmdMsg.buf[0] = 0; 
    cmdMsg.buf[1] = 0; 
    cmdMsg.buf[2] = 0; 
    cmdMsg.buf[3] = 0; 
    cmdMsg.buf[4] = 0; 
    cmdMsg.buf[5] = 0; 
    cmdMsg.buf[6] = 0; 
    cmdMsg.buf[7] = 0;

    Can0.write(cmdMsg);

}

/*
 * sendRMSHeartbeat
 *
 * Populates CAN_message_t cmdMsg, then writes on Can0. For more information
 * on the CAN Command Message for the RMS see Section 2.2 Command Message in
 * the RMS CAN Protocol document. 
 *
 */
void sendRMSHeartbeat(){

  cmdMsg.id = RMS_COMMAND_MESSGE_ADDR;
  cmdMsg.flags.extended = 0;
  cmdMsg.len = 8;

  // Construct msg
  cmdMsg.buf[0] = (TorqueCommand * 10) % 256;
  cmdMsg.buf[1] = int(TorqueCommand * 10 / 256);
  cmdMsg.buf[2] = SpeedCommand % 256;
  cmdMsg.buf[3] = int(SpeedCommand / 256);
  cmdMsg.buf[4] = Direction;
  cmdMsg.buf[5] = int(InverterEnabled);
  cmdMsg.buf[6] = 0;
  cmdMsg.buf[7] = 0;
  
  Can0.write(cmdMsg);

}

/*
 * canSniff
 *
 * Callback function that assigns incoming signals to globals 
 */
void canSniff(const CAN_message_t &msg){
    printCANMsg(msg);	

    return;
    
    if (msg.id >= RMS_ADDR_LOW && msg.id <= RMS_ADDR_HIGH) { 

        switch(msg.id) {
            case RMS_TEMPERATURES_1:
                ModuleATemperature = msg.buf[0] | (msg.buf[1] << 8);
                ModuleBTemperature = msg.buf[2] | (msg.buf[3] << 8);
                ModuleCTemperature = msg.buf[4] | (msg.buf[5] << 8);
                GateDriverBoardTemperature = msg.buf[6] | (msg.buf[7] << 8);
                break;
            case RMS_TEMPERATURES_2:
                ControlBoardTemperature = msg.buf[0] | (msg.buf[1] << 8);
                RTD1Temperature = msg.buf[2] | (msg.buf[3] << 8);
                RTD2Temperature = msg.buf[4] | (msg.buf[5] << 8);
                RTD3Temperature = msg.buf[6] | (msg.buf[7] << 8);
                break;
            case RMS_TEMPERATURES_3:
                RTD4Temperature = msg.buf[0] | (msg.buf[1] << 8);
                RTD5Temperature = msg.buf[2] | (msg.buf[3] << 8);
                MotorTemperature = msg.buf[4] | (msg.buf[5] << 8);
                TorqueShudder = msg.buf[6] | (msg.buf[7] << 8);
                break;

            case RMS_ANALOG_INPUT_VOLTAGE:
                AnalogInput1 = msg.buf[0] | (msg.buf[1] << 8);
                AnalogInput2 = msg.buf[2] | (msg.buf[3] << 8);
                AnalogInput3 = msg.buf[4] | (msg.buf[5] << 8);
                AnalogInput4 = msg.buf[6] | (msg.buf[7] << 8);
                break;

            case RMS_DIGITAL_INPUT_STATUS:
                DigitalInput1 = msg.buf[0];
                DigitalInput2 = msg.buf[1];
                DigitalInput3 = msg.buf[2];
                DigitalInput4 = msg.buf[3];
                DigitalInput5 = msg.buf[4];
                DigitalInput6 = msg.buf[5];
                break;
            
            case RMS_MOTOR_POSITION_INFO:
                MotorAngle = msg.buf[0] | (msg.buf[1] << 8);
                MotorSpeed = msg.buf[2] | (msg.buf[3] << 8);
                ElectricalOutputFreq = msg.buf[4] | (msg.buf[5] << 8);
                DeltaResolver = msg.buf[6] | (msg.buf[7] << 8);
                break;

            case RMS_CURRENT_INFORMATION:
                PhaseACurrent = msg.buf[0] | (msg.buf[1] << 8);
                PhaseBCurrent = msg.buf[2] | (msg.buf[3] << 8);
                PhaseCCurrent = msg.buf[4] | (msg.buf[5] << 8);
                DCBusCurrent = msg.buf[6] | (msg.buf[7] << 8);
                break;

            case RMS_VOLTAGE_INFORMATION:
                DCBusVoltage = msg.buf[0] | (msg.buf[1] << 8);
                OutputVoltage = msg.buf[2] | (msg.buf[3] << 8);
                PhaseABVoltage = msg.buf[4] | (msg.buf[5] << 8);
                PhaseBCVoltage = msg.buf[6] | (msg.buf[7] << 8);
                break;
            
            case RMS_FLUX_INFORMATION:
                FluxCommand = msg.buf[0] | (msg.buf[1] << 8);
                FluxFeedback = msg.buf[2] | (msg.buf[3] << 8);
                idFeedback = msg.buf[4] | (msg.buf[5] << 8);
                iqFeedback = msg.buf[6] | (msg.buf[7] << 8);
                break;
            
            case RMS_INTERNAL_VOLTAGES:
                ReferenceVoltage15 = msg.buf[0] | (msg.buf[1] << 8);
                ReferenceVoltage25 = msg.buf[2] | (msg.buf[3] << 8);
                ReferenceVoltage50 = msg.buf[4] | (msg.buf[5] << 8);
                SystemVoltage12 = msg.buf[6] | (msg.buf[7] << 8);
                break;
            
            case RMS_INTERNAL_STATES:
                VSMState = msg.buf[0] | (msg.buf[1] << 8);
                InverterState = msg.buf[2];
                RelayState = msg.buf[3];
                InverterRunMode = msg.buf[4];
                InverterCommandMode = msg.buf[5];
                InverterEnableState = msg.buf[6] & 1;
                InverterEnableLockout = msg.buf[6] & 128;
                DirectionCommand = msg.buf[7];
                break;

            case RMS_FAULT_CODES:
                POSTFaultLo = msg.buf[0] | (msg.buf[1] << 8);
                POSTFaultHi = msg.buf[2] | (msg.buf[3] << 8);
                RunFaultLo = msg.buf[4] | (msg.buf[5] << 8);
                RunFaultHi = msg.buf[6] | (msg.buf[7] << 8);
                break;

            case RMS_TORQUE_AND_TIMER_INFORMATION:
                CommandedTorque = msg.buf[0] | (msg.buf[1] << 8);
                TorqueFeedback = msg.buf[2] | (msg.buf[3] << 8);
                PowerOnTimer = msg.buf[4] | (msg.buf[5] << 8) | (msg.buf[6] << 16) | (msg.buf[7] << 32); 
                break;
            
            case RMS_MODULATION_INDEX_AND_FLUX_WEAKENING_OUTPUT_INFORMATION:
                ModulationIndex = msg.buf[0] | (msg.buf[1] << 8);
                FluxWeakeningOutput = msg.buf[2] | (msg.buf[3] << 8);
                IqCommand = msg.buf[4] | (msg.buf[5] << 8);
                IqCommand = msg.buf[6] | (msg.buf[7] << 8);
                break;
            
            case RMS_FIRMWARE_INFORMATION:
                EEPROMVersion= msg.buf[0] | (msg.buf[1] << 8);
                SoftwareVersion = msg.buf[2] | (msg.buf[3] << 8);
                DataCode_mmdd = msg.buf[4] | (msg.buf[5] << 8);
                DataCode_yyyy = msg.buf[6] | (msg.buf[7] << 8);
                break;
            
            case RMS_DIAGNOSTIC_DATA:
                // TODO
                break;
            
            default:
                break;

        }


    }
    else if (msg.id >=BMS_ADDR_LOW && msg.id <= BMS_ADDR_HIGH) {

        /* Checksum - Byte 7
         1. Take the boradcast ID and add 8 (the length).
         2. Add bytes 0-6 to the value from step 1.
         3. Chop off the least significant 8 bits (effectively turning
            it into an unsigned byte) and that will be the checksum 
            value.
         4. If the computed checksum doesn't equal the provided checksum, 
            the values should be discarded.
         */

        switch (msg.id){
            case 0x0: // BMS Fault Code 1
                break;
            case 0x1: // BMS Fault Code 2
                break;
            default:
                // Expect all message to be 8 bytes in len
                int sum = msg.id + 8;
                for (int i=0; i<7; i++){
                    sum += msg.buf[i];
                }

                sum &= ~8;

                if (sum != msg.buf[7]){
                    return; // Failed checksum
                }

                break;
        }

        // Assign to global values
        if (msg.id == 0x00) // BMS Msg 1
            return;
        else if (msg.id == 0x00) // BMS Msg 2
            return;
        else if (msg.id == 0x0) // BMS Fault Code 1
            return;
        else if (msg.id == 0x0) // BMS Fault Code 2
            return;
        else
        {
            // Unknown Message
        }




    }
    else {} // Unknown Message 

}

/*
 * printCANMsg 
 *
 * Prints a CAN msg to the Serial Console
 */
void printCANMsg(const CAN_message_t &msg){
    Serial.print("MB "); Serial.print(msg.mb);
    Serial.print("  OVERRUN: "); Serial.print(msg.flags.overrun);
    Serial.print("  LEN: "); Serial.print(msg.len);
    Serial.print(" EXT: "); Serial.print(msg.flags.extended);
    Serial.print(" TS: "); Serial.print(msg.timestamp);
    Serial.print(" ID: "); Serial.print(msg.id, HEX);
    Serial.print(" Buffer: ");
    for ( uint8_t i = 0; i < msg.len; i++ ) {
        Serial.print(msg.buf[i], HEX); Serial.print(" ");
    } Serial.println();

}
