/*
 * Author: Dhruv Pandey
 *
 * This file is auto-generated and may be overwritten.
*/

#ifndef TEMP_LOOKUP_H
#define TEMP_LOOKUP_H

#include <cstdint>

#define ARRAY_SIZE 58

//58 elements in the array. The first element represents the temperature value when the ADC gives 65 in binary, and the last element when ADC gives 122
static const int8_t lookup[ARRAY_SIZE] = { 
    120, 110, 100, 93, 85, 80, 77, 73, 68, 65, 62, 59, 56, 54, 51, 49, 46, 44, 42, 40, 38, 37, 35, 33, 32, 30, 28, 27, 25, 23, 22, 20, 19, 17, 16, 14, 13, 11, 9, 7, 6, 4, 2, 1, -1, -2, -4, -6, -9, -11, -13, -15, -18, -22, -25, -30, -35, -40
};

 #endif