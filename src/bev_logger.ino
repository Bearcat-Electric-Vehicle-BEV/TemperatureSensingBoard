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
#include "bev_i2c.h"

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
    static char buffer[100];
    
    snprintf(buffer, 100, "%s:%s", LEVEL_STRING[level], string);
    WriteToSD(buffer, "EVENT.log");
    
}

void Bev_Logger::print(const CAN_message_t &msg) {
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

	// open the file
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

	// open the file
	File dataFile = SD.open(fname, FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.println(buffer);
      dataFile.close();
    }

}

