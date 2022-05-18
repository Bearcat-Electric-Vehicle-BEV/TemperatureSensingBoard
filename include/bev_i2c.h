#ifndef BEV_I2C_H
#define BEV_I2C_H

#include <i2c_device.h>
#include <i2c_driver.h>
#include <i2c_driver_wire.h>

/*
 * I2C Library Used
 * https://github.com/Richard-Gemmell/teensy4_i2c
 */

/*
0x0B - speed (in kph)
0x0C - battery temp (in degree C)
0x0D - range left in distance (in km)
0x0E - range left in terms of time (mins)
0x0F - battery life (percentage)
 */

/*
 * Macros used to define parameters to communicate with 
 * Pyportal Titano Display. Macros are used so if the 
 * communication definition changes, limited code changes
 * are needed.
 */

#define UPDATE_DISPLAY_SPEED 0x40
#define UPDATE_DISPLAY_TEMP 0x41
#define UPDATE_DISPLAY_PERCENT 0x42
#define UPDATE_DISPLAY_DIST 0x43
#define UPDATE_DISPLAY_TIME 0x44

extern bool displayOnline;

void display_write(int addr, const char *string);
void updateDisplay();
bool check_display_online();

#endif // BEV_I2C_H
