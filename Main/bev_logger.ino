#include "include/bev_logger.h"

// https://github.com/thijse/Arduino-Log

Bev_Logger Log((uint8_t)(LOGGER_SERIAL_MODE));

Bev_Logger::Bev_Logger(uint8_t _log_mode) : log_mode(_log_mode)  { }

void Bev_Logger::info(const CAN_message_t &msg) {
    print(msg);
}
void Bev_Logger::error(const CAN_message_t &msg) {
    print(msg);
}
void Bev_Logger::warning(const CAN_message_t &msg) {
    print(msg);
}
void Bev_Logger::critical(const CAN_message_t &msg) {
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
    
    char buffer[100];
    snprintf(buffer, 100, "%s:%s", LEVEL_STRING[level], string);
    
    if (log_mode & LOGGER_DISPLAY_MODE) {
      if (!log_2_display(buffer)) {
          // TODO: need something
      }
    }
    if (log_mode & LOGGER_SD_MODE) {
      if (!log_2_sd(buffer, "EVENT.log")) {
          // TODO: need something
      }
    }
    if (log_mode & LOGGER_SERIAL_MODE) {
        Serial.println(buffer);
    }
    
}

void Bev_Logger::print(const CAN_message_t &msg) {
    
    if (log_mode & LOGGER_DISPLAY_MODE) {
      if (!log_2_display(msg)) {
          // TODO: need something
      }
    }
    if (log_mode & LOGGER_SD_MODE) {
      if (!log_2_sd(msg, "CAN.log")) {
          // TODO: need something
      }
    }
    if (log_mode & LOGGER_SERIAL_MODE) {
        char buffer[100];
        can_2_str(msg, buffer, 100);
        Serial.println(buffer);
    }
}

bool log_2_display(const char* dataString) 
{
    if (!check_display_online()) {
        return false;
    }

    if (dataString == NULL) {
        return false;
    }

    display_write(EVENT_LOG_ADDR, dataString);

    return true;
}

bool log_2_display(const CAN_message_t &msg) 
{
//    if (!check_display_online()) {
//        return false;
//    }

    char buffer[100];
    can_2_str(msg, buffer, 100);
    display_write(CAN_LOG_ADDR, buffer);

    return true;
}

bool log_2_sd(const char* dataString, const char* fname){
	if (!SD.begin(BUILTIN_SDCARD)) {
      return false;
	}

    if (dataString == NULL || fname == NULL) {
        return false;
    }

	// open the file
	File dataFile = SD.open(fname, FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
    }
    else {
      return false;
    }
    // delay(100);

	return true;
}

bool log_2_sd(const CAN_message_t &msg, const char* fname){
	if (!SD.begin(BUILTIN_SDCARD)) {
      return false;
	}

    char buffer[100];
    can_2_str(msg, buffer, 100);

	// open the file
	File dataFile = SD.open(fname, FILE_WRITE);
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.println(buffer);
      dataFile.close();
    }
    else {
      return false;
    }
    // delay(100);

	return true;
}
