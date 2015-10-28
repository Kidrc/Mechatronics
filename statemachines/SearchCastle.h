/*
 * File:   AlignReverse_4thLevel.h
  *
 * Created on November 30, 2014, 7:18 PM
 */

#ifndef SEARCHCASTLE_4THLEVEL_H
#define	SEARCHCASTLE_4THLEVEL_H

#include "ES_Configure.h"
#include "ES_Framework.h"



uint8_t SEARCH_CASTLE_InitFSM(uint8_t Priority);
ES_Event SEARCH_CASTLE_RunFSM(ES_Event);
uint8_t PostSearchCastleFSM(ES_Event ThisEvent);

void PostSearchCastle(ES_EventTyp_t EventType, uint8_t castleType, uint8_t src);

#endif	/* ALIGNREVERSE_4THLEVEL_H */

