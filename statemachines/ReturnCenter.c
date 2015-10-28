
#include "ReturnCenter.h"

#include "hodor_motors.h"
#include "hodor_sensors.h"

#define RETURN_CENTER_ENUMFORM(STATE) STATE,

#define LIST_OF_RETURN_CENTER_STATES(STATE)\
STATE(CW90)\
STATE(FORWARD)\
STATE(BACK_ADJUST_1ST_CCW)\
STATE(IDLE)\
STATE(CCW90)\
STATE(FORWARD_2ND)\
STATE(BACK_ADJUST_2ND_CW)\
STATE(BACK_ADJUST_2ND_CCW)\
STATE(DEADBOT_HANDLING_CW)\
STATE(DEADBOT_HANDLING_CCW)\
STATE(DEADBOT_HANDLING_FORWARD)\
STATE(DEADBOT_HANDLING_REVERSE)\

extern uint8_t crownTurn;
typedef enum
{
    INIT_RETURN_CENTER_STATE=0, LIST_OF_RETURN_CENTER_STATES(RETURN_CENTER_ENUMFORM)
}ReturnCenter_t;

static ReturnCenter_t currentState;

static int return_cw90_R = -700*rate_damper;
static int return_cw90_L = 400*rate_damper;
static int return_cw90_Time = 570/rate_damper;

extern int reverse_L;
extern int reverse_R;
extern int reverse_Time;

extern int ccw_L;
extern int ccw_R;
extern int ccw90_Time;

static int return_forward_fast_L = 600*rate_damper;
static int return_forward_fast_R = 500*rate_damper;

static int return_forward_L = 300;
static int return_forward_R = 300;

static int return_forward_2nd_L = 700*rate_damper;
static int return_forward_2nd_R = 700*rate_damper;

static int return_ccw90_R = 600*rate_damper;
static int return_ccw90_L = -600*rate_damper;
static int return_ccw90_Time = 250/rate_damper;


static int back_adjust_cw_L = 0*rate_damper;
static int back_adjust_cw_R = -600*rate_damper;
static int back_adjust_cw_Time = 250/rate_damper;

static int back_adjust_ccw_L = -600*rate_damper;
static int back_adjust_ccw_R = 0*rate_damper;
static int back_adjust_ccw_Time = 250/rate_damper;


static int deadbot_Time = 800*0.6/rate_damper;

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

static int forward_Time = 1200*0.7/rate_damper;
static int forward_detect_Time = 1200;

extern int center_Time;

static TopState_t CurrentState = INIT_TOPSTATE;
static uint8_t MyPriority;

uint8_t returnTurn = 0;

uint8_t PostReturnCenterFSM(ES_Event ThisEvent)
{
	return ES_PostToService(MyPriority, ThisEvent);
}


uint8_t RETURN_CENTER_InitFSM(uint8_t Priority)
{
    MyPriority = Priority;
    currentState = INIT_RETURN_CENTER_STATE;
    dbugprintf("RETURN_CENTER_INITFUNCTION, currentState = %d\n", currentState);

    return ES_PostToService(MyPriority, INIT_EVENT);
}


