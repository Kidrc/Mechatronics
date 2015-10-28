#ifndef SUBFINDWALL_H
#define SUBFINDWALL_H

#include "ES_Configure.h"

#define LIST_OF_FIND_WALL_STATES(STATE)\
        STATE(FORWARD)\
        STATE(SPIN180)\

#define ENUM_FORM(STATE) STATE,
#define STRING_FORM(STATE) #STATE,

typedef enum
{
	LIST_OF_FIND_WALL_STATES(ENUM_FORM)
}FindWallState_t;


void FIND_WALL_InitSubHSM(void);

ES_Event FIND_WALL_RunSubHSM(ES_Event ThisEvent);

#endif