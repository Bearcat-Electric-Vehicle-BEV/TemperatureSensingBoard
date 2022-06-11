#ifndef BEV_STATE_H
#define BEV_STATE_H


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

enum ECUState{
    FOREACH_STATE(GENERATE_STATE_ENUM)
};

const char *STATE_STRING[] = {
    FOREACH_STATE(GENERATE_STATE_STRING)
};

extern const char *STATE_STRING[];
extern ECUState currentState;


/* Function prototypes */

void ChangeState(ECUState newState);
void carInit();
void carReset();
void resetConfirm();
void error();
void routineCheck();
void preHVCheck();

#endif // BEV_STATE_H