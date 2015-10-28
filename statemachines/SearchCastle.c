
#include "SearchCastle.h"

#include "hodor_motors.h"
#include "hodor_sensors.h"

#define SEARCH_CASTLE_ENUMFORM(STATE) SEARCH_CASTLE_ ## STATE,

#define LIST_OF_SEARCH_CASTLE_STATES(STATE)\
    STATE(IDLE)\
    STATE(ALIGN_1ST)\
    STATE(ALIGN_2ND)\
    STATE(CW90_1ST)\
    STATE(BACK_ADJUST_2ND)\
    STATE(FORWARD_1ST)\
    STATE(FORWARD_2ND)\
    STATE(CW90_2ND)\
    STATE(BACK_ADJUST_1ST_CW)\
    STATE(BACK_ADJUST_1ST_CCW)\
    STATE(DEADBOT_HANDLING_CCW)\
    STATE(DEADBOT_HANDLING_CW)\
    STATE(DEADBOT_HANDLING_FORWARD)\
    STATE(DEADBOT_HANDLING_REVERSE)\

typedef enum
{
    INIT_SEARCH_CASTLE_STATE=0, LIST_OF_SEARCH_CASTLE_STATES(SEARCH_CASTLE_ENUMFORM)
}SearchCastle_t;

static SearchCastle_t currentState;

static int search_cw90_1st_R = -280*rate_damper;
static int search_cw90_1st_L = 600*rate_damper;
static int search_cw90_1st_Time = 470/rate_damper;

static int search_cw90_2nd_R = -500*rate_damper;
static int search_cw90_2nd_L = 470*rate_damper;
static int search_cw90_2nd_Time = 370/rate_damper;

static int search_forward_1st_L= 700*rate_damper;
static int search_forward_1st_R = 690*rate_damper;

static int search_forward_2nd_L= 550*rate_damper;
static int search_forward_2nd_R = 700*rate_damper;


static int crown_cw90_1st_R = -280*rate_damper;
static int crown_cw90_1st_L = 600*rate_damper;
static int crown_cw90_1st_Time = 430/rate_damper;

static int crown_cw90_2nd_R = -500*rate_damper;
static int crown_cw90_2nd_L = 470*rate_damper;
static int crown_cw90_2nd_Time = 400/rate_damper;

static int crown_forward_1st_L= 650*rate_damper;
static int crown_forward_1st_R = 620*rate_damper;

static int crown_forward_2nd_L= 590*rate_damper;
static int crown_forward_2nd_R = 700*rate_damper;

static int search_turning_limit_Time = 1000;

static int back_adjust_L = 0*rate_damper;
static int back_adjust_R = -600*rate_damper;
static int back_adjust_Time = 300/rate_damper;

static int back_adjust_cw_L = -200*rate_damper;
static int back_adjust_cw_R = -600*rate_damper;
static int back_adjust_cw_Time = 350/rate_damper;

static int back_adjust_ccw_L = -600*rate_damper;
static int back_adjust_ccw_R = -200*rate_damper;
static int back_adjust_ccw_Time = 350/rate_damper;

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

uint8_t crownTurn = 0;

static uint8_t MyPriority;

uint8_t PostSearchCastleFSM(ES_Event ThisEvent)
{
	return ES_PostToService(MyPriority, ThisEvent);
}


uint8_t SEARCH_CASTLE_InitFSM(uint8_t Priority)
{
    MyPriority = Priority;
    currentState = INIT_SEARCH_CASTLE_STATE;
    dbugprintf("SEARCH_CASTLE_INITFUNCTION, currentState = %d\n", currentState);

    return ES_PostToService(MyPriority, INIT_EVENT);
}


