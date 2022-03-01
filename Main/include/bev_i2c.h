#ifndef BEV_I2C_H
#define BEV_I2C_H

#include <i2c_device.h>

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

#define DISPLAY_PARAM_MIN 0
#define DISPLAY_SPEED 1
#define DISPLAY_BATTERY_TEMP 2
#define DISPLAY_BATTERY_LIFE 3
#define DISPLAY_RANGE_KM 4
#define DISPLAY_RANGE_MINS 5
#define DISPLAY_PARAM_MAX 6

#define MIN_I2C_ADDR 0x1
#define DISPLAY_I2C_ADDR 0x40
#define MAX_I2C_ADDR 0x7F

bool displayUpdateParam(uint16_t param_macro, uint16_t param_val);
void displayRead();
void displayWrite(uint16_t val);
void displayReceiveEvent();
void displayRequestEvent();
void find_address();

#endif // BEV_I2C_H
