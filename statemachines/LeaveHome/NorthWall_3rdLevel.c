#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"

#include "LeaveHome_2ndLevel.h"
#include "globalmacros.h"

#define NORTH_WALL_ENUMFORM(STATE) NORTH_WALL_##STATE,

#define LIST_OF_NORTH_WALL_STATES(STATE)\
    STATE(ALIGN)\
    STATE(REVERSE)\
    STATE(CCW90)\
STATE(FORWARD)\

typedef enum
{
    INIT_NORTH_WALL_STATE=0, LIST_OF_NORTH_WALL_STATES(NORTH_WALL_ENUMFORM)
}SubNorthWall_t;

static SubNorthWall_t currentState;

ES_Event NORTH_WALL_RunSubHSM(ES_Event ThisEvent);

uint8_t NORTH_WALL_InitSubHSM(void)
{
    ES_Event returnEvent;
    ES_Event PostEvent;
    currentState = INIT_NORTH_WALL_STATE;
    returnEvent = NORTH_WALL_RunSubHSM(INIT_EVENT);
    dbugprintf("NORTH_WALL_INITFUNCTION, currentState = %d\n", currentState);

    return returnEvent.EventType == ES_NO_EVENT;
}


ES_Event NORTH_WALL_RunSubHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE;
    SubNorthWall_t nextState;
    uint8_t temp1, temp2;
    static uint8_t once = 0;
    ES_Event PostEvent;
    
    switch(currentState)
    {
        case INIT_NORTH_WALL_STATE:
            if(ThisEvent.EventType == ES_INIT)
            {
                currentState = NORTH_WALL_ALIGN;
                ThisEvent.EventType = ES_NO_EVENT;
                dbugprintf("INIT_NORTH_WALL = %d\n", currentState);
                //makeTransition = TRUE;
            }
            break;

        case NORTH_WALL_ALIGN:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        PostEvent.EventType = START_ALIGN;
                        PostEvent.EventParam = 0;
                        PostAlignFSM(PostEvent);

                        dbugprintf("NORTH_WALL_ALIGN\n");
                    break;

                    case COMPLETE:
                        nextState = NORTH_WALL_CCW90;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case NORTH_WALL_CCW90:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        dbugprintf("NORTH_WALL_CCW180\n");
                        Motor_RightSpeed(ccw_R);
                        Motor_LeftSpeed(ccw_L);
                        HSM_LEDSubIndicate(0x0B);
                        ES_Timer_InitTimer(HSM_TIMER, ccw90_Time);
                        break;

                    case ES_TIMEOUT:
                        nextState = NORTH_WALL_FORWARD;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    default:
                        break;
                }
            }
            break;

        case NORTH_WALL_FORWARD:
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
        NORTH_WALL_RunSubHSM(EXIT_EVENT);
        currentState = nextState;
        NORTH_WALL_RunSubHSM(ENTRY_EVENT);
    }

    return ThisEvent;
}

