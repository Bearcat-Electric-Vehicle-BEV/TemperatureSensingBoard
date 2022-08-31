#ifndef BEV_LOGGER_H
#define BEV_LOGGER_H

#include <SPI.h>
#include <SD.h>

#include "bev_can.h"

enum LogLevel{
    INFO = 0,
    ERROR,
    CRITICAL,
    WARNING,
    NUM_LOG_LEVELS,
};

const char *LEVEL_STRING[NUM_LOG_LEVELS] = {
    "INFO",
    "ERROR",
    "CRITICAL",
    "WARNING",
};

class Bev_Logger {
public:
	Bev_Logger();
    void info(const char *string);
    void error(const char *string);
    void warning(const char *string);
    void critical(const char *string);
    void can(const CAN_message_t &msg);
private:
    void print(LogLevel level, const char *string);
    void print(const CAN_message_t &msg);
};

extern Bev_Logger Log;

void WriteToSD(const char* dataString, const char* fname);
void WriteToSD(const CAN_message_t &msg, const char* fname);


#endif // BEV_LOGGER_H