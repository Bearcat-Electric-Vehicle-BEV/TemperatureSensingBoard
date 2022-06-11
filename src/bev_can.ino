/**
 * $$$$$$$\  $$$$$$$$\ $$\    $$\ 
 * $$  __$$\ $$  _____|$$ |   $$ |
 * $$ |  $$ |$$ |      $$ |   $$ |
 * $$$$$$$\ |$$$$$\    \$$\  $$  |
 * $$  __$$\ $$  __|    \$$\$$  / 
 * $$ |  $$ |$$ |        \$$$  /  
 * $$$$$$$  |$$$$$$$$\    \$  /   
 * \_______/ \________|    \_/    
 *
 * @name bev_can.ino
 *                              
 * @author Marshal Stewart
 * 
 * APIs for interacting with CAN bus and the devices on it.
 * 
 * @lib https://github.com/tonton81/FlexCAN_T4 
 *
 */


#include "bev_can.h"
#include "bev_logger.h"

/**
 * CAN Bus Object, Can0
 * 
 * Object is an instance of CAN1 on the Teensy Pinout. Object needs 
 * initialized via CANInit(), this will set baudrate, mailbox filters, 
 * callbacks, and enabled mailboxes. 
 */
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

/**
 * Motor Controller CAN parameters
 * 
 * All possible CAN msgs that the motor controller can broadcast. During 
 * production, majority of these will go unused.
 * 
 * TODO: #define guards, once compiler args file is planned
 * 
 * TODO: Write Python script to auto generate these parameters
 * 
 */
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
uint8_t Diagnostic_Index, Diagnostic_SubIndex, Record_0, Record_1, Record_2, Record_3, Record_4, Record_5;

/**
 * Orion BMS 2 CAN Messages
 * 
 * CAN msgs that the BMS can broadcast. These aren't static and defined from
 * the Orion BMS GUI. These should be in sync with the OrionBMS2.dbc file
 * 
 * TODO: Python script to autogenerate these parameters
 */
unsigned SOC, DCL, CCL, InternalTemperature, HighestCellVoltage, PackCurrent, AverageTemperature, CheckSum;
uint32_t bms_faults[3];

/**
 * PM100DX Command Heartbeat Message, CmdMsg
 * 
 * CAN message sent to Motor Controller at least every half second. Populated
 * by numerous functions and tasks. 
 * 
 * The other variables are the globals that are used to populate the CAN message.
 */
CAN_message_t CmdMsg;

uint8_t TorqueCommand = 0;
uint8_t SpeedCommand = 0;
uint8_t Direction = 1;
uint8_t InverterEnabled = 0;
uint8_t Duration = 0;

/**
 * CANInit
 * 
 * @param void
 * 
 * @return void
 * 
 * Initializes CAN bus, mailboxes, filters. Should be called before attempting to use Can0
 * 
 * @todo #define guards for what messages are being used
 * 
 * @todo What is a fail condition
 * 
 */
void CANInit(){
    Can0.begin();
    Can0.setBaudRate(250000);
    Can0.setMaxMB(16);

    Can0.setMB(MB0, RX, STD);
    Can0.setMB(MB1, RX, STD);
    Can0.setMB(MB2, RX, STD);
    Can0.setMB(MB3, RX, STD);
    Can0.setMB(MB4, RX, STD);
    
    Can0.setMBFilter(REJECT_ALL);
    Can0.setMBFilter(MB0, RMS_TEMPERATURES_3);
    Can0.setMBFilter(MB1, RMS_MOTOR_POSITION_INFO);
    Can0.setMBFilter(MB2, RMS_FAULT_CODES);
    Can0.setMBFilter(MB3, RMS_TORQUE_AND_TIMER_INFORMATION);
    Can0.setMBFilter(MB4, RMS_DIAGNOSTIC_DATA);

    Can0.onReceive(MB0,CanSniff);
    Can0.onReceive(MB1,CanSniff);
    Can0.onReceive(MB2,CanSniff);

    Can0.setMBUserFilter(MB0,0x00,0xFF);
    Can0.setMBUserFilter(MB1,0x03,0xFF);
    Can0.setMBUserFilter(MB2,0x0B,0xFF);

    Can0.mailboxStatus();

    // Setup Command Message, static msgs members, set once
    CmdMsg.id = RMS_COMMAND_MESSGE_ADDR;
    CmdMsg.flags.extended = 0;
    CmdMsg.len = 8;
}

