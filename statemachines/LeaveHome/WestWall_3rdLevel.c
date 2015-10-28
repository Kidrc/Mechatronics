#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"

#include "LeaveHome_2ndLevel.h"

#define WEST_WALL_ENUMFORM(STATE) WEST_WALL_##STATE,

#define LIST_OF_WEST_WALL_STATES(STATE)\
    STATE(ALIGN)\
    STATE(REVERSE)\
    STATE(CCW90)\

typedef enum
{
    INIT_WEST_WALL_STATE=0, ALIGN_REVERSE, LIST_OF_WEST_WALL_STATES(WEST_WALL_ENUMFORM)
}SubWestWall_t;

static SubWestWall_t currentState;

ES_Event WEST_WALL_RunSubHSM(ES_Event ThisEvent);

uint8_t WEST_WALL_InitSubHSM(void)
{
    ES_Event returnEvent;

    currentState = INIT_WEST_WALL_STATE;
    returnEvent = WEST_WALL_RunSubHSM(INIT_EVENT);
    dbugprintf("WEST_WALL_INITFUNCTION, currentState = %d\n", currentState);

    return returnEvent.EventType == ES_NO_EVENT;
}


ES_Event WEST_WALL_RunSubHSM(ES_Event ThisEvent)
{
    ES_Event PostEvent;
    uint8_t makeTransition = FALSE;
    SubWestWall_t nextState;
    uint16_t temp1 = 0, temp2 = 0;
    static uint8_t once = 0;

    switch(currentState)
    {
        case INIT_WEST_WALL_STATE:
            if(ThisEvent.EventType == ES_INIT)
            {
                currentState = WEST_WALL_ALIGN;
                ThisEvent.EventType = ES_NO_EVENT;
                dbugprintf("INIT_WEST_WALL = %d\n", currentState);
                //makeTransition = TRUE;
            }
            break;

        case WEST_WALL_ALIGN:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    PostEvent.EventType = START_ALIGN;
                    PostEvent.EventParam = 0;

                    PostAlignFSM(PostEvent);
                break;

                case COMPLETE:
                    nextState = WEST_WALL_CCW90;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case WEST_WALL_CCW90:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        Motor_RightSpeed(wall_ccw_R);
                        Motor_LeftSpeed(wall_ccw_L);
                        HSM_LEDSubIndicate(0x04);
                        ES_Timer_InitTimer(HSM_TIMER, wall_ccw90_Time);
                        break;

                    case ES_TIMEOUT:
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
        WEST_WALL_RunSubHSM(EXIT_EVENT);
        currentState = nextState;
        WEST_WALL_RunSubHSM(ENTRY_EVENT);
    }

    return ThisEvent;
}

