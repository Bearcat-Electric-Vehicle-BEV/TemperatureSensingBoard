#ifndef BEV_STATE_H
#define BEV_STATE_H

#include <FreeRTOS.h>
#include <FreeRTOSConfig.h>
#include <task.h> 

/** @todo fill out with useful */

#define OK 0
#define FAIL -1

typedef int code_t;

/**
 * State Macros/Enums
 * 
 * Using #defines to autogenerate enum states and their strings 
 */

#define GENERATE_STATE_ENUM(ENUM) ENUM,
#define GENERATE_STATE_STRING(STRING) #STRING,

#define FOREACH_STATE(STATE) \
        STATE(INIT)   \
        STATE(RESET)  \
        STATE(RESET_CONFIRM)   \
        STATE(ERROR_STATE)  \
        STATE(ROUTINE_CHECK)  \
        STATE(PRE_HV_CHECK)  \
        STATE(HV_READY_WAIT)  \
        STATE(PRECHARGE_WAIT)  \
        STATE(READY_TO_GO_WAIT)  \

typedef enum {
    FOREACH_STATE(GENERATE_STATE_ENUM)
} ECUState_t;

const char *STATE_STRING[] = {
    FOREACH_STATE(GENERATE_STATE_STRING)
};

extern const char *STATE_STRING[];
extern volatile ECUState_t currentState;

void ISR_SHUTDOWN_TTL_OK();
code_t ChangeState(ECUState_t newState);
code_t ChangeState(ECUState_t newState, const char *reason);
bool CheckState(ECUState_t vState);

extern TaskHandle_t pxStateMachineHandle;
void vStateMachine(void * pvParameters);

#endif // BEV_STATE_H