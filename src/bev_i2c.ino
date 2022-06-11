/**
 * $$$$$$$\  $$$$$$$$\ $$\    $$\ 
 * $$  __$$\ $$  _____|$$ |   $$ |
 * $$ |  $$ |$$ |      $$ |   $$ |
 * $$$$$$$\ |$$$$$\    \$$\  $$  |
 * $$  __$$\ $$  __|    \$$\$$  / 
 * $$ |  $$ |$$ |        \$$$  /  
 * $$$$$$$  |$$$$$$$$\    \$  /   
 * \_______/ \________|    \_/    
 *
 * @name bev_i2c.ino
 *                              
 * @author Marshal Stewart
 * 
 * APIs for interacting with I2C Bus
 * 
 * @lib https://github.com/Richard-Gemmell/teensy4_i2c
 *
 */

#include "bev_i2c.h"
#include "bev_can.h"

static bool DisplayOnline = true;

/**
 * DisplayWrite
 * 
 * @author Marshal
 * 
 * @param addr      Slave I2C Address to write to
 * @param buffer    Buffer to write to Slave Address
 * 
 * @return True/Success, False/Fail
 * If the passed buffer is NULL, will return False.
 * 
 * @brief
 * Begins transmission with I2C Slave at addr, writes buffer, then ends
 * transmission.
 * 
 * It's very possible for the write to fail, this is due to the I2C lib,
 * most common occurances are that the transaction gets interrupted by another 
 * task, the display doesn't send ACK bit (Pyportal code possibly bad), or 
 * bad connection and/or noise present.
 * 
 */
bool DisplayWrite(unsigned addr, const char *buffer) {

    if (buffer == NULL) {
      return false;
    }
 
    Wire.beginTransmission(addr);
    Wire.write(MotorSpeed);
    Wire.endTransmission();

    return true;
}

/**
 * DisplayWrite
 * 
 * @author Marshal
 * 
 * @param addr      Slave I2C Address to write to
 * @param buffer    Buffer to write to Slave Address
 * 
 * @return True/Success, False/Fail
 * If the passed buffer is NULL, will return False.
 * 
 * @brief
 * Begins transmission with I2C Slave at addr, writes buffer, then ends
 * transmission.
 * 
 * It's very possible for the write to fail, this is due to the I2C lib,
 * most common occurances are that the transaction gets interrupted by another 
 * task, the display doesn't send ACK bit (Pyportal code possibly bad), or 
 * bad connection and/or noise present.
 * 
 */
void UpdateDisplay() {
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


/**
 * CheckDisplayOnline
 * 
 * @author Marshal
 * 
 * @param void
 * 
 * @return True/Online, False/Offline
 * 
 * @see <a href="https://github.com/Richard-Gemmell/teensy4_i2c/blob/master/examples/wire/find_slaves/find_slaves.ino"></a>
 * 
 * @brief
 * Checks whether Pyportal Titano Display is listening and responsive on the 
 * I2C bus. Does this by starting an empty transmission. The Wire lib is waiting
 * for a ACK bit, once recieved will end transmission. Note that if the display 
 * wasn't online when this function is first called, then will only return false.
 * 
 */
bool CheckDisplayOnline(){
  
    if (DisplayOnline) {
        Wire.beginTransmission(0x40);
        if (Wire.endTransmission() != 0) {
            DisplayOnline = false;
        }
    }
    
    return DisplayOnline;
}
