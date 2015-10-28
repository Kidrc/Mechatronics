
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"

#include "FindRuling_2ndLevel.h"
#include "globalmacros.h"
#include "hodor_sensors.h"

static int cw90_1st_R = -280*rate_damper;
static int cw90_1st_L = 600*rate_damper;
static int cw90_1st_Time = 480/rate_damper;

static int cw90_2nd_R = -570*rate_damper;
static int cw90_2nd_L = 470*rate_damper;
static int cw90_2nd_Time = 370/rate_damper;

static int forward_1st_L = 700*rate_damper;
static int forward_1st_R = 670*rate_damper;

static int forward_2nd_L = 620*rate_damper;
static int forward_2nd_R = 700*rate_damper;

static int sample_Time = 50;

#define SEARCH_CASTLE_SE_ENUMFORM(STATE) SEARCH_CASTLE_SE_##STATE,

#define LIST_OF_SEARCH_CASTLE_SE_STATES(STATE)\
    STATE(SEARCH)\
    STATE(DETECTING)\
    STATE(CCW90)\
    STATE(RETURN_CENTER)\
STATE(DEADBOT_TURNING)\

typedef enum
{
    INIT_SEARCH_CASTLE_SE_STATE=0, LIST_OF_SEARCH_CASTLE_SE_STATES(SEARCH_CASTLE_SE_ENUMFORM)
}SubSearchSE_t;

static SubSearchSE_t currentState;

ES_Event SEARCH_CASTLE_SE_RunSubHSM(ES_Event ThisEvent);

uint8_t SEARCH_CASTLE_SE_InitSubHSM(void)
{
    ES_Event returnEvent;

    currentState = INIT_SEARCH_CASTLE_SE_STATE;
    returnEvent = SEARCH_CASTLE_SE_RunSubHSM(INIT_EVENT);
    dbugprintf("SEARCH_CASTLE_SE_INITFUNCTION, currentState = %d\n", currentState);

    return returnEvent.EventType == ES_NO_EVENT;
}


ES_Event SEARCH_CASTLE_SE_RunSubHSM(ES_Event ThisEvent)
{
    ES_Event PostEvent;
    uint8_t makeTransition = FALSE;
    SubSearchSE_t nextState;
    uint16_t temp1 = 0, temp2 = 0;
    static uint8_t once = 0;
    static uint8_t timeout = 0;

    switch(currentState)
    {
        case INIT_SEARCH_CASTLE_SE_STATE:
            if(ThisEvent.EventType == ES_INIT)
            {
                currentState = SEARCH_CASTLE_SE_CCW90;
                ThisEvent.EventType = ES_NO_EVENT;
                dbugprintf("INIT_SEARCH_CASTLE_SE = %d\n", currentState);
                //makeTransition = TRUE;
            }
            break;

        case SEARCH_CASTLE_SE_CCW90:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    /*
                    case ES_ENTRY:
                        dbugprintf("SEARCH_CASTLE_SE_CCW90\n");
                        Motor_RightSpeed(findruling_ccw_R);
                        Motor_LeftSpeed(findruling_ccw_L);
                        HSM_LEDSubIndicate(0x04);
                        ES_Timer_InitTimer(HSM_TIMER, findruling_ccw90_Time);
                        break;

                    case BUMPED:
                        if (BUMPER(BUMPER_LEFT))
                        {
                            ES_Timer_StopTimer(HSM_TIMER);
                            nextState = SEARCH_CASTLE_SE_DEADBOT_TURNING;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case ES_TIMEOUT:
                        nextState = SEARCH_CASTLE_SE_SEARCH;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
*/
                    case ES_ENTRY:
                        PostRotate(START_ROTATE, MAIN_HSM, findruling_ccw_L, findruling_ccw_R);
                        break;

                    case COMPLETE:
                        nextState = SEARCH_CASTLE_SE_SEARCH;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                        
                    default:
                        break;
                }
            }
            break;
/*
        case SEARCH_CASTLE_SE_DEADBOT_TURNING:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    ES_Timer_InitTimer(HSM_TIMER, )
                default:
                    break;
            }
            break;
 */
        case SEARCH_CASTLE_SE_SEARCH:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        PostSearchCastle(START_SEARCH, !startingCastle, MAIN_HSM);
                        break;

                    case COMPLETE:
                            ThisEvent.EventType = FOUND_RULING;
                            currentObstacleType = !startingCastle;
                            location = SE;
                        break;

                    default:
                        break;
                }
            }
            break;

        case SEARCH_CASTLE_SE_RETURN_CENTER:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    PostEvent.EventType = RETURN_CENTER;
                    PostEvent.EventParam = (!startingCastle)|(MAIN_HSM << 1);
                    PostReturnCenterFSM(PostEvent);
                    break;

                case COMPLETE:
                    ThisEvent.EventType = NOT_FOUND_RULING;
                    break;

                default:
                    break;
            }


        default:
            break;
    }

    if (makeTransition)
    {
        SEARCH_CASTLE_SE_RunSubHSM(EXIT_EVENT);
        currentState = nextState;
        SEARCH_CASTLE_SE_RunSubHSM(ENTRY_EVENT);
    }

    return ThisEvent;
}

