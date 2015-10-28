/*
 * File:   AlignReverse_4thLevel.h
  *
 * Created on November 30, 2014, 7:18 PM
 */

#ifndef RETURNCENTER_4THLEVEL_H
#define	RETURNCENTER_4THLEVEL_H

#include "ES_Configure.h"
#include "ES_Framework.h"


uint8_t RETURN_CENTER_InitFSM(uint8_t Priority);
ES_Event RETURN_CENTER_RunFSM(ES_Event);
uint8_t PostReturnCenterFSM(ES_Event ThisEvent);

void PostReturnCenter(ES_EventTyp_t EventType, uint8_t sensor, uint8_t src);

#endif	/* ALIGNREVERSE_4THLEVEL_H */

