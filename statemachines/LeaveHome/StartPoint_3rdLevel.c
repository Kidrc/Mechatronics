#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"

#include "LeaveHome_2ndLevel.h"

extern center_Time;

static int startpoint_ccw_L = -600 * rate_damper;
static int startpoint_ccw_R = 600 * rate_damper;
static int startpoint_ccw90_Time = 260 / rate_damper;

static int startpoint_forward_L = 700 * rate_damper;
static int startpoint_forward_R = 650 * rate_damper;

static int startpoint_forward_slow_L = 300;
static int startpoint_forward_slow_R = 300;

static int startpoint_center_L = 700 * rate_damper;
static int startpoint_center_R = 700 * rate_damper;

static int startpoint_Time = 550 / rate_damper;

static int detour_Time = 500/rate_damper;
static int deadbot_handling_ccw_L = -500*rate_damper;
static int deadbot_handling_ccw_R = 500*rate_damper;
static int deadbot_handling_ccw_Time = 450/rate_damper;

static int deadbot_handling_cw_L = 500*rate_damper;
static int deadbot_handling_cw_R = -500*rate_damper;
static int deadbot_handling_cw_Time = 480/rate_damper;

static int deadbot_handling_forward_L = 500*rate_damper;
static int deadbot_handling_forward_R = 500*rate_damper;

static int deadbot_handling_reverse_L = -500*rate_damper;
static int deadbot_handling_reverse_R = -500*rate_damper;
static int deadbot_handling_reverse_Time = 500/rate_damper;

static int startingtime = 0;
static int deadbot_Time = 0;

uint8_t startpointTurn = 0;
extern uint8_t startingCastle;
#define START_POINT_ENUMFORM(STATE) START_POINT_##STATE,

#define LIST_OF_START_POINT_STATES(STATE)\
    STATE(FORWARD)\
    STATE(BUMP_ALIGN)\
    STATE(TAPE_ALIGN)\
    STATE(REVERSE)\
    STATE(CCW90)\
    STATE(CENTER)\
    STATE(DEADBOT_HANDLING_REVERSE)\
    STATE(DEADBOT_HANDLING_CCW)\
    STATE(DEADBOT_HANDLING_CW)\
    STATE(DEADBOT_HANDLING_FORWARD)\



typedef enum {
    INIT_START_POINT_STATE = 0, LIST_OF_START_POINT_STATES(START_POINT_ENUMFORM)
} SubStartPoint_t;

static SubStartPoint_t currentState;

ES_Event START_POINT_RunSubHSM(ES_Event ThisEvent);

uint8_t START_POINT_InitSubHSM(void) {
    ES_Event returnEvent;

    currentState = INIT_START_POINT_STATE;
    returnEvent = START_POINT_RunSubHSM(INIT_EVENT);
    dbugprintf("START_POINT_INITFUNCTION, currentState = %d\n", currentState);

    return returnEvent.EventType == ES_NO_EVENT;
}

ES_Event START_POINT_RunSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE;
    SubStartPoint_t nextState;
    ES_Event PostEvent;
    static uint8_t sensor = 0;

    switch (currentState) {
        case INIT_START_POINT_STATE:
            if (ThisEvent.EventType == ES_INIT) {
                currentState = START_POINT_FORWARD;
                ThisEvent.EventType = ES_NO_EVENT;
                dbugprintf("INIT_START_POINT = %d\n", currentState);
                //makeTransition = TRUE;
            }
            break;

        case START_POINT_FORWARD:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        dbugprintf("START_POINT_FORWARD\n");
                        Motor_LeftSpeed(startpoint_forward_L);
                        Motor_RightSpeed(startpoint_forward_R);
                        ES_Timer_InitTimer(HSM_TIMER, startpoint_Time);
                        break;

                    case ES_TIMEOUT:
                        Motor_LeftSpeed(startpoint_forward_slow_L);
                        Motor_RightSpeed(startpoint_forward_slow_R);
                        break;

                    case BUMPED:
                        if (BUMPER(BUMPER_FRONT_LEFT | BUMPER_FRONT_RIGHT)) {
                            nextState = START_POINT_BUMP_ALIGN;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case TAPE:
                        nextState = START_POINT_TAPE_ALIGN;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                }
            }
            break;

        case START_POINT_BUMP_ALIGN:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    dbugprintf("START_POINT_BUMP_ALIGN\n");
                    PostEvent.EventType = START_ALIGN;
                    PostEvent.EventParam = 0;
                    sensor = 0;
                    startingCastle = 0;
                    PostAlignFSM(PostEvent);
                    break;

                case COMPLETE:
                    nextState = START_POINT_CCW90;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case START_POINT_TAPE_ALIGN:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    dbugprintf("START_POINT_TAPE_ALIGN\n");
                    PostEvent.EventType = START_ALIGN;
                    PostEvent.EventParam = 1;
                    sensor = 1;
                    startingCastle = 1;
                    PostAlignFSM(PostEvent);
                    break;

                case COMPLETE:
                    nextState = START_POINT_CCW90;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case START_POINT_CCW90:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        dbugprintf("START_POINT_CCW90\n");
