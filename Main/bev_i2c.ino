#include <i2c_device.h>

#include "include/bev_i2c.h"
#include <i2c_driver.h>
#include <i2c_driver_wire.h>

I2CMaster& master = master;
I2CDevice sensor = I2CDevice(master, DISPLAY_I2C_ADDR, _BIG_ENDIAN);

/*
 * displayUpdateParam
 * uint16_t param_macro - macro defining which display parameter to write to
 * uint16_t param_val   - value to be written to display parameter
 * 
 * Sends two I2C bytes, one for defining which parameter is to be written to,
 * the other for the value of that parameter. The goal of this is to not update 
 * all the parameters of the display constantly, but in unique intervals. For example 
 * the driver should have the speed updated very often, but not necessarily the battery
 * percentage since it changes less frequently. This could be implemented on the teensy side
 * via timers or hysterisis.
 */
bool displayUpdateParam(uint16_t param_macro, uint16_t param_val){

  if (param_macro <= DISPLAY_PARAM_MIN || param_macro >= DISPLAY_PARAM_MAX)
  {
    Serial.printf("Unknown display parameter %d\n", param_macro);
    return false;
  }

  if (!sensor.write(DISPLAY_I2C_ADDR, param_macro, false)) {
    Serial.printf("ERROR: Failed to write display parameter %d to display\n", param_macro);
    return false;
  }
  
  Serial.printf("Wrote parameter %d to display\n", val);
      
  if (!sensor.write(DISPLAY_I2C_ADDR, param_val, true)) {
    Serial.printf("ERROR: Failed to write %d to display\n", param_val);
    return false;
  }

  Serial.printf("Wrote val %d to display\n", val);

  return true;
    
}

// Teensy Master Write, Display Read
void displayWrite(uint16_t val){

    if (!sensor.write(DISPLAY_I2C_ADDR, val, true)) {
      Serial.println("ERROR: Failed to write to display");
      return;
    } else {
      Serial.printf("Wrote %d to display\n", val);     
    }
    
}

// Teensy Master Read, Display Write
void displayRead(){

    uint16_t val = 0;
    if (!sensor.read(DISPLAY_I2C_ADDR, &val, true)) {
        Serial.println("ERROR: Failed to read from display");
    }
    Serial.printf("Read from display: %d\n", val);
  
}


// Teensy Slave Write, Display Read
int count = 0;
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

// Teensy Slave Read, Display Write
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
