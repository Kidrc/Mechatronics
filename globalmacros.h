#ifndef GLOBALMACROS_H
#define GLOBALMACROS_H

#include "BOARD.h"

#define _HODOR_TEST
//#define _HODOR_NORMAL

//#define _DEBUGMODE
#ifdef _DEBUGMODE
#define dbugprintf(...) printf(__VA_ARGS__); while(!IsTransmitEmpty())

#else
#define dbugprintf(...) ;

#endif
#define dbugstop() Motor_LeftSpeed(0);Motor_RightSpeed(0);while(1);

#define INITFUNC_PROTOTYPE(STATE) uint8_t STATE ##_InitSubHSM(void);
#define RUNFUNC_PROTOTYPE(STATE) ES_Event STATE ##_RunSubHSM(ES_Event);

#define INITFUNC_FORM(STATE) STATE ##_InitSubHSM();
#define BUMPER_PARAM(x) (ThisEvent.EventParam & (x))

#define rate_damper 0.8

#define SE 2
#define SW 3
#define NW 4

#define MAIN_HSM 0
#define RETURN_CENTER_FSM 1
#define SEARCH_CASTLE_FSM 2
#define ALIGN_FSM 3

#define WALL_ALIGN 0
#define TAPE_ALIGN 1

uint8_t beaconlock;

#include "TimerList.h"

#endif