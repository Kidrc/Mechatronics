/*
 * File:   AlignReverse_4thLevel.h
  *
 * Created on November 30, 2014, 7:18 PM
 */

#ifndef ALIGNREVERSE_4THLEVEL_H
#define	ALIGNREVERSE_4THLEVEL_H

#include "ES_Configure.h"
#include "ES_Framework.h"


uint8_t ALIGN_REVERSE_InitFSM(uint8_t Priority);
ES_Event ALIGN_REVERSE_RunFSM(ES_Event);
uint8_t PostAlignFSM(ES_Event ThisEvent);

void PostAlign(ES_EventTyp_t EventType, uint8_t sensor, uint8_t src);
#endif	/* ALIGNREVERSE_4THLEVEL_H */

