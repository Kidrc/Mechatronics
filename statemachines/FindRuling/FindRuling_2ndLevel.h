#ifndef FIND_RULING_2NDLEVEL_H
#define FIND_RULING_2NDLEVEL_H

#include "ES_Configure.h"
#include "ES_Framework.h"

#include "globalmacros.h"
#include "SearchCastle.h"

#define FIND_RULING_ENUMFORM(STATE) FIND_RULING_##STATE,

#define LIST_OF_FIND_RULING_STATES(STATE)\
    STATE(SEARCH_CASTLE_SE)\
    STATE(SEARCH_CASTLE_SW)\
    STATE(SEARCH_CASTLE_NW)\

LIST_OF_FIND_RULING_STATES(INITFUNC_PROTOTYPE);
LIST_OF_FIND_RULING_STATES(RUNFUNC_PROTOTYPE);

extern uint8_t startingCastle;
extern uint8_t currentObstacleType;
extern uint8_t location;

extern int findruling_ccw_L;
extern int findruling_ccw_R;
extern int findruling_ccw90_Time;
extern int findruling_ccw180_Time;

extern int forward_L;
extern int forward_R;

extern int align;
extern int align_Time;

extern int reverse_L;
extern int reverse_R;
extern int reverse_Time;

#endif
