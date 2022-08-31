/**
 * @file bev_logger.ino
 * @author Marshal Stewart (stewa2m3@mail.uc.edu)
 * @brief 
 * @version v1.1
 * @date 2022-07-03
 * 
 * Logger API, able to log to Serial, SD Card, and I2C device
 *  
 * $$$$$$$\  $$$$$$$$\ $$\    $$\
 * $$  __$$\ $$  _____|$$ |   $$ |
 * $$ |  $$ |$$ |      $$ |   $$ |
 * $$$$$$$\ |$$$$$\    \$$\  $$  |
 * $$  __$$\ $$  __|    \$$\$$  /
 * $$ |  $$ |$$ |        \$$$  /
 * $$$$$$$  |$$$$$$$$\    \$  /   
 * \_______/ \________|    \_/    
 * Copyright University of Cincinnati 2022
 * 
 */

#include "bev_logger.h"
#include "bev_can.h"

Bev_Logger Log;

Bev_Logger::Bev_Logger() {}

void Bev_Logger::can(const CAN_message_t &msg) {
    print(msg);
}
void Bev_Logger::info(const char* string) {
    print(INFO, string);
}
void Bev_Logger::error(const char* string) {
    print(ERROR, string);
}
void Bev_Logger::warning(const char* string) {
    print(WARNING, string);
}
void Bev_Logger::critical(const char* string) {
    print(CRITICAL, string);
}

void Bev_Logger::print(LogLevel level, const char *string) {
    static char buffer[120];
    
    #ifdef DEBUG_BEV
    Serial.println(string);
    #endif

    if (snprintf(buffer, 100, "%s:%s", LEVEL_STRING[level], string) >= 0)
    {
      WriteToSD(buffer, "EVENT.log");
    }
    
}

void Bev_Logger::print(const CAN_message_t &msg) {
    
    #ifdef DEBUG_BEV
    char buffer[100] = {0};
    CAN2Str(msg, buffer, 100);
    Serial.println(buffer);
    #endif

    WriteToSD(msg, "CAN.log");
}

/** @todo CAN King Format */
void CAN2Str(const CAN_message_t &msg, char *buffer, size_t len) {

    snprintf(buffer, len, "MB:%d OVERRUN:%d LEN:%d EXT:%d TS:%05d ID:%04lX BUFFER: ", 
              msg.mb, msg.flags.overrun, msg.len, msg.flags.extended, 
              msg.timestamp, msg.id);
    
    /* Adding char '0' to numeric returns ascii value */
    char tmpBuf[msg.len] = {0};
    for ( uint8_t i = 0; i < msg.len; i++ ) {
        tmpBuf[i] = msg.buf[i] + '0';
    }

    /* Append to buffer */
    strncat(buffer, tmpBuf, msg.len);

}

void WriteToSD(const char* dataString, const char* fname){
	if (!SD.begin(BUILTIN_SDCARD)) {
        return;
    }

    if (dataString == NULL || fname == NULL) {
        return;
    }

	File dataFile = SD.open(fname, FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
    }

}

void WriteToSD(const CAN_message_t &msg, const char* fname){
    static char buffer[100];
	
    if (!SD.begin(BUILTIN_SDCARD)) {
      return;
	}

    CAN2Str(msg, buffer, 100);

	File dataFile = SD.open(fname, FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.println(buffer);
      dataFile.close();
    }

}

/**
 * @brief File I/O Operations for debugging
 */
// static void printSpaces(int num) {
//   for (int i=0; i < num; i++) {
//     Serial.print(" ");
//   }
// }
// static void printDirectory(File dir, int numSpaces) {
//    while(true) {
//      File entry = dir.openNextFile();
//      if (! entry) {
//        //Serial.println("** no more files **");
//        break;
//      }
//      printSpaces(numSpaces);
//      Serial.print(entry.name());
//      if (entry.isDirectory()) {
//        Serial.println("/");
//        printDirectory(entry, numSpaces+2);
//      } else {
//        // files have sizes, directories do not
//        unsigned int n = log10(entry.size());
//        if (n > 10) n = 10;
//        printSpaces(50 - numSpaces - strlen(entry.name()) - n);
//        Serial.print("  ");
//        Serial.print(entry.size(), DEC);
//        DateTimeFields datetime;
//        if (entry.getModifyTime(datetime)) {
//          printSpaces(4);
//         //  printTime(datetime);
//        }
//        Serial.println();
//      }
//      entry.close();
//    }
// }

// void ls(void)
// {
//     File root = SD.open("/");
//     printDirectory(root, 0);
// }



