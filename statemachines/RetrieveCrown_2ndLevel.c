

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"

#include "globalmacros.h"
#include "hodor_sensors.h"
#include "hodor_mech.h"

extern uint8_t currentObstacleType;
extern uint8_t location;

#define RETRIEVE_CROWN_ENUMFORM(STATE) RETRIEVE_CROWN_##STATE,

#define LIST_OF_RETRIEVE_CROWN_STATES(STATE)\
    STATE(FORWARD)\
    STATE(IDLE)\
    STATE(FORK_UP)\
    STATE(REVERSE)\
    STATE(RETURN)\
    STATE(TURN)\

typedef enum
{
    INIT_RETRIEVE_CROWN_STATE=0, LIST_OF_RETRIEVE_CROWN_STATES(RETRIEVE_CROWN_ENUMFORM)
}SubRetrieveCrown_t;

static SubRetrieveCrown_t currentState;


static int retrieve_forward_L = 500*rate_damper;
static int retrieve_forward_R = 500*rate_damper;

static int retrieve_fork_up_Time = 800;

static int retrieve_reverse_L = -695*rate_damper;
static int retrieve_reverse_R = -700*rate_damper;
static int retrieve_reverse_Time = 400/rate_damper;

static int retrieve_ccw_L = -600*rate_damper;
static int retrieve_ccw_R = 600*rate_damper;
static int retrieve_ccw_Time = 250/rate_damper;

static int retrieve_cw_L = 600*rate_damper;
static int retrieve_cw_R = -600*rate_damper;
static int retrieve_cw_Time = 340/rate_damper;

static int retrieve_idle_Time = 400;

ES_Event RETRIEVE_CROWN_RunSubHSM(ES_Event ThisEvent);

uint8_t RETRIEVE_CROWN_InitSubHSM(void)
{
    ES_Event returnEvent;

    currentState = INIT_RETRIEVE_CROWN_STATE;
    returnEvent = RETRIEVE_CROWN_RunSubHSM(INIT_EVENT);
    dbugprintf("RETRIEVE_CROWN_INITFUNCTION, currentState = %d\n", currentState);

    return returnEvent.EventType == ES_NO_EVENT;
}


ES_Event RETRIEVE_CROWN_RunSubHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE;
    SubRetrieveCrown_t nextState;
    static uint8_t tape = 0;
    static uint8_t lock = 0;
    ES_Event PostEvent;
    static uint8_t sensorType = 0;

    switch(currentState)
    {
       case INIT_RETRIEVE_CROWN_STATE:
            if(ThisEvent.EventType == ES_INIT)
            {
                currentState = RETRIEVE_CROWN_FORWARD;
                ThisEvent.EventType = ES_NO_EVENT;
                dbugprintf("INIT_RETRIEVE_CROWN = %d\n", currentState);
                //makeTransition = TRUE;
            }
            break;

        case RETRIEVE_CROWN_FORWARD:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        Motor_LeftSpeed(retrieve_forward_L);
                        Motor_RightSpeed(retrieve_forward_R);
                        Mech_Grabber(GRAB_DOWN);
                        break;

                    case BUMPED:
                        if (BUMPER(BUMPER_NOTCH))
                        {
                            nextState = RETRIEVE_CROWN_IDLE;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    default:
                        break;
                }
            }
            break;

        case RETRIEVE_CROWN_IDLE:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        Motor_LeftSpeed(0);
                        Motor_RightSpeed(0);
                        ES_Timer_InitTimer(HSM_TIMER, retrieve_idle_Time);
                        break;

                    case ES_TIMEOUT:
                        nextState = RETRIEVE_CROWN_FORK_UP;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case RETRIEVE_CROWN_FORK_UP:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        Mech_Grabber(GRAB_UP);
                        ES_Timer_InitTimer(HSM_TIMER, retrieve_fork_up_Time);
                        break;

                    case ES_TIMEOUT:
                        nextState = RETRIEVE_CROWN_REVERSE;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case RETRIEVE_CROWN_REVERSE:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        Motor_LeftSpeed(retrieve_reverse_L);
                        Motor_RightSpeed(retrieve_reverse_R);
                        ES_Timer_InitTimer(HSM_TIMER, retrieve_reverse_Time);
                        break;

                    case ES_TIMEOUT:
                        nextState = RETRIEVE_CROWN_RETURN;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case RETRIEVE_CROWN_RETURN:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        PostEvent.EventType = RETURN_CENTER;
                        PostEvent.EventParam = currentObstacleType;
                        PostReturnCenterFSM(PostEvent);
                        break;

                    case COMPLETE:
                        nextState = RETRIEVE_CROWN_TURN;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case RETRIEVE_CROWN_TURN:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    switch(location)
                    {
                        case SE:
/*                            Motor_LeftSpeed(retrieve_cw_L);
                            Motor_RightSpeed(retrieve_cw_R);
                            ES_Timer_InitTimer(HSM_TIMER, retrieve_cw_Time);
 */
                            PostRotate(START_ROTATE, MAIN_HSM, retrieve_cw_L, retrieve_cw_R);
                            break;

                        case SW:
//                            ES_Timer_InitTimer(HSM_TIMER, 10);
                            break;

                        case NW:
/*                            Motor_LeftSpeed(retrieve_ccw_L);
                            Motor_RightSpeed(retrieve_ccw_R);
                            ES_Timer_InitTimer(HSM_TIMER, retrieve_ccw_Time);
 */
                            PostRotate(START_ROTATE, MAIN_HSM, retrieve_ccw_L, retrieve_ccw_R);
                            break;

                        default:
                            break;
                    }
                    break;

                case COMPLETE:
                    ThisEvent.EventType = COMPLETE;
                    break;
            }
            break;

        default:
            break;
    }

    if (makeTransition)
    {
        RETRIEVE_CROWN_RunSubHSM(EXIT_EVENT);
        currentState = nextState;
        RETRIEVE_CROWN_RunSubHSM(ENTRY_EVENT);
    }

    return ThisEvent;
}


