/** 
 * Author: Marshal Stewart
 * Date: %<DATE_TIME>
 *
 * The following is an auto-generated file edits are likely to be
 * overwritten.
 */

#ifndef ETC_CURVE_H
#define ETC_CURVE_H

#include "bev_etc.h"

#define TABLE_SIZE %<TABLE_SIZE>U

/**
 * @paragraph ETC Lookup Table
 * The following array is the lookup table used for ETC calculations.
 * A lookup table is used instead of a calculations for speed. Flash 
 * memory is barely being used, therefore placing this table in flash
 * saves Teensy from doing complicated polynomial floating point calcs
 * every 50 ms or so.
 *
 * Takes input in integer Nm * 10, outputs integer in Nm * 10
 *
 */
static const torque_t lookup[TABLE_SIZE] = {
%<DATA>
};

#endif  // ETC_CRUVE_H