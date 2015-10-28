#ifndef LEAVE_HOME_2NDLEVEL_H
#define LEAVE_HOME_2NDLEVEL_H

#include "ES_Configure.h"
#include "ES_Framework.h"

#include "globalmacros.h"

#define LEAVE_HOME_ENUMFORM(STATE) LEAVE_HOME_##STATE,

#define LIST_OF_LEAVE_HOME_STATES(STATE)\
    STATE(FORWARD)\
    STATE(CCW90)\
    STATE(CCW45)\
    STATE(CCW180_REVERSE)\
    STATE(CCW180)\
    STATE(READY_CCW90)\
    STATE(CHECK_TW)\
    STATE(START_POINT)\

uint8_t START_POINT_InitSubHSM(void);
ES_Event START_POINT_RunSubHSM(ES_Event ThisEvent);


extern int ccw_L;
extern int ccw_R;
extern int ccw90_Time;
extern int ccw180_Time;

extern int wall_ccw_L;
extern int wall_ccw_R;
extern int wall_ccw90_Time;
extern int wall_ccw180_Time;


extern int forward_L;
extern int forward_R;

extern int align;
extern int align_Time;

extern int reverse_L;
extern int reverse_R;
extern int reverse_Time;

#endif
