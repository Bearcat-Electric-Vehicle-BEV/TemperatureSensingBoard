//#include <Ardiuno.h>
#include <i2c_device.h>

#include "include/bev_i2c.h"
#include <i2c_driver.h>
#include <i2c_driver_wire.h>

/*
 * write_channel_int
 *
 * Takes in a channel and value and writes over I2C bus as master
 * returns value signifying status
 */
int write_channel_int(uint chan, int val){
    if (chan < MIN_I2C_ADDR || chan > MAX_I2C_ADDR)
        return -1;

	Wire.beginTransmission(chan);
	Wire.write(val);
	Wire.endTransmission();

	delay(500);

	return 0;
}

/*
 * write_channel_pchar
 *
 * Takes in a channel and value and writes over I2C bus as master
 * returns value signifying status
 */
int write_channel_char_array(uint chan, char *val, size_t size){

    if (chan < MIN_I2C_ADDR || chan > MAX_I2C_ADDR)
        return -1;
    else if (val == nullptr)
        return -1;
    else if (size <= 0)
        return -1;

	Wire.beginTransmission(chan);
	Wire.write(val);
	Wire.endTransmission();

	delay(500);

	return 0;
}

void requestEvent()
{
  Serial.println("writing hello to i2c bus");
  Wire1.write("hello ");     // respond with message of 6 bytes
}

void slave_sender(){
  Wire1.begin(8);        // join i2c bus with address #8
  Wire1.onRequest(requestEvent); // register event
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