ES_Event SEARCH_CASTLE_RunFSM(ES_Event ThisEvent)
{
    ES_Event PostEvent;
    uint8_t makeTransition = FALSE;
    SearchCastle_t nextState;
    static uint8_t source = 0;
    static uint8_t type = 0;
    static uint8_t turning_limit_timeout = 0;
    static uint8_t castleType = 0;
    static uint8_t deadbot_timeout = 0;
    static int detour_Time = 500;
    static uint8_t detour_direction = 0;
    static uint8_t fail_times = 0;
    
    switch(currentState)
    {
        case INIT_SEARCH_CASTLE_STATE:
            if(ThisEvent.EventType == ES_INIT)
            {
                currentState = SEARCH_CASTLE_IDLE;
                ThisEvent.EventType = ES_NO_EVENT;
                dbugprintf("INIT_SEARCH_CASTLE_SE = %d\n", currentState);
                //makeTransition = TRUE;
            }
            break;

        case SEARCH_CASTLE_IDLE:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    turning_limit_timeout = 0;
                    deadbot_timeout = 0;
                    beaconlock = 0;
                   break;

                case START_SEARCH:
                    beaconlock = 1;
                    source = (ThisEvent.EventParam & 0x06) >> 1;
                    type = 0;
                    detour_direction = castleType = ThisEvent.EventParam & 0x01;

                    nextState = SEARCH_CASTLE_FORWARD_1ST;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                case RETURN_HOME_CASTLE:
                    source = (ThisEvent.EventParam & 0x06) >> 1;
                    type = 1;
                    castleType = ThisEvent.EventParam & 0x01;

                    nextState = SEARCH_CASTLE_FORWARD_1ST;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;           
                    
                default:
                    break;
            }
            break;

        case SEARCH_CASTLE_FORWARD_1ST:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                            ES_Timer_InitTimer(SEARCH_CASTLE_TIMER, deadbot_Time);

                        if (type == 0)
                        {
                            Motor_RightSpeed(search_forward_1st_R);
                            Motor_LeftSpeed(search_forward_1st_L);
                        }
                        else
                        {
                            Motor_RightSpeed(crown_forward_1st_R);
                            Motor_LeftSpeed(crown_forward_1st_L);   
                        }
                        dbugprintf("SEARCH_CASTLE_FORWARD_1ST\n");
                        break;

                    case BUMPED:
                        if (BUMPER(BUMPER_FRONT_LEFT|BUMPER_FRONT_RIGHT))
                        {
                            if (deadbot_timeout)
                            {
                                nextState = SEARCH_CASTLE_ALIGN_1ST;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                            else
                            {
                                detour_direction = castleType;

                                nextState = SEARCH_CASTLE_DEADBOT_HANDLING_REVERSE;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                        }
                        break;

                    case TAPE:
                        //if (!deadbot_timeout)
                        if (0)
                        {
                            nextState = SEARCH_CASTLE_DEADBOT_HANDLING_REVERSE;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        else
                        {
                            if (castleType == 0)
                            {
                                nextState = SEARCH_CASTLE_BACK_ADJUST_1ST_CCW;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                            else
                            {
                                nextState = SEARCH_CASTLE_BACK_ADJUST_1ST_CW;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                        }
                        break;

                    case ES_TIMEOUT:
                        deadbot_timeout = 1;
                        break;

                    default:
                        break;
                }
            }
            break;

        case SEARCH_CASTLE_DEADBOT_HANDLING_REVERSE:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Motor_LeftSpeed(deadbot_handling_reverse_L);
                    Motor_RightSpeed(deadbot_handling_reverse_R);
                    ES_Timer_InitTimer(SEARCH_CASTLE_TIMER, deadbot_handling_reverse_Time);
                    break;

                case ES_TIMEOUT:
                    if (detour_direction == 0)
                    {
                        nextState = SEARCH_CASTLE_DEADBOT_HANDLING_CCW;
                    }
                    else
                    {
                        nextState = SEARCH_CASTLE_DEADBOT_HANDLING_CW;
                    }

                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case SEARCH_CASTLE_DEADBOT_HANDLING_CCW:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Motor_LeftSpeed(deadbot_handling_ccw_L);
                    Motor_RightSpeed(deadbot_handling_ccw_R);
                    ES_Timer_InitTimer(SEARCH_CASTLE_TIMER, deadbot_handling_ccw_Time);
                    break;

                case ES_TIMEOUT:
                    if (detour_direction == 0)
                        nextState = SEARCH_CASTLE_DEADBOT_HANDLING_FORWARD;
                    else
                        nextState = SEARCH_CASTLE_FORWARD_1ST;

                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case SEARCH_CASTLE_DEADBOT_HANDLING_FORWARD:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Motor_LeftSpeed(deadbot_handling_forward_L);
                    Motor_RightSpeed(deadbot_handling_forward_R);
                    ES_Timer_InitTimer(SEARCH_CASTLE_TIMER, detour_Time);
                    break;

                case BUMPED:
                    if (BUMPER(BUMPER_FRONT_LEFT|BUMPER_FRONT_RIGHT))
                    {
                case TAPE:
                        if (detour_direction == 0)
                            nextState = SEARCH_CASTLE_DEADBOT_HANDLING_CW;
                        else
                            nextState = SEARCH_CASTLE_DEADBOT_HANDLING_CCW;

                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                case ES_TIMEOUT:
                    if (detour_direction == 0)
                        nextState = SEARCH_CASTLE_DEADBOT_HANDLING_CW;
                    else
                        nextState = SEARCH_CASTLE_DEADBOT_HANDLING_CCW;

                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case SEARCH_CASTLE_DEADBOT_HANDLING_CW:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Motor_LeftSpeed(deadbot_handling_cw_L);
                    Motor_RightSpeed(deadbot_handling_cw_R);
                    ES_Timer_InitTimer(SEARCH_CASTLE_TIMER, deadbot_handling_cw_Time);
                    break;

                case ES_TIMEOUT:
                    if (detour_direction == 0)
                        nextState = SEARCH_CASTLE_FORWARD_1ST;
                    else
                        nextState = SEARCH_CASTLE_DEADBOT_HANDLING_FORWARD;

                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case SEARCH_CASTLE_BACK_ADJUST_1ST_CCW:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                     Motor_LeftSpeed(back_adjust_ccw_L);
                     Motor_RightSpeed(back_adjust_ccw_R);
                     ES_Timer_InitTimer(SEARCH_CASTLE_TIMER, back_adjust_ccw_Time);
                     break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == SEARCH_CASTLE_TIMER)
                    {
                    nextState = SEARCH_CASTLE_FORWARD_1ST;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
            }
            break;

        case SEARCH_CASTLE_BACK_ADJUST_1ST_CW:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                     Motor_LeftSpeed(back_adjust_cw_L);
                     Motor_RightSpeed(back_adjust_cw_R);
                     ES_Timer_InitTimer(SEARCH_CASTLE_TIMER, back_adjust_cw_Time);
                     break;

                case ES_TIMEOUT:
                    nextState = SEARCH_CASTLE_FORWARD_1ST;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;


        case SEARCH_CASTLE_ALIGN_1ST:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        dbugprintf("SEARCH_CASTLE_ALIGN_1ST\n");
                        PostAlign(START_ALIGN, WALL_ALIGN, SEARCH_CASTLE_FSM);
                        break;

                    case COMPLETE:
                        nextState = SEARCH_CASTLE_CW90_1ST;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case SEARCH_CASTLE_CW90_1ST:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        /*if (type == 0)
                        {
                             Motor_LeftSpeed(search_cw90_1st_L);
                            Motor_RightSpeed(search_cw90_1st_R);
                            ES_Timer_InitTimer(SEARCH_CASTLE_TIMER, search_cw90_1st_Time);
                        }
                        else
                        {
                            Motor_RightSpeed(crown_cw90_1st_R);
                            Motor_LeftSpeed(crown_cw90_1st_L);
                            ES_Timer_InitTimer(SEARCH_CASTLE_TIMER, crown_cw90_1st_Time);
                        }
                        */
                        PostRotate(START_ROTATE, SEARCH_CASTLE_FSM, search_cw90_1st_L, search_cw90_1st_R);
                        break;

                    case COMPLETE:
                        nextState = SEARCH_CASTLE_FORWARD_2ND;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case SEARCH_CASTLE_FORWARD_2ND:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        if (type == 0)
                        {
                            Motor_RightSpeed(search_forward_2nd_R);
                            Motor_LeftSpeed(search_forward_2nd_L);
                        }
                        else
                        {
                            Motor_RightSpeed(crown_forward_2nd_R);
                            Motor_LeftSpeed(crown_forward_2nd_L);
                        }
                        ES_Timer_InitTimer(SEARCH_CASTLE_TIMER, search_turning_limit_Time);
                        break;

                    case BUMPED:
                        if (BUMPER(BUMPER_FRONT_LEFT|BUMPER_FRONT_RIGHT))
                        {
                            if (0& !turning_limit_timeout)
                            {
                                nextState = SEARCH_CASTLE_BACK_ADJUST_2ND;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                            else
                            {
                                nextState = SEARCH_CASTLE_ALIGN_2ND;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                        }
                        break;


                    case ES_TIMEOUT:
                        turning_limit_timeout = 1;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case SEARCH_CASTLE_BACK_ADJUST_2ND:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                     Motor_LeftSpeed(back_adjust_L);
                     Motor_RightSpeed(back_adjust_R);
                     ES_Timer_InitTimer(SEARCH_CASTLE_TIMER, back_adjust_Time);
                     break;

                case ES_TIMEOUT:
                    nextState = SEARCH_CASTLE_FORWARD_2ND;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case SEARCH_CASTLE_ALIGN_2ND:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        PostEvent.EventType = START_ALIGN;
                        PostEvent.EventParam = WALL_ALIGN|(SEARCH_CASTLE_FSM << 1);
                        PostAlignFSM(PostEvent);
                        break;

                    case COMPLETE:
                        nextState = SEARCH_CASTLE_CW90_2ND;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case SEARCH_CASTLE_CW90_2ND:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        /*
                        if (type == 0)
                        {
                             Motor_LeftSpeed(search_cw90_2nd_L);
                            Motor_RightSpeed(search_cw90_2nd_R);
                            ES_Timer_InitTimer(SEARCH_CASTLE_TIMER, search_cw90_2nd_Time);
                        }
                        else
                        {
                            Motor_RightSpeed(crown_cw90_2nd_R);
                            Motor_LeftSpeed(crown_cw90_2nd_L);
                            ES_Timer_InitTimer(SEARCH_CASTLE_TIMER, crown_cw90_2nd_Time);
                        }
                        break;

                    case ES_TIMEOUT:
                        PostEvent.EventType = COMPLETE;
                        PostToplevelHSM(PostEvent);

                        nextState = SEARCH_CASTLE_IDLE;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                         */
                        crownTurn = 1;
                        PostRotate(START_ROTATE, SEARCH_CASTLE_FSM, crown_cw90_2nd_L, crown_cw90_2nd_R);
                        break;

                    case COMPLETE:
                        crownTurn = 0;
                        PostEvent.EventType = COMPLETE;
                        PostToplevelHSM(PostEvent);
                        nextState = SEARCH_CASTLE_IDLE;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                    default:
                        break;
                }
            }
            break;

        default:
            break;
    }

    if (makeTransition)
    {
        SEARCH_CASTLE_RunFSM(EXIT_EVENT);
        currentState = nextState;
        SEARCH_CASTLE_RunFSM(ENTRY_EVENT);
    }

}

void PostSearchCastle(ES_EventTyp_t EventType, uint8_t castleType, uint8_t src)
{
    ES_Event PostEvent;

    PostEvent.EventType = EventType;
    PostEvent.EventParam = castleType|(src << 1);
    dbugprintf("postsearchsrc = %d\n", src);
    PostSearchCastleFSM(PostEvent);
}