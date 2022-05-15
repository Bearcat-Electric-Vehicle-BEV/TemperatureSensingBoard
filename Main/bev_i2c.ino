#include "include/bev_i2c.h"

bool displayOnline = true;

void display_write(int addr, const char *string) {
    Wire.beginTransmission(addr);

    if (string == NULL) {
      return;
    }

    Wire.write(MotorSpeed);
    Wire.endTransmission();
}

void update_display() {
    unsigned Range_KM = 0, Range_Mins = 0;
    
    char buffer[100];
    snprintf(buffer, 100, "%d,%d,%d,%d,%d",
      MotorSpeed, InternalTemperature, SOC, Range_KM, Range_Mins);
    display_write(UPDATE_DISPLAY_ADDR, buffer);
}

/*
 * find_address
 * finds address of devices on I2C bus and prints to Serial
 * https://github.com/Richard-Gemmell/teensy4_i2c/blob/master/examples/wire/find_slaves/find_slaves.ino
 */
bool check_display_online(){
  
    if (displayOnline) {
        Wire.beginTransmission(UPDATE_DISPLAY_ADDR);
        if (Wire.endTransmission() != 0) {
            displayOnline = false;
        }
    }
    
    return displayOnline;
}
