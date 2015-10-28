#ifndef EVENTCHECKER_H
#define EVENTCHECKER_H

#include "ES_Configure.h"

#include "hodor_sensors.h"

#define FILTER_DEPTH 8
#define SHIFT_ITERATIONS 3

static unsigned short filterArray[FILTER_DEPTH] = {[0 ... FILTER_DEPTH-1] = 0};

uint8_t CheckBumpers(void);
uint8_t CheckTapes(void);
uint8_t CheckTrackwire(void);
uint8_t CheckBeacon(void);

#endif