ES_Event RETURN_CENTER_RunFSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE;
    ReturnCenter_t nextState;
    uint8_t temp1, temp2;
    static uint8_t sensor = 0;
    ES_Event PostEvent;
    static uint8_t forward_timeout = 0;

    static uint8_t startingtime = 0;
    static uint8_t deadbot_timeout = 0;
    static int detour_Time = 600;
    static uint8_t detour_direction = 0;
    static uint8_t fail_times = 0;
    static uint8_t deadbotTime = 0;

    switch(currentState)
    {
        case INIT_RETURN_CENTER_STATE:
            if (ThisEvent.EventType == ES_INIT)
            {
                currentState = IDLE;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            break;

        case IDLE:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    break;

                case RETURN_CENTER:
                    detour_direction = sensor = ThisEvent.EventParam & 0x01;

                    nextState = CW90;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case CW90:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        dbugprintf("RETURN_CENTER\n");
/*
                        Motor_LeftSpeed(return_cw90_L);
                        Motor_RightSpeed(return_cw90_R);
                        ES_Timer_InitTimer(RETURN_CENTER_TIMER, return_cw90_Time);
                        break;

                    case ES_TIMEOUT:*/
                        PostRotate(START_ROTATE, RETURN_CENTER_FSM, return_cw90_L, return_cw90_R);
                        break;

                    case COMPLETE:
                        nextState = FORWARD;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case FORWARD:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        Motor_LeftSpeed(return_forward_fast_L);
                        Motor_RightSpeed(return_forward_fast_R);
                        ES_Timer_InitTimer(RETURN_CENTER_TIMER, forward_Time);
                        break;

                    case ES_TIMEOUT:
                        forward_timeout = 1;
                        Motor_LeftSpeed(return_forward_L);
                        Motor_RightSpeed(return_forward_R);
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    case BUMPED:
                        if (BUMPER(BUMPER_FRONT_LEFT|BUMPER_FRONT_RIGHT))
                        {
                            if (forward_timeout)
                            {
                                PostEvent.EventType = START_ALIGN;
                                PostEvent.EventParam = 0 | (RETURN_CENTER_FSM << 1);
                                PostAlignFSM(PostEvent);

                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                            else
                            {
                                nextState = BACK_ADJUST_1ST_CCW;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }

                        }
                        break;

                    case TAPE:
                        PostEvent.EventType = START_ALIGN;
                        PostEvent.EventParam = 1|(RETURN_CENTER_FSM << 1);
                        PostAlignFSM(PostEvent);
                        ThisEvent.EventType = ES_NO_EVENT;

                        break;

                    case COMPLETE:
                        nextState = CCW90;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case CCW90:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
/*                        Motor_LeftSpeed(return_ccw90_L);
                        Motor_RightSpeed(return_ccw90_R);
                        ES_Timer_InitTimer(RETURN_CENTER_TIMER, return_ccw90_Time);
                        break;

                    case ES_TIMEOUT:
 */
                        returnTurn = 1;
                        PostRotate(START_ROTATE, RETURN_CENTER_FSM, return_ccw90_L, return_ccw90_R);
                        break;

                    case COMPLETE:
                        returnTurn  =0;
                        startingtime = ES_Timer_GetTime();
                        nextState = FORWARD_2ND;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case FORWARD_2ND:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        Motor_LeftSpeed(return_forward_2nd_L);
                        Motor_RightSpeed(return_forward_2nd_R);
                        if (deadbotTime)
                        {
                            ES_Timer_InitTimer(RETURN_CENTER_TIMER, center_Time - deadbotTime);
                        }
                        else
                        {
                            ES_Timer_InitTimer(RETURN_CENTER_TIMER, center_Time);
                        }
                        break;

                    case ES_TIMEOUT:
                        dbugprintf("RETURNED\n");
                        PostEvent.EventType = COMPLETE;
                        PostToplevelHSM(PostEvent);

                        nextState = IDLE;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    case BUMPED:
                        if (BUMPER(BUMPER_FRONT_LEFT|BUMPER_FRONT_RIGHT))
                        {
                            deadbotTime = ES_Timer_GetTime() - startingtime;
                            nextState = DEADBOT_HANDLING_REVERSE;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case TAPE:
                        if (sensor == 0)
                        {
                            nextState = BACK_ADJUST_2ND_CW;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        else
                        {
                            nextState = BACK_ADJUST_2ND_CCW;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;
                    default:
                        break;
                }
            }
            break;

        case DEADBOT_HANDLING_REVERSE:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Motor_LeftSpeed(deadbot_handling_reverse_L);
                    Motor_RightSpeed(deadbot_handling_reverse_R);
                    ES_Timer_InitTimer(RETURN_CENTER_TIMER, deadbot_handling_reverse_Time);
                    break;

                case ES_TIMEOUT:
                    if (detour_direction == 0)
                    {
                        nextState = DEADBOT_HANDLING_CCW;
                    }
                    else
                    {
                        nextState = DEADBOT_HANDLING_CW;
                    }

                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case DEADBOT_HANDLING_CCW:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Motor_LeftSpeed(deadbot_handling_ccw_L);
                    Motor_RightSpeed(deadbot_handling_ccw_R);
                    ES_Timer_InitTimer(RETURN_CENTER_TIMER, deadbot_handling_ccw_Time);
                    break;

                case ES_TIMEOUT:
                    if (detour_direction == 0)
                        nextState = DEADBOT_HANDLING_FORWARD;
                    else
                        nextState = FORWARD_2ND;

                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case DEADBOT_HANDLING_FORWARD:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Motor_LeftSpeed(deadbot_handling_forward_L);
                    Motor_RightSpeed(deadbot_handling_forward_R);
                    ES_Timer_InitTimer(RETURN_CENTER_TIMER, detour_Time);
                    break;

                case BUMPED:
                    if (BUMPER(BUMPER_FRONT_LEFT|BUMPER_FRONT_RIGHT))
                    {
                case TAPE:
                        if (detour_direction == 0)
                            nextState = DEADBOT_HANDLING_CW;
                        else
                            nextState = DEADBOT_HANDLING_CCW;

                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_TIMEOUT:
                    if (detour_direction == 0)
                        nextState = DEADBOT_HANDLING_CW;
                    else
                        nextState = DEADBOT_HANDLING_CCW;

                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case DEADBOT_HANDLING_CW:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Motor_LeftSpeed(deadbot_handling_cw_L);
                    Motor_RightSpeed(deadbot_handling_cw_R);
                    ES_Timer_InitTimer(RETURN_CENTER_TIMER, deadbot_handling_cw_Time);
                    break;

                case ES_TIMEOUT:
                    if (detour_direction == 0)
                        nextState = FORWARD_2ND;
                    else
                        nextState = DEADBOT_HANDLING_FORWARD;

                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case BACK_ADJUST_1ST_CCW:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                     Motor_LeftSpeed(back_adjust_ccw_L);
                     Motor_RightSpeed(back_adjust_ccw_R);
                     ES_Timer_InitTimer(RETURN_CENTER_TIMER, back_adjust_ccw_Time);
                     break;

                case ES_TIMEOUT:
                    nextState = FORWARD;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case BACK_ADJUST_2ND_CCW:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                     Motor_LeftSpeed(back_adjust_ccw_L);
                     Motor_RightSpeed(back_adjust_ccw_R);
                     ES_Timer_InitTimer(RETURN_CENTER_TIMER, back_adjust_ccw_Time);
                     break;

                case ES_TIMEOUT:
                    nextState = FORWARD_2ND;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;
            
        case BACK_ADJUST_2ND_CW:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                     Motor_LeftSpeed(back_adjust_cw_L);
                     Motor_RightSpeed(back_adjust_cw_R);
                     ES_Timer_InitTimer(RETURN_CENTER_TIMER, back_adjust_cw_Time);
                     break;

                case ES_TIMEOUT:
                    nextState = FORWARD_2ND;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        default:
            break;
    }

    if (makeTransition)
    {
        RETURN_CENTER_RunFSM(EXIT_EVENT);
        currentState = nextState;
        RETURN_CENTER_RunFSM(ENTRY_EVENT);
    }
}

void PostReturnCenter(ES_EventTyp_t EventType, uint8_t sensor, uint8_t src)
{
    ES_Event PostEvent;

    PostEvent.EventType = EventType;
    PostEvent.EventParam = sensor|(src << 1);
    PostReturnCenterFSM(PostEvent);
}
