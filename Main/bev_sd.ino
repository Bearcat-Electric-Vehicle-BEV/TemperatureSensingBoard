#include "include/bev_sd.h"

bool log_2_sd(const char* dataString){
	if (!SD.begin(BUILTIN_SDCARD)) {
      	Serial.println("Card failed, or not present");
		return false;
	}

	// open the file
	File dataFile = SD.open("datalog.txt", FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
    } else {
      // if the file isn't open, pop up an error:
      Serial.println("error opening datalog.txt");
    }
    delay(100); // run at a reasonable not-too-fast speed

	return true;
}
