/**
 * @file bev_state.ino
 * @author Marshal Stewart (stewa2m3@mail.uc.edu)
 * @brief 
 * @version v1.1
 * @date 2022-06-30
 * 
 *
 * $$$$$$$\  $$$$$$$$\ $$\    $$\
 * $$  __$$\ $$  _____|$$ |   $$ |
 * $$ |  $$ |$$ |      $$ |   $$ |
 * $$$$$$$\ |$$$$$\    \$$\  $$  |
 * $$  __$$\ $$  __|    \$$\$$  /
 * $$ |  $$ |$$ |        \$$$  /
 * $$$$$$$  |$$$$$$$$\    \$  /   
 * \_______/ \________|    \_/    
 * Copyright University of Cincinnati 2022
 * 
 */

#include "bev_logger.h"
#include "bev_pins.h"
#include "bev_state.h"
#include "bev_faults.h"

#include <FreeRTOS.h>
#include <task.h>

/**
 * State Machine Diagram https://drive.google.com/file/d/1_kZ9mo7b1bYq2sO-uvetE1C0Gtml-KTl/view?usp=sharing
 * Original documentation on the states can be found at https://xiahualiu.github.io/posts/bev-tasks/
 */

volatile ECUState_t ECUState;

/**
 * @brief 
 * ISR for debouncing SHUTDOWN_TTL_OK
 */
void ISR_SHUTDOWN_TTL_OK(void)
{
    /// @todo debounce

    if (0)
    {
    /// Change to error state
    ChangeState(SHUTDOWN, "PIN_SHUTDOWN_TTL_OK went HIGH");
    }

}

/**
 * @brief Transition the current state
 * 
 * @param newState 
 */
code_t ChangeState(ECUState_t newState) {
    ECUState = newState;
    char buffer[100];
    snprintf(buffer, 100, "CHANGE STATE TO %s", STATE_STRING[newState]);
    Log.info(buffer);

    /** @todo Should have way of knowing whether a transition is valid */
    return OK;
}

code_t ChangeState(ECUState_t newState, const char *reason) {
    ECUState = newState;
    char buffer[100];
    snprintf(buffer, 100, "CHANGE STATE TO %s", STATE_STRING[newState]);
    if (newState == SHUTDOWN || newState == TS_DISABLE)
    {
        Log.error(buffer);
        Log.error(reason);
    }
    else 
    {
        Log.info(buffer);
        Log.info(reason);
    }

    /** @todo Should have way of knowing whether a transition is valid */
    return OK;
}

/**
 * @brief 
 * 
 * @param vState 
 * @return true 
 * @return false 
 */
bool CheckState(ECUState_t vState)
{
    if (ECUState != vState)
    {
        return false;
    }

    return true;
}

/**
 * @brief Get the State Str object
 * 
 * @return const char* 
 */
const char *GetStateStr(void)
{
  return STATE_STRING[ECUState];
}

TaskHandle_t pxStateMachineHandle;

/** @todo Need to make sure that StateMachine is the only active task during startup */

/**
 * @brief 
 * 
 * 
 * @note VERY IMPORTANT THAT TASK IS VERY SHORT, SHOULDN'T DO MUCH IN A STATE
 */
