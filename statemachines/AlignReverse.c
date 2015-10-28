#include "AlignReverse.h"

#include "hodor_motors.h"
#include "hodor_sensors.h"

#define ALIGN_REVERSE_ENUMFORM(STATE) STATE,

#define LIST_OF_ALIGN_REVERSE_STATES(STATE)\
STATE(ALIGN)\
STATE(REVERSE)\
STATE(IDLE)\

typedef enum
{
    INIT_ALIGN_REVERSE_STATE=0, LIST_OF_ALIGN_REVERSE_STATES(ALIGN_REVERSE_ENUMFORM)
}AlignReverse_t;

static AlignReverse_t currentState;

static int align = 700*rate_damper;
static int align_sample_Time = 50;
static int align_limit_Time = 800;
static int align_short_limit_Time = 600;
static int align_long_limit_Time = 4000;

static int reverse_L = -600*rate_damper;
static int reverse_R = -600*rate_damper;
static int reverse_Time = 150/rate_damper;

extern int cw90_L;
extern int cw90_R;
extern int cw90_Time;

extern uint8_t trackwire;
extern uint8_t lefthome;

static TopState_t CurrentState = INIT_TOPSTATE;
static uint8_t MyPriority;

uint8_t PostAlignFSM(ES_Event ThisEvent)
{
	return ES_PostToService(MyPriority, ThisEvent);
}


uint8_t ALIGN_REVERSE_InitFSM(uint8_t Priority)
{
    MyPriority = Priority;
    currentState = INIT_ALIGN_REVERSE_STATE;
    dbugprintf("ALIGN_REVERSE_INITFUNCTION, currentState = %d\n", currentState);

    return ES_PostToService(MyPriority, INIT_EVENT);
}


ES_Event ALIGN_REVERSE_RunFSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE;
    AlignReverse_t nextState;
    uint8_t temp1, temp2;
    static uint8_t sensor = 0;
    static uint8_t source = 0;
    static uint8_t once = 0;

    switch(currentState)
    {
        case INIT_ALIGN_REVERSE_STATE:
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
                    LED_OnBank(LED_BANK1, 0x01);
                    source = 0;
                   break;

                case START_ALIGN:
                    sensor = ThisEvent.EventParam & 0x01;
                    source = (ThisEvent.EventParam & 0x06) >> 1;

                    nextState = ALIGN;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case ALIGN:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        LED_OnBank(LED_BANK1, 0x01);

                        dbugprintf("ALIGN = %d\n", ThisEvent.EventParam);
                        ES_Timer_InitTimer(ALIGN_SAMPLE_TIMER, align_sample_Time);
                        if (once < 6)
                        {
                            if (sensor == 0)
                            {
                                ES_Timer_InitTimer(ALIGN_LIMIT_TIMER, align_limit_Time);
                            }
                            else
                            {
                                ES_Timer_InitTimer(ALIGN_LIMIT_TIMER, align_short_limit_Time);
                            }
                            once++;
                        }
                        else
                        {
                            if (sensor == 0)
                            {
                                ES_Timer_InitTimer(ALIGN_LIMIT_TIMER, align_short_limit_Time);
                            }
                            else
                            {
                                ES_Timer_InitTimer(ALIGN_LIMIT_TIMER, align_long_limit_Time);
                            }
                        }

                        break;

                    case TRACKWIRE:
                        trackwire = 1;
                        break;

                    case ES_TIMEOUT:
                        ThisEvent.EventType = ES_NO_EVENT;
                        switch(ThisEvent.EventParam)
                        {
                            case ALIGN_SAMPLE_TIMER:
                                if (sensor == 0)
                                {
                                    temp1 = Sensors_CheckBumperStatus(BUMPER_FRONT_RIGHT|BUMPER_RIGHT) != 0;
                                    temp2 = Sensors_CheckBumperStatus(BUMPER_FRONT_LEFT|BUMPER_LEFT) != 0;
                                }
                                else
                                {
                                    temp1 = (Sensors_CheckTapeStatus(TAPE_RIGHT2) == 0);
                                    temp2 = (Sensors_CheckTapeStatus(TAPE_LEFT2) == 0);
                                }

                                /*if (!temp1 && temp2)
                                {
                                    Motor_RightSpeed(align);
                                    Motor_LeftSpeed(-align);
                                }
                                else if (!temp1 && !temp2)
                                {
                                    Motor_RightSpeed(align);
                                    Motor_LeftSpeed(align);
                                }
                                else if (temp1 && !temp2)
                                {
                                    Motor_RightSpeed(-align);
                                    Motor_LeftSpeed(align);
                                }
                                else */
                                //if (sensor == 0)
                                if (1)
                                {
                                    if (!temp1)
                                        Motor_RightSpeed(align);
                                    else
                                        Motor_RightSpeed(-align);

                                    if (!temp2)
                                        Motor_LeftSpeed(align);
                                    else
                                        Motor_LeftSpeed(-align);
                                }

                                if (temp1 && temp2)
                                 {
                                     nextState = REVERSE;
                                     makeTransition = TRUE;
                                     ES_Timer_StopTimer(ALIGN_LIMIT_TIMER);
                                     ES_Timer_StopTimer(ALIGN_SAMPLE_TIMER);
                                 }
                                 else
                                 {
                                     ES_Timer_InitTimer(ALIGN_SAMPLE_TIMER, align_sample_Time);
                                 }
                                break;

                            case ALIGN_LIMIT_TIMER:
                                ES_Timer_StopTimer(ALIGN_SAMPLE_TIMER);

                                nextState = REVERSE;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                                break;
                        }
                        break;

                        default:
                            break;
                     }
                }
                break;

        case REVERSE:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Motor_LeftSpeed(reverse_L);
                    Motor_RightSpeed(reverse_R);
                    if (lefthome)
                    {
                        reverse_L = -400*rate_damper;
                        reverse_R = -400*rate_damper;
                    }
                    if (sensor == 1)
                    {
                        ES_Timer_InitTimer(REVERSE_TIMER, 2*reverse_Time);
                    }
                    else
                    {
                        ES_Timer_InitTimer(REVERSE_TIMER, reverse_Time);
                    }
                    break;

                case ES_TIMEOUT:
                    ThisEvent.EventType = COMPLETE;

                    dbugprintf("source = %d\n", source);

                    if (source == MAIN_HSM)
                    {
                        PostToplevelHSM(ThisEvent);
                    }
                    else if (source == RETURN_CENTER_FSM)
                    {
                        PostReturnCenterFSM(ThisEvent);
                    }
                    else if (source == SEARCH_CASTLE_FSM)
                    {
                        PostSearchCastleFSM(ThisEvent);
                    }

                    dbugprintf("ALIGN FINISHED\n");
                    nextState = IDLE;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
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
        ALIGN_REVERSE_RunFSM(EXIT_EVENT);
        currentState = nextState;
        ALIGN_REVERSE_RunFSM(ENTRY_EVENT);
    }
}

void PostAlign(ES_EventTyp_t EventType, uint8_t sensor, uint8_t src)
{
    ES_Event PostEvent;

    PostEvent.EventType = EventType;
    PostEvent.EventParam = sensor|(src << 1);
    PostAlignFSM(PostEvent);
}
