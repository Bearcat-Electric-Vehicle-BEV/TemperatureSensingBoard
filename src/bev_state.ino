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

static volatile ECUState_t ECUState;

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
    if (newState == ERROR_STATE)
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
 	  const TickType_t xFrequency = pdMS_TO_TICKS(25);

    // Initialise the xLastWakeTime variable with the current time.
    xLastWakeTime = xTaskGetTickCount();

    for( ;; )
    {
        if (CheckState(INIT)) {
            digitalWrite(PIN_ECU_OK, LOW);
            ChangeState(RESET);
        } 
        else if(CheckState(RESET)) {
            // TODO (Marsh May 2022): what memory needs reset?
            digitalWrite(PIN_ECU_OK, LOW);
            digitalWrite(PIN_PRECHARGE_FINISHED, LOW);
            ChangeState(PRE_HV_CHECK);            
        } 
        else if(CheckState(RESET_CONFIRM)) {
            // TODO (marsh May 2022): is this state necessary?
        } 
        else if(CheckState(ERROR_STATE)) {
            digitalWrite(PIN_ECU_OK, LOW);
            SendInverterDisable();
            configASSERT(NULL);  // Reset vector?
        } 
        else if(CheckState(ROUTINE_CHECK)) {
            /** @todo */
        } 
        else if(CheckState(PRE_HV_CHECK)) {
            // TODO (Marsh May 2022): what memory needs reset?

            digitalWrite(PIN_ECU_OK, LOW);
            digitalWrite(PIN_PRECHARGE_FINISHED, LOW);

            ChangeState(PRE_HV_CHECK);
        } 
        else if(CheckState(HV_READY_WAIT)) {
            digitalWrite(PIN_ECU_OK, HIGH);
            // digitalWrite(PIN_HV_READY, HIGH);

            ChangeState(PRECHARGE_WAIT);
        } 
        /**
         * The PM100DX has it's own internal logic and circuitry for the pre-charge, however we are
         * by passing this. The pre-charge is actually done without the motor controller knowing. The 
         * accumulator circuit and shutdown circuit open the relay for 5 time constants, charging the 
         * capacitors.
         */
        else if(CheckState(PRECHARGE_WAIT)) {
            // 5 Time Constants of the Pre-Charge Circuit
            /** @todo Disable interrupts */
            delay(1500);

            if (digitalRead(PIN_FORWARD_SWITCH) == HIGH)
            {
              digitalWrite(PIN_FORWARD_ENABLE, HIGH);
              // Play ready to go sound
              // Change state to 
            }
            // if passed precharge wait
            ChangeState(READY_TO_GO_WAIT);        
        } 
        else if(CheckState(READY_TO_GO_WAIT)) {
            /** @todo Allow ETC Task to run */
        
            // EnableMotor();
            // SendInverterDisable();
        
        }
        else {
          Log.critical("Entered unknown state, jumping to error");
          ChangeState(ERROR_STATE);
        }

        // Wait for the next cycle.
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
 
    configASSERT(NULL);
 
}
