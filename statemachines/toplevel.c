#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"

#include "toplevel.h"

//ES_Event LEAVE_HOME_RunSubHSM(ES_Event);

static const char *StateNames[] = {
	"INIT_TOPSTATE", LIST_OF_TOP_STATES(STRING_FORM)
};

static TopState_t CurrentState = INIT_TOPSTATE;
static uint8_t MyPriority;

uint8_t testing = 0;

uint8_t startingCastle = 0;
uint8_t currentObstacleType = 0;
uint8_t location = 0;
extern uint8_t trackwire;
uint8_t InitToplevelHSM(uint8_t Priority)
{
	MyPriority = Priority;

	CurrentState = INIT_TOPSTATE;

	return ES_PostToService(MyPriority, INIT_EVENT);
}

uint8_t PostToplevelHSM(ES_Event ThisEvent)
{
	return ES_PostToService(MyPriority, ThisEvent);
}


TopState_t QueryToplevelHSM(void)
{
	return (CurrentState);	
}

ES_Event RunToplevelHSM(ES_Event ThisEvent)
{
	uint8_t makeTransition = FALSE;
	TopState_t nextState;
        static uint8_t sensor = 0;

	//ES_Tattle();
	
	switch(CurrentState)
	{
#ifdef _HODOR_NORMAL
            case INIT_TOPSTATE:
                if (ThisEvent.EventType == ES_INIT)
                {
                    LIST_OF_TOP_STATES(INITFUNC_FORM);
                    ES_Timer_Init();
                    LED_AddBanks(LED_BANK1|LED_BANK2|LED_BANK3);
                    LED_OffBank(LED_BANK1, 0x0F);
                    LED_OffBank(LED_BANK2, 0x0F);
                    LED_OffBank(LED_BANK3, 0x0F);

                    beaconlock = 0;

                    nextState = LEAVE_HOME;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
                        
            case LEAVE_HOME:
                ThisEvent = LEAVE_HOME_RunSubHSM(ThisEvent);
                
                if (ThisEvent.EventType == COMPLETE)
                {
                    nextState = FIND_RULING;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;

            case FIND_RULING:
                ThisEvent = FIND_RULING_RunSubHSM(ThisEvent);

                if (ThisEvent.EventType == COMPLETE)
                {
                    nextState = RETRIEVE_CROWN;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;

            case RETRIEVE_CROWN:
                ThisEvent = RETRIEVE_CROWN_RunSubHSM(ThisEvent);

                if (ThisEvent.EventType == COMPLETE)
                {
                    nextState = RETURN_HOME;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;

            case RETURN_HOME:
                ThisEvent = RETURN_HOME_RunSubHSM(ThisEvent);

                if (ThisEvent.EventType == COMPLETE)
                {
                    trackwire = 0;
                    nextState = LEAVE_HOME;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;

            case ROTATE_TEST:
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        PostRotate(START_ROTATE, MAIN_HSM, 500*rate_damper, -300*rate_damper);
                        break;

                    case COMPLETE:
                        Motor_LeftSpeed(0);
                        Motor_RightSpeed(0);
                        while(1);
                        break;
                }
                break;


#endif
#ifdef _HODOR_TEST
            case INIT_TOPSTATE:
            if (ThisEvent.EventType == ES_INIT)
            {
                ES_Timer_Init();
                CurrentState = TIMER_TEST;
               ES_Timer_InitTimer(HSM_TIMER, 1000);
            }
            break;

            case TIMER_TEST:
                if (ThisEvent.EventType == ES_TIMEOUT)
                {
                    ES_Timer_InitTimer(HSM_TIMER, 1000);

                    printf("Timer Test, Period = 1000ms\n");
                    ThisEvent.EventType = ES_NO_EVENT;
                }
                break;
#endif

            default:
                break;
	}

        if (makeTransition)
        {
            RunToplevelHSM(EXIT_EVENT);
            CurrentState = nextState;
            RunToplevelHSM(ENTRY_EVENT);
        }

}

void HSM_LEDSubIndicate(uint8_t label)
{
    LED_SetBank(LED_BANK3, label & 0x0F);
    LED_SetBank(LED_BANK2, (label & 0x10) >> 4);
}
