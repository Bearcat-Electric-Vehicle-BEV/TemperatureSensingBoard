/*
 * Author: Dhruv Pandey
 *
 * This file is auto-generated and may be overwritten.
*/

#ifndef TEMP_LOOKUP_H
#define TEMP_LOOKUP_H

#include <cstdint>

#define ARRAY_SIZE 59

//58 elements in the array. The first element represents the temperature value when the ADC gives 65 in binary, and the last element when ADC gives 122
static const int8_t lookup[ARRAY_SIZE] = { 
    120, 105, 105, 95, 90, 80, 78, 75, 70, 65, 68, 60, 58, 55, 53, 50, 48, 45, 44, 42, 40, 39, 37, 35, 34, 32, 30, 29, 27, 25, 24, 22, 20, 19, 17, 15, 14, 13, 12, 10, 9, 7, 5, 3, 2, 0, -2, -3, -5, -7, -10, -12, -15, -18, -20, -25, -30, -35, -40
};

 #endif