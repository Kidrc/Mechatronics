#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"

#include "LeaveHome_2ndLevel.h"

typedef enum
{
    INIT_LEAVE_HOME_STATE=0, LIST_OF_LEAVE_HOME_STATES(LEAVE_HOME_ENUMFORM)
}SubLeaveHome_t;

static SubLeaveHome_t currentState;
uint8_t lefthome = 0;

uint8_t beacon = 0;

int ccw_L= -600*rate_damper;
int ccw_R = 600*rate_damper;
static int ccw45_L = -700*rate_damper;
static int ccw45_R = -200*rate_damper;

static int ccw45_Time = 250/rate_damper;
int ccw90_Time = 240/rate_damper;
int ccw180_Time = 450/rate_damper;

int wall_ccw_L= -300*rate_damper;
int wall_ccw_R = 600*rate_damper;
int wall_ccw90_Time = 400/rate_damper;
int wall_ccw180_Time = 510/rate_damper;

int forward_L = 600*rate_damper;
int forward_R = 600*rate_damper;

int reverse_L = -650*rate_damper;
int reverse_R = -650*rate_damper;
int reverse_Time = 400/rate_damper;

int trackwire_Time = 100;
int trackwire_limit_Time = 100;

static int forward_limit_Time = 1000;
uint8_t trackwire = 0;
static int tape = 0;

ES_Event LEAVE_HOME_RunSubHSM(ES_Event ThisEvent);

uint8_t LEAVE_HOME_InitSubHSM(void)
{
    ES_Event returnEvent;

    currentState = INIT_LEAVE_HOME_STATE;
    returnEvent = LEAVE_HOME_RunSubHSM(INIT_EVENT);
    dbugprintf("LEAVE_HOME_INITFUNCTION, currentState = %d\n", currentState);

    return returnEvent.EventType == ES_NO_EVENT;
}


