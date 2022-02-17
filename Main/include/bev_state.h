#ifndef BEV_STATE_H
#define BEV_STATE_H

/* TODO: Marshal (2/14/22)
* Need to document this state machine logic 
*/

//Enum to describe the different states of the car 
//Documentation on the states can be found at https://xiahualiu.github.io/posts/bev-tasks/
//enum ECUState {INIT,RESET,RESET_CONFIRM,ERROR_STATE,ROUTINE_CHECK,PRE_HV_CHECK,HV_READY_WAIT,PRECHARGE_WAIT,READY_TO_GO_WAIT};
//probably better variable name could be found but I am braindead and in ened so this is what you get
enum ECUState {
   INIT, RESET, RESET_CONFIRM, ERROR_STATE, ROUTINE_CHECK, PRE_HV_CHECK, 
   HV_READY_WAIT, PRECHARGE_WAIT,READY_TO_GO_WAIT};



#endif // BEV_STATE_H