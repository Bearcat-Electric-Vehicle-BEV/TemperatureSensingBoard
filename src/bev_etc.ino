#include "bev_etc.h"
#include "bev_can.h"

bool enable_motor() {
  send_clear_faults();
  delay(1000); // takes a second to clear faults
  sendInverterEnable();
  InverterEnabled = 1;
	return true;
}

bool apply_pedals(int pedal_0) {

  int flip_thing = 937 - pedal_0;
  
  if (flip_thing > 100) {
	  InverterEnabled = 1;
  } else {
    InverterEnabled = 0;
  }

  double percent_pedal_0 = (double)flip_thing * (100.0 / 937.0);

  int new_torque = (int) (percent_pedal_0 * (3.0/100.0));

  double percent_torque_now = (double)TorqueCommand * (100.0 / 3.0);

  if (abs(percent_torque_now - percent_pedal_0) > 5) {
    TorqueCommand = new_torque;
  }

  return true;
}

/*
 * validate_pedals
 * TODO:
 */
bool validate_pedals(int pedal_0, int pedal_1) {

	// pedal_0 -> normal and 5v ~ (0 - 937)
	// pedal_1 -> reversed and 3.3v ~ (610 - 0)
	
	// convert pedal_1 to (0 - 610 scale)
	int scaled_pedal_1 = 610 - pedal_1;

	// Convert pedal_0 and pedal_1 to a percentage
	double percent_pedal_0 = (double)pedal_0 * (100.0 / 937.0); 
	double percent_pedal_1 = (double)scaled_pedal_1 * (100.0 / 610.0);

	return abs(percent_pedal_0 - percent_pedal_1) <= 10;
}

bool validate_current_drawn() {
	return DCL < PackCurrent ? false : true; 
}