//                        Motor_LeftSpeed(startpoint_ccw_L);
  //                      Motor_RightSpeed(startpoint_ccw_R);
    //                    ES_Timer_InitTimer(HSM_TIMER, startpoint_ccw90_Time);
                        startpointTurn = 1;
                        PostRotate(START_ROTATE, MAIN_HSM, startpoint_ccw_L, startpoint_ccw_R);
                        break;

                    case COMPLETE:
                        startpointTurn = 0;
                        startingtime = ES_Timer_GetTime();

                        nextState = START_POINT_CENTER;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case START_POINT_CENTER:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    dbugprintf("START_POINT_CENTER\n");
                    Motor_RightSpeed(startpoint_center_R);
                    Motor_LeftSpeed(startpoint_center_L);
                    if (deadbot_Time == 0)
                    {
                        ES_Timer_InitTimer(HSM_TIMER, center_Time);
                    }
                    else
                    {
                        ES_Timer_InitTimer(HSM_TIMER, center_Time - deadbot_Time);
                    }
                    break;

                case BUMPED:
                    if (BUMPER(BUMPER_FRONT_RIGHT|BUMPER_FRONT_LEFT))
                    {
                        deadbot_Time = ES_Timer_GetTime() - startingtime;

                        nextState = START_POINT_DEADBOT_HANDLING_REVERSE;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_TIMEOUT:
                    ThisEvent.EventType = COMPLETE;
                    ThisEvent.EventParam = sensor;
                    break;

                default:
                    break;
            }

            break;


        case START_POINT_DEADBOT_HANDLING_REVERSE:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Motor_LeftSpeed(deadbot_handling_reverse_L);
                    Motor_RightSpeed(deadbot_handling_reverse_R);
                    ES_Timer_InitTimer(HSM_TIMER, deadbot_handling_reverse_Time);
                    break;

                case ES_TIMEOUT:
                    nextState = START_POINT_DEADBOT_HANDLING_CCW;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case START_POINT_DEADBOT_HANDLING_CCW:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    Motor_LeftSpeed(deadbot_handling_ccw_L);
                    Motor_RightSpeed(deadbot_handling_ccw_R);
                    ES_Timer_InitTimer(HSM_TIMER, deadbot_handling_ccw_Time);
                    break;

                case ES_TIMEOUT:
                    nextState = START_POINT_DEADBOT_HANDLING_FORWARD;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case START_POINT_DEADBOT_HANDLING_FORWARD:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    Motor_LeftSpeed(deadbot_handling_forward_L);
                    Motor_RightSpeed(deadbot_handling_forward_R);
                    ES_Timer_InitTimer(HSM_TIMER, detour_Time);
                    break;

                case BUMPED:
                    if (BUMPER(BUMPER_FRONT_LEFT | BUMPER_FRONT_RIGHT)) {
                        case TAPE:
                        nextState = START_POINT_DEADBOT_HANDLING_CW;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_TIMEOUT:
                    nextState = START_POINT_DEADBOT_HANDLING_CW;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case START_POINT_DEADBOT_HANDLING_CW:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    Motor_LeftSpeed(deadbot_handling_cw_L);
                    Motor_RightSpeed(deadbot_handling_cw_R);
                    ES_Timer_InitTimer(HSM_TIMER, deadbot_handling_cw_Time);
                    break;

                case ES_TIMEOUT:
                    nextState = START_POINT_CENTER;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;


        default:
            break;
    }

    if (makeTransition) {
        START_POINT_RunSubHSM(EXIT_EVENT);
        currentState = nextState;
        START_POINT_RunSubHSM(ENTRY_EVENT);
    }

    return ThisEvent;
}

