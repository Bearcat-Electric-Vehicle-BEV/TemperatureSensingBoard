#ifndef BEV_I2C_H
#define BEV_I2C_H

//#include <Ardiuno.h>
#include <i2c_device.h>

/*
 * I2C Library Used
 * https://github.com/Richard-Gemmell/teensy4_i2c
 */

#define TRAVELED_I2C_ADDR 0xB
#define RANGE_I2C_ADDR 0xC
#define SPEED_I2C_ADDR 0xD
#define TEMPERATURE_I2C_ADDR 0xE
#define BATTERY_I2C_ADDR 0xF

int write_channel_int(uint chan, int val);
int write_channel_int_array(uint chan, int *val, size_t size);
int write_channel_char_array(uint chan, char *val, size_t size);
void find_address();

#endif // BEV_I2C_H
