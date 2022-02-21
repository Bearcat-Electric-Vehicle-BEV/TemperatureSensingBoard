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

#define MIN_I2C_ADDR 0x1
#define DISPLAY_I2C_ADDR 0x40
#define MAX_I2C_ADDR 0x7F

void displayReceiveEvent();
void displayRequestEvent();
void find_address();

#endif // BEV_I2C_H