/**
 * CheckFautCodes
 * 
 * @param void
 * 
 * @return True/Fault, False/No Fault
 * 
 * Checks whether a fault code has been asserted on either the Motor Controller
 * or the BMS. Returns True if there is a fault, false if no fault.
 * 
 * @todo The faultPersistant thing straight up doesn't work, also should use the header system
 * 
 */
bool CheckFaultCodes() {

    // Motor Controller 
    for (uint8_t i=0; i<16; i++) {
        if ((POSTFaultLo & (1 << i)) || (POSTFaultHi & (1 << i)) ||
            (RunFaultLo & (1 << i)) || (RunFaultHi & (1 << i))) 
        {
            return (true);
        }
    }
    
    // BMS
    for (uint8_t i=0; i<sizeof(bms_faults)/sizeof(uint32_t); i++) {
        if (bms_faults[i]) {
            return (true);
        }
    }


    return false;

}

/**
 * SendMessage
 * 
 * @param id                CAN message ID
 * @param buffer            Buffer to create message from
 * @param len               Length of Buffer (DLC)
 * 
 * @return True/Success, False/Failed
 * 
 * Constructs a CAN msg from parameters and attempts to write to CAN bus. Fails
 * if the user provides an invalid parameter.
 * 
 * TODO: The faultPersistant thing straight up doesn't work, also should use the header system
 * 
 */
bool SendMessage(unsigned id, unsigned *buffer, unsigned len) {

    if (buffer == nullptr)
        return false;
    
    CAN_message_t msg;
    msg.id = id;
    msg.flags.extended = 0;
    
    for (unsigned i=0; i<len; i++){
        msg.buf[i] = buffer[i];
    }

    Can0.write(msg);

    return true;

}

/**
 * SendInverterEnable
 * 
 * @param void
 * 
 * @return void
 * 
 * Sends enable CAN message to the Motor Controller.
 * 
 * Before the inverter can be ran, must send a disable command.
 * For more information see Section 2.2.1 Inverter Enable Safety Options
 * of the RMS CAN Protocol Document
 * 
 */
void SendInverterEnable() {

    // Set in CANInit, small optimization
    // CmdMsg.id = RMS_COMMAND_MESSGE_ADDR;
    // CmdMsg.flags.extended = 0;
    // CmdMsg.len = 8;

    for (unsigned i=0; i<8; i++){
        CmdMsg.buf[i] = 0;
    }

    CmdMsg.buf[4] = 1;

    Can0.write(CmdMsg);

}

/**
 * SendInverterDisable
 * 
 * @param void
 * 
 * @return void
 * 
 * Sends enable CAN message to the Motor Controller.
 * 
 * Before the inverter can be ran, must send a disable command.
 * For more information see Section 2.2.1 Inverter Enable Safety Options
 * of the RMS CAN Protocol Document
 * 
 */
void SendInverterDisable() {

    // Set in CANInit, small optimization
    // CmdMsg.id = RMS_COMMAND_MESSGE_ADDR;
    // CmdMsg.flags.extended = 0;
    // CmdMsg.len = 8;

    for (unsigned i=0; i<8; i++){
        CmdMsg.buf[i] = 0;
    }

    Can0.write(CmdMsg);
}

/**
 * SendRMSHeartBeat
 * 
 * @param void
 * 
 * @return void
 * 
 * Callback function for task to send heartbeat to motor controller
 * 
 * Populates CAN_message_t CmdMsg, then writes on Can0. For more information
 * on the CAN Command Message for the RMS see Section 2.2 Command Message in
 * the RMS CAN Protocol document. 
 * 
 */
void SendRMSHeartBeat(){

    // Set in CANInit, small optimization
    // CmdMsg.id = RMS_COMMAND_MESSGE_ADDR;
    // CmdMsg.flags.extended = 0;
    // CmdMsg.len = 8;

    CmdMsg.buf[0] = (TorqueCommand * 10) % 256;
    CmdMsg.buf[1] = int(TorqueCommand * 10 / 256);
    CmdMsg.buf[2] = SpeedCommand % 256;
    CmdMsg.buf[3] = int(SpeedCommand / 256);
    CmdMsg.buf[4] = Direction;
    CmdMsg.buf[5] = int(InverterEnabled);
    CmdMsg.buf[6] = 0;
    CmdMsg.buf[7] = 0;
    
    Can0.write(CmdMsg);

}

