
//#define CHEAT_SEARCH_NW
#define CHEAT_SEARCH_SE

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"

#include "FindRuling_2ndLevel.h"
#include "globalmacros.h"

extern uint8_t beacon;

typedef enum
{
    INIT_FIND_RULING_STATE=0, FIND_RULING_CHOOSE, LIST_OF_FIND_RULING_STATES(FIND_RULING_ENUMFORM)
}SubFindRuling_t;

static SubFindRuling_t currentState;


int center_Time = 1620*0.6/rate_damper;

int findruling_ccw_R = 600*rate_damper;
int findruling_ccw_L = -600*rate_damper;
int findruling_ccw90_Time = 330/rate_damper;

extern uint8_t testing;

ES_Event FIND_RULING_RunSubHSM(ES_Event ThisEvent);

uint8_t FIND_RULING_InitSubHSM(void)
{
    ES_Event returnEvent;

    currentState = INIT_FIND_RULING_STATE;
    returnEvent = FIND_RULING_RunSubHSM(INIT_EVENT);
    dbugprintf("FIND_RULING_INITFUNCTION, currentState = %d\n", currentState);

    return returnEvent.EventType == ES_NO_EVENT;
}


ES_Event FIND_RULING_RunSubHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE;
    SubFindRuling_t nextState;
    static uint8_t tape = 0;
    static uint8_t lock = 0;
 
    switch(currentState)
    {
       case INIT_FIND_RULING_STATE:
            if(ThisEvent.EventType == ES_INIT)
            {
                SEARCH_CASTLE_SE_InitSubHSM();
                SEARCH_CASTLE_SW_InitSubHSM();
                SEARCH_CASTLE_NW_InitSubHSM();
                
                currentState = FIND_RULING_CHOOSE;
                ThisEvent.EventType = ES_NO_EVENT;
                dbugprintf("INIT_FIND_RULING = %d\n", currentState);
                //makeTransition = TRUE;
            }
            break;

        case FIND_RULING_CHOOSE:
            if (ThisEvent.EventType == ES_ENTRY)
            {
#ifdef CHEAT_SEARCH_SE
                if (beacon || testing)
                {
                    nextState = FIND_RULING_SEARCH_CASTLE_NW;
                }
                else
                {
                    nextState = FIND_RULING_SEARCH_CASTLE_SE;
                }
#endif
#ifdef CHEAT_SEARCH_NW
                if (beacon || testing)
                {
                    nextState = FIND_RULING_SEARCH_CASTLE_SE;
                }
                else
                {
                    nextState = FIND_RULING_SEARCH_CASTLE_NW;
                }
#endif
                
                makeTransition = TRUE;

            }
            break;

        case FIND_RULING_SEARCH_CASTLE_SE:
            ThisEvent = SEARCH_CASTLE_SE_RunSubHSM(ThisEvent);

            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case FOUND_RULING:
                      ThisEvent.EventType = COMPLETE;
                        //dbugstop();
                        break;

                    case NOT_FOUND_RULING:
                        nextState = FIND_RULING_SEARCH_CASTLE_SW;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;

                    default:
                        break;
                }
            }
            break;

        case FIND_RULING_SEARCH_CASTLE_SW:
            ThisEvent = SEARCH_CASTLE_SW_RunSubHSM(ThisEvent);

            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case FOUND_RULING:
                      ThisEvent.EventType = COMPLETE;
                        //dbugstop();
                        break;

                    case NOT_FOUND_RULING:
                        nextState = FIND_RULING_SEARCH_CASTLE_SW;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;

                    default:
                        break;
                }
            }
            break;


        case FIND_RULING_SEARCH_CASTLE_NW:
            ThisEvent = SEARCH_CASTLE_NW_RunSubHSM(ThisEvent);

            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case FOUND_RULING:
                      ThisEvent.EventType = COMPLETE;
                        //dbugstop();
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
        FIND_RULING_RunSubHSM(EXIT_EVENT);
        currentState = nextState;
        FIND_RULING_RunSubHSM(ENTRY_EVENT);
    }

    return ThisEvent;
}


