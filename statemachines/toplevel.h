#ifndef TOPLEVEL_H
#define TOPLEVEL_H

#include "ES_Configure.h"
#include "ES_Framework.h"

#include "hodor_sensors.h"
#include "hodor_mech.h"
#include "hodor_motors.h"

#include "globalmacros.h"

#include "LED.h"

#define LIST_OF_TOP_STATES(STATE)\
		STATE(LEAVE_HOME)\
                STATE(FIND_RULING)\
                STATE(RETRIEVE_CROWN)\
                STATE(RETURN_HOME)\

LIST_OF_TOP_STATES(INITFUNC_PROTOTYPE);
LIST_OF_TOP_STATES(RUNFUNC_PROTOTYPE);

typedef enum
{
	INIT_TOPSTATE, ROTATE_TEST, LIST_OF_TOP_STATES(ENUM_FORM)
#ifdef _HODOR_TEST
        TIMER_TEST,
#endif
}TopState_t;

#define ENUM_FORM(STATE) STATE,
#define STRING_FORM(STATE) #STATE,
#define INITFUNC_FORM(STATE) STATE ##_InitSubHSM();



uint8_t InitToplevelHSM(uint8_t Priority);

uint8_t PostToplevelHSM(ES_Event ThisEvent);

TopState_t QueryToplevelHSM(void);

ES_Event RunToplevelHSM(ES_Event ThisEvent);

void HSM_LEDSubIndicate(uint8_t label);

#endif
