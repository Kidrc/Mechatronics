/*
 * File:   AlignReverse_4thLevel.h
  *
 * Created on November 30, 2014, 7:18 PM
 */

#ifndef ROTATE_H
#define	ROTATE_H

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "TimerList.h"

#define CCW 0
#define CW 1

#define CW_TARGET 80
#define CCW_TARGET 85
#define ROTATE_LIMIT_TIME 400
#define TOLERANCE 12

uint8_t ROTATE_InitFSM(uint8_t Priority);
ES_Event ROTATE_RunFSM(ES_Event);
uint8_t PostRotateFSM(ES_Event ThisEvent);

void PostRotate(ES_EventTyp_t EventType, uint8_t src, int16_t left, int16_t right);
#endif	/* ALIGNREVERSE_4THLEVEL_H */

