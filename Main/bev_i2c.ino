#include <i2c_device.h>

#include "include/bev_i2c.h"
#include <i2c_driver.h>
#include <i2c_driver_wire.h>

int count = 0;

// Teensy Write, Display Read
void displayRequestEvent()
{
    Serial.println(count);
    count += 1;
    Wire.write(25 + int(random(0, 10)));  //speed (in kph)
    Wire.write(30  + int(random(0, 5)));  //battery temp (in degree C)
    Wire.write(10  + int(random(0, 5)));  //range left in distance (in km)
    Wire.write(45  + int(random(0, 5)));  //range left in terms of time (mins)
    Wire.write(99  - int(random(0, 5)));  //battery life (percentage)


}

// Teensy Read, Display Write
void displayReceiveEvent(int howMany)
{
    while(Wire.available() > 1) {
        char c = Wire.read();
        Serial.print(c);
    }
    Serial.println();
    int x = Wire.read();
    Serial.println(x);
}

/*
 * find_address
 * finds address of devices on I2C bus and prints to Serial
 * https://github.com/Richard-Gemmell/teensy4_i2c/blob/master/examples/wire/find_slaves/find_slaves.ino
 */
void find_address(){
    Serial.println("Searching for slave devices...");

    uint8_t num_found = 0;
    for (uint8_t address = MIN_I2C_ADDR; address < MAX_I2C_ADDR; address++) {
		// Serial.println("Checking address ");
		// Serial.println(address, HEX);
        Wire.beginTransmission(address);

        uint8_t error = Wire.endTransmission();
        if (error == 0) {
            Serial.print("Slave device found at address ");
            Serial.println(address);
            num_found++;
        } else if (error == 2) {
            // The master received an address NACK.
            // This is the code we expect if there's nobody listening on this address.
            // Serial.println("Address not in use.");
        } else {
            // Serial.print("Unexpected error at address ");
            // Serial.println(address);
        }
    }
    if (num_found == 0) {
        Serial.println("No I2C slave devices found.");
    } else {
        Serial.print("Found ");
        Serial.print(num_found);
        Serial.println(" slave devices.");
    }
    Serial.println();

    delay(5000);           // wait 5 seconds for next scan
}
