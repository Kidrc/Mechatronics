
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

#define SEARCH_CASTLE_SW_ENUMFORM(STATE) SEARCH_CASTLE_SW_##STATE,

#define LIST_OF_SEARCH_CASTLE_SW_STATES(STATE)\
    STATE(SEARCH)\
    STATE(DETECTING)\
    STATE(CCW90)\
    STATE(RETURN_CENTER)\

typedef enum
{
    INIT_SEARCH_CASTLE_SW_STATE=0, LIST_OF_SEARCH_CASTLE_SW_STATES(SEARCH_CASTLE_SW_ENUMFORM)
}SubSearchSW_t;

static SubSearchSW_t currentState;

ES_Event SEARCH_CASTLE_SW_RunSubHSM(ES_Event ThisEvent);

uint8_t SEARCH_CASTLE_SW_InitSubHSM(void)
{
    ES_Event returnEvent;

    currentState = INIT_SEARCH_CASTLE_SW_STATE;
    returnEvent = SEARCH_CASTLE_SW_RunSubHSM(INIT_EVENT);
    dbugprintf("SEARCH_CASTLE_SW_INITFUNCTION, currentState = %d\n", currentState);

    return returnEvent.EventType == ES_NO_EVENT;
}


ES_Event SEARCH_CASTLE_SW_RunSubHSM(ES_Event ThisEvent)
{
    ES_Event PostEvent;
    uint8_t makeTransition = FALSE;
    SubSearchSW_t nextState;
    uint16_t temp1 = 0, temp2 = 0;
    static uint8_t once = 0;
    static uint8_t timeout = 0;
    static uint8_t beacon = 0;

    switch(currentState)
    {
        case INIT_SEARCH_CASTLE_SW_STATE:
            if(ThisEvent.EventType == ES_INIT)
            {
                currentState = SEARCH_CASTLE_SW_CCW90;
                ThisEvent.EventType = ES_NO_EVENT;
                dbugprintf("INIT_SEARCH_CASTLE_SW = %d\n", currentState);
                //makeTransition = TRUE;
            }
            break;

        case SEARCH_CASTLE_SW_CCW90:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        dbugprintf("SEARCH_CASTLE_SW_CCW90\n");
                        Motor_RightSpeed(findruling_ccw_R);
                        Motor_LeftSpeed(findruling_ccw_L);
                        HSM_LEDSubIndicate(0x04);
                        ES_Timer_InitTimer(HSM_TIMER, findruling_ccw90_Time);
                        break;

                    case ES_TIMEOUT:
                        nextState = SEARCH_CASTLE_SW_SEARCH;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case SEARCH_CASTLE_SW_SEARCH:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        PostSearchCastle(START_SEARCH, startingCastle, MAIN_HSM);
                        break;

                    case FOUND_BEACON:
                        beacon = 1;
                        break;

                    case COMPLETE:
                        if (beacon)
                        {
                            ThisEvent.EventType = FOUND_RULING;
                            currentObstacleType = !startingCastle;
                            location = SW;
                        }
                        else
                        {
                            nextState = SEARCH_CASTLE_SW_RETURN_CENTER;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    default:
                        break;
                }
            }
            break;

        case SEARCH_CASTLE_SW_RETURN_CENTER:
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
            break;

        default:
            break;
    }

    if (makeTransition)
    {
        SEARCH_CASTLE_SW_RunSubHSM(EXIT_EVENT);
        currentState = nextState;
        SEARCH_CASTLE_SW_RunSubHSM(ENTRY_EVENT);
    }

    return ThisEvent;
}

