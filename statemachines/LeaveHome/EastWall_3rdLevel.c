#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"

#include "LeaveHome_2ndLevel.h"

#define EAST_WALL_ENUMFORM(STATE) EAST_WALL_##STATE,

#define LIST_OF_EAST_WALL_STATES(STATE)\
    STATE(ALIGN)\
    STATE(REVERSE)\
    STATE(CCW180)\
    STATE(FORWARD)\

typedef enum
{
    INIT_EAST_WALL_STATE=0, LIST_OF_EAST_WALL_STATES(EAST_WALL_ENUMFORM)
}SubEastWall_t;

static SubEastWall_t currentState;

ES_Event EAST_WALL_RunSubHSM(ES_Event ThisEvent);

uint8_t EAST_WALL_InitSubHSM(void)
{
    ES_Event returnEvent;

    currentState = INIT_EAST_WALL_STATE;
    returnEvent = EAST_WALL_RunSubHSM(INIT_EVENT);
    dbugprintf("EAST_WALL_INITFUNCTION, currentState = %d\n", currentState);

    return returnEvent.EventType == ES_NO_EVENT;
}


ES_Event EAST_WALL_RunSubHSM(ES_Event ThisEvent)
{
    ES_Event PostEvent;
    uint8_t makeTransition = FALSE;
    SubEastWall_t nextState;
    uint8_t temp1, temp2;
    static uint8_t once = 0;

    switch(currentState)
    {
        case INIT_EAST_WALL_STATE:
            if(ThisEvent.EventType == ES_INIT)
            {
                currentState = EAST_WALL_ALIGN;
                ThisEvent.EventType = ES_NO_EVENT;
                dbugprintf("INIT_EAST_WALL = %d\n", currentState);
                //makeTransition = TRUE;
            }
            break;

        case EAST_WALL_ALIGN:
             switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    PostEvent.EventType = START_ALIGN;
                    PostEvent.EventParam = 0;

                    PostAlignFSM(PostEvent);
                break;

                case COMPLETE:
                    nextState = EAST_WALL_CCW180;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case EAST_WALL_CCW180:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        Motor_RightSpeed(ccw_R);
                        Motor_LeftSpeed(ccw_L);
                        HSM_LEDSubIndicate(0x07);
                        ES_Timer_InitTimer(HSM_TIMER, ccw180_Time);
                        break;

                    case ES_TIMEOUT:
                        nextState = EAST_WALL_FORWARD;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case EAST_WALL_FORWARD:
           if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        Motor_RightSpeed(forward_R);
                        Motor_LeftSpeed(forward_L);
                        HSM_LEDSubIndicate(0x08);
                        break;

                    case BUMPED:
                        ThisEvent.EventType = COMPLETE;
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
        EAST_WALL_RunSubHSM(EXIT_EVENT);
        currentState = nextState;
        EAST_WALL_RunSubHSM(ENTRY_EVENT);
    }

    return ThisEvent;
}


