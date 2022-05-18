#include "bev_i2c.h"
#include "bev_can.h"

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
    Wire.beginTransmission(UPDATE_DISPLAY_SPEED);
    Wire.write(TorqueFeedback);
    Wire.endTransmission();
    delay(10);
    return;
    Wire.write(MotorTemperature);
    Wire.write(SOC);
    Wire.write(96);
    Wire.write(69);
    Wire.endTransmission();
    delay(10);
}

/*
 * find_address
 * finds address of devices on I2C bus and prints to Serial
 * https://github.com/Richard-Gemmell/teensy4_i2c/blob/master/examples/wire/find_slaves/find_slaves.ino
 */
bool check_display_online(){
  
    if (displayOnline) {
        Wire.beginTransmission(0x40);
        if (Wire.endTransmission() != 0) {
            displayOnline = false;
        }
    }
    
    return displayOnline;
}
