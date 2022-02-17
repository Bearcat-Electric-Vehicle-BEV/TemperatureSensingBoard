#ifndef BEV_I2C_H
#define BEV_I2C_H

//#include <Ardiuno.h>
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
#define SPEED_I2C_ADDR 0xB
#define BATTERY_TEMP_I2C_ADDR 0xC
#define RANGE_DISTANCE_I2C_ADDR 0xD
#define RANGE_TIME_I2C_ADDR 0xE
#define BATTERY_LIFE_I2C_ADDR 0xF

#define MIN_I2C_ADDR 0x1
#define MAX_I2C_ADDR 0x7F

int write_channel_int(uint chan, int val);
int write_channel_char_array(uint chan, char *val, size_t size);
void find_address();
void slave_sender();

#endif // BEV_I2C_H
