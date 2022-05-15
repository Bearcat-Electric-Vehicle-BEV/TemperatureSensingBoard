#ifndef BEV_LOGGER_H
#define BEV_LOGGER_H

#include <SPI.h>
#include <SD.h>

#include "bev_can.h"

#define LOGGER_DISPLAY_MODE 1
#define LOGGER_SD_MODE 2
#define LOGGER_SERIAL_MODE 4

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

#define FOREACH_LEVEL(LEVEL) \
        LEVEL(INFO)   \
        LEVEL(ERROR)  \
        LEVEL(CRITICAL)   \
        LEVEL(WARNING)  \

enum LogLevel{
    FOREACH_LEVEL(GENERATE_ENUM)
};

static const char *LEVEL_STRING[] = {
    FOREACH_LEVEL(GENERATE_STRING)
};

class Bev_Logger {
public:
    uint8_t log_mode;
    
	Bev_Logger(uint8_t _log_mode);
    void info(const char *string);
    void error(const char *string);
    void warning(const char *string);
    void critical(const char *string);
    void info(const CAN_message_t &msg);
    void error(const CAN_message_t &msg);
    void warning(const CAN_message_t &msg);
    void critical(const CAN_message_t &msg);
    void print(LogLevel level, const char *string);
    void print(const CAN_message_t &msg);
};

extern Bev_Logger Log;

bool log_2_display(const char* dataString);
bool log_2_sd(const char* dataString, const char* fname);


#endif // BEV_LOGGER_H