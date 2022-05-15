#ifndef BEV_ETC_H
#define BEV_ETC_H

bool enable_motor();
bool apply_pedals(int pedal_0, int pedal_1);
bool validate_pedals(int pedal_0, int pedal_1);
bool validate_current_drawn();

#endif // BEV_ETC_H