ES_Event LEAVE_HOME_RunSubHSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE;
    SubLeaveHome_t nextState;
    static uint8_t lock = 0;
    static uint8_t timer_Lock = 0;
    static uint8_t ready = 0;
    static uint8_t tw_count = 0;
    static uint8_t tw_detected = 0;

    switch(currentState)
    {
        case INIT_LEAVE_HOME_STATE:
            if(ThisEvent.EventType == ES_INIT)
            {
                START_POINT_InitSubHSM();

                currentState = LEAVE_HOME_FORWARD;
                ThisEvent.EventType = ES_NO_EVENT;
                dbugprintf("INIT_LEAVE_HOME = %d\n", currentState);
                //makeTransition = TRUE;
            }
            break;

        case LEAVE_HOME_FORWARD:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        Motor_LeftSpeed(forward_L);
                        Motor_RightSpeed(forward_R);

                        dbugprintf("LEAVE_HOME_FORWARD = %d\n", currentState);
                        
                        if (!timer_Lock)
                        {
                            ES_Timer_InitTimer(HSM_TIMER, forward_limit_Time);
                        }
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == HSM_TIMER)
                        {
                            timer_Lock = 1;

                            if (!trackwire)
                            {
                                nextState = LEAVE_HOME_CCW180_REVERSE;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                        }
                        else if (ThisEvent.EventParam == HSM_SAMPLE_TIMER)
                        {
                            nextState = LEAVE_HOME_FORWARD;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case TRACKWIRE:
                        printf("TRACKWIRE\n");
                        trackwire = 1;
                        break;

                    case TAPE:
                        tape = 1;
                        dbugprintf("TAPE\n");
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;

                    case BUMPED:
//                        if (ready >= 1 && BUMPER(BUMPER_LEFT))
                        timer_Lock = 1;
                            if (0)
                        {
                            dbugprintf("BUMPED_REVERSE\n");
                            ready = 0;
                            Motor_LeftSpeed(0);
                            Motor_RightSpeed(reverse_R);

                            ES_Timer_InitTimer(HSM_SAMPLE_TIMER, reverse_Time);
                        }
                        else
                        {
                            ES_Timer_StopTimer(HSM_TIMER);
                            PostAlign(START_ALIGN, 0, MAIN_HSM);
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        break;

                    case COMPLETE:
                        if (trackwire)
                        {
                            nextState = LEAVE_HOME_READY_CCW90;
                        }
                        else
                        {
                            if (tape)
                            {
                                nextState = LEAVE_HOME_CCW45;
                            }
                            else
                            {
                                nextState = LEAVE_HOME_CCW90;
                            }
                        }
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                        break;
                }
            }
            break;

        case LEAVE_HOME_CCW45:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Motor_LeftSpeed(ccw45_L);
                    Motor_RightSpeed(ccw45_R);
                    ES_Timer_InitTimer(HSM_TIMER, ccw45_Time);
                    break;
                    
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == HSM_TIMER)
                    {
                        nextState = LEAVE_HOME_FORWARD;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                default:
                    break;
            }
            break;

        case LEAVE_HOME_CCW90:
            switch(ThisEvent.EventType)
            {
                /*case ES_ENTRY:
                    Motor_LeftSpeed(-ccw_L);
                    Motor_RightSpeed(-ccw_R);
                    ES_Timer_InitTimer(HSM_TIMER, ccw90_Time);
                    break;
                    
                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == HSM_TIMER)
                    {
                        nextState = LEAVE_HOME_FORWARD;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
                    */
                case ES_ENTRY:
                    PostRotate(START_ROTATE, MAIN_HSM, -ccw_L, -ccw_R);
                    break;

                case COMPLETE:
                    nextState = LEAVE_HOME_FORWARD;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                    
                default:
                    break;
            }
            break;

        case LEAVE_HOME_CCW180_REVERSE:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Motor_LeftSpeed(reverse_L);
                    Motor_RightSpeed(reverse_R);
                    ES_Timer_InitTimer(HSM_TIMER, forward_limit_Time);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == HSM_TIMER)
                    {
                        nextState = LEAVE_HOME_CCW180;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                default:
                    break;
            }
            break;

        case LEAVE_HOME_CCW180:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Motor_LeftSpeed(ccw_L);
                    Motor_RightSpeed(ccw_R);
                    ES_Timer_InitTimer(HSM_TIMER, ccw180_Time);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == HSM_TIMER)
                    {
                        nextState = LEAVE_HOME_FORWARD;
                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;

                default:
                    break;
            }
            break;

        case LEAVE_HOME_READY_CCW90:
            switch(ThisEvent.EventType)
            {
/*                case ES_ENTRY:
                    dbugprintf("LEAVE_HOME_READY_CCW90\n");
                    Motor_LeftSpeed(ccw_L);
                    Motor_RightSpeed(ccw_R);
                    ES_Timer_InitTimer(HSM_TIMER, ccw90_Time);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == HSM_TIMER)
                    {
                            ++ready;

                        if (ready >= 2)
                        {
                            if (Sensors_CheckBumperStatus(BUMPER_LEFT))
                            {
                                nextState = LEAVE_HOME_READY_CCW90;
                            }
                            else
                            {
                                nextState = LEAVE_HOME_START_POINT;
                            }
                        }
                        else

                        {
                            nextState = LEAVE_HOME_FORWARD;
                        }

                        makeTransition = TRUE;
                        ThisEvent.EventType = ES_NO_EVENT;
                    }
                    break;
*/
                case ES_ENTRY:
                    printf("READY_CCW90");
                    PostRotate(START_ROTATE, MAIN_HSM, ccw_L, ccw_R);
                    break;

                case COMPLETE:
                    printf("COMPLETE");
                    ++ready;

                    if (ready >= 2)
                    {
                        nextState = LEAVE_HOME_START_POINT;
                        lefthome = 1;
                    }
                    else
                    {
                        nextState = LEAVE_HOME_FORWARD;
                    }
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
                    
            }
            break;

        case LEAVE_HOME_START_POINT:
            ThisEvent = START_POINT_RunSubHSM(ThisEvent);

            if (ThisEvent.EventType == FOUND_BEACON)
            {
                beacon = 1;
                ThisEvent.EventType = ES_NO_EVENT;
            }
            else if (ThisEvent.EventType == ES_ENTRY)
            {
                beaconlock = 1;
            }
            break;

        default:
            break;
    }

    if (makeTransition)
    {
        LEAVE_HOME_RunSubHSM(EXIT_EVENT);
        currentState = nextState;
        LEAVE_HOME_RunSubHSM(ENTRY_EVENT);
    }

    return ThisEvent;
}

