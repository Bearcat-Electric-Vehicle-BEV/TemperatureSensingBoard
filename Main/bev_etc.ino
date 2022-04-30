#include "include/bev_etc.h"
#include "include/bev_can.h"

bool validate_pedals(int pedal_0, int pedal_1) {
	return (float)abs((pedal_0 - pedal_1)/pedal_1) > 10 ? false : true;
}

bool validate_current_drawn() {
	return DCL < PackCurrent ? false : true; 
}