/**
 * SendClearFaults
 * 
 * @param void
 * 
 * @return void
 * 
 * Callback function for task to send heartbeat to motor controller
 * 
 * Populates CAN_message_t CmdMsg, then writes on Can0. For more information
 * on the CAN Command Message for the RMS see Section 2.2 Command Message in
 * the RMS CAN Protocol document. 
 * 
 */
void SendClearFaults() {

    CmdMsg.id = RMS_PARAMETER_MSG1;
    CmdMsg.flags.extended = 0;
    CmdMsg.len = 8;

    CmdMsg.buf[0] = 20; 
    CmdMsg.buf[1] = 0; 
    CmdMsg.buf[2] = 1; 
    CmdMsg.buf[3] = 0;
    CmdMsg.buf[4] = 0; 
    CmdMsg.buf[5] = 0; 
    CmdMsg.buf[6] = 0; 
    CmdMsg.buf[7] = 0;

    Can0.write(CmdMsg);

}

/**
 * CanSniff
 * 
 * @param msg       CAN Message Object, passed by reference
 * 
 * @return void
 * 
 * Callback function that assigns incoming signals to globals
 * 
 */
void CanSniff(const CAN_message_t &msg){

//    Log.info(msg);

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
                PowerOnTimer = msg.buf[4] | (msg.buf[5] << 8) | (msg.buf[6] << 16) | (msg.buf[7] << 24); 
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
                Diagnostic_Index = msg.buf[0];
                Diagnostic_SubIndex = msg.buf[1];
                Record_0 = msg.buf[2];
                Record_1 = msg.buf[3];
                Record_2 = msg.buf[4];
                Record_3 = msg.buf[5];
                Record_4 = msg.buf[6];
                Record_5 = msg.buf[7];
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
                
            // Checksum
            // Expect all message to be 8 bytes in len
            int sum = msg.id + 8;
            for (int i=0; i<7; i++){
                sum += msg.buf[i];
            }

            sum &= ~8;

            if (sum != msg.buf[7]){
                Log.error("Failed checksum");
                return;
            }

        switch (msg.id){
            case BMS_MSG1:
                SOC = msg.buf[0];
                DCL = msg.buf[1];
                CCL = msg.buf[2];
                InternalTemperature = msg.buf[3];
                HighestCellVoltage = msg.buf[4];
                PackCurrent = msg.buf[5];
                AverageTemperature = msg.buf[6];
                break;
            case BMS_FAULTS1: 
                bms_faults[0] = msg.buf[0];
                break;
            case BMS_FAULTS2: 
                bms_faults[1] = msg.buf[0] | (msg.buf[1] << 8);
                break;
            case BMS_FAULTS3: 
                bms_faults[2] = msg.buf[0];
                break;
            
            default:
                break;
        }

    }
    else { return; } // Unknown Message 

//    Log.info(msg);

}

/**
 * DumpFaultCodes
 * 
 * @param void
 * 
 * @return void
 * 
 * Callback function that assigns incoming signals to globals
 * 
 */
void DumpFaultCodes() {
    char buffer[200];
    snprintf(buffer, 200, 
    "POSTFaultLo:%d,POSTFaultHi:%d,RunFaultLo:%d,RunFaultHi:%d"
    "DTC_Status_1:%lu,DTC_Status_2:%lu,Failsafe_Statuses:%lu",
    POSTFaultLo,POSTFaultHi,RunFaultLo, RunFaultHi,
    bms_faults[0],bms_faults[1],bms_faults[2]);

    Log.error(buffer);

}

/**
 * CAN2Str
 * 
 * @param msg           CAN Message to be casted
 * @param buffer        Buffer that will be written to
 * @param len           Buffer len (not DLC)
 * 
 * @return void
 * 
 * Breaks down CAN message and writes to buffer in CAN King format
 * 
 * TODO: make CAN king format, so we can use parsing tools
 * 
 */
void CAN2Str(const CAN_message_t &msg, char *buffer, size_t len) {

    snprintf(buffer, len, "MB:%d OVERRUN:%d LEN:%d EXT:%d TS:%05d ID:%04lX BUFFER: ", 
              msg.mb, msg.flags.overrun, msg.len, msg.flags.extended, 
              msg.timestamp, msg.id);
    
    /* Adding char '0' to numeric returns ascii value */
    char tmpBuf[msg.len] = {0};
    for ( uint8_t i = 0; i < msg.len; i++ ) {
        tmpBuf[i] = msg.buf[i] + '0';
    }

    /* Append to buffer */
    strncat(buffer, tmpBuf, msg.len);

}