void vStateMachine(__attribute__((unused)) void * pvParameters)
{
    TickType_t xLastWakeTime;
 	const TickType_t xFrequency = pdMS_TO_TICKS(1000);

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    for( ;; )
    {
        ServiceCANIdle();
        
        if (CheckState(INIT)) {
            /* 
            This state is the first to be entered after the vehicle LV switch is flipped. Durring 
            this state CAN communication is initialized and basic checks should be completed. All 
            pins corresponding to running the motor or allowing HV should be set to their respective 
            OFF positions.
            */
            digitalWrite(PIN_ECU_OK, LOW);
            ChangeState(RESET);
        } 
        else if(CheckState(RESET)) {
            /*
            At a minimum, this state should be used to reset the fault manager and the display. 
            This state will be used to complete the 'refresh' tasks required to clear any lingering 
            faults or errors which may have caused the previous shutdown.
            */
           // TODO (Marsh May 2022): what memory needs reset?
            digitalWrite(PIN_ECU_OK, LOW);
            digitalWrite(PIN_PRECHARGE_FINISHED, LOW);
            ChangeState(PRE_HV_CHECK);            
        } 
        else if(CheckState(RESET_CONFIRM)) {
            // TODO (marsh May 2022): is this state necessary?
            /*
            If this state is considered nessecary, it will be a resting state between TS_DISABLED
            and READY_TO_GO_WAIT. During this time it can wait to see a button press or some other
            confirmation from the driver that they are ready to re-enter the driving state.
            */
        } 
        else if(CheckState(SHUTDOWN)) {
            /*
            This state replaced the legacy ERROR state which effectively killed HV power to the
            vehicle. Shutdown state is meant to disconnect HV power from the accumulator to the
            rest of the tractive system. This state cannot be left until the vehicle is reset
            from outside. This state is effectively GAME OVER for the current run.
            */
            digitalWrite(PIN_ECU_OK, LOW);
            digitalWrite(PIN_PRECHARGE_FINISHED, LOW);
            SendInverterDisable();
            
            #ifdef DEBUG_BEV
            // Serial.println("Entered Error State");
            #else 
            //configASSERT(NULL);  // Reset vector?
            #endif
            
        } 
        else if(CheckState(TS_DISABLE)) {
            /*
            This is a soft version of the SHUTDOWN state. This state does not require that we
            completely cut off HV power, but it must shutoff the motor. Effectively, this state
            will act as a way to stop the motor if a non critical issue comes up, while still
            allowing the driver the ability to restart without getting out of the vehicle or having
            to quit the current run.
            */
            digitalWrite(PIN_ECU_OK, LOW);
            SendInverterDisable();
            
            #ifdef DEBUG_BEV
            // Serial.println("Entered Error State");
            #else 
            //configASSERT(NULL);  // Reset vector?
            #endif
            
        } 
        else if(CheckState(PRE_HV_CHECK)) {
            // TODO (Marsh May 2022): what memory needs reset?
            /*
            This state checks the features of the vehicle pertaining to HV before PRE_CHARGE_WAIT
            Items including the current charge of the battery and reseting the precharge pin will
            be handled here ??, and a physical switch will need to be flipped before going into
            pre charge
            */
            digitalWrite(PIN_ECU_OK, LOW);
            digitalWrite(PIN_PRECHARGE_FINISHED, LOW);

            ChangeState(PRECHARGE_WAIT);
        } 
        /**
         * The PM100DX has it's own internal logic and circuitry for the pre-charge, however we are
         * by passing this. The pre-charge is actually done without the motor controller knowing. The 
         * accumulator circuit and shutdown circuit open the relay for 5 time constants, charging the 
         * capacitors.
         */
        else if(CheckState(PRECHARGE_WAIT)) {
            /*
            This state is meant to allow enough time for the system to precharge, it manually delays
            while monitoring how the capacitors charge.
            */
            // 5 Time Constants of the Pre-Charge Circuit
            digitalWrite(PIN_ECU_OK, HIGH);
            vTaskDelay(pdMS_TO_TICKS(1500));

            if (digitalRead(PIN_FORWARD_SWITCH) == HIGH)
            {
              /// @todo Need to redo 
              digitalWrite(PIN_FORWARD_ENABLE, HIGH);
              // Play ready to go sound
              // Change state to 
            }
            // if passed precharge wait
            ChangeState(READY_TO_GO_WAIT);        
        } 
        else if(CheckState(READY_TO_GO_WAIT)) {
            /*
            This task begins reading the pedal positions and allows the motor controler to respond
            by spinning the motor. This is the running state of the vehicle.
            */
            /** @note ETC Task is unblocked and running */
        }
        else {
            /*
            Catch for if the vehicle somehow changes to a state that hasnt been laid out here.
            Sends the vehicle to SHUTDOWN
            */
          Log.critical("Entered unknown state, jumping to error");
          ChangeState(SHUTDOWN);
        }

        // Wait for the next cycle.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
 
    configASSERT(NULL);
 
}
