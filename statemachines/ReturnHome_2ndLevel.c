

#include "ES_Configure.h"
#include "ES_Framework.h"
#include "BOARD.h"

#include "globalmacros.h"
#include "hodor_sensors.h"
#include "hodor_mech.h"

#include "SearchCastle.h"

void reset(void);
extern uint8_t testing;
extern uint8_t currentObstacleType;
extern uint8_t location;
extern uint8_t startingCastle;

#define RETURN_HOME_ENUMFORM(STATE) RETURN_HOME_##STATE,

#define LIST_OF_RETURN_HOME_STATES(STATE)\
    STATE(RETURN_CASTLE)\
    STATE(FORWARD)\
    STATE(ERROR_HANDLING)\
    STATE(THRONE_HANDLING)\
    STATE(FORK_DOWN)\
    STATE(SHAKE)\
    STATE(REVERSE)\
    STATE(TWELVELEVELPARTYHIERARCHICALSTATE)\

typedef enum {
    INIT_RETURN_HOME_STATE = 0, LIST_OF_RETURN_HOME_STATES(RETURN_HOME_ENUMFORM)
} SubReturnHome_t;

static SubReturnHome_t currentState;


static int returnhome_forward_L = 650 * rate_damper;
static int returnhome_forward_R = 650 * rate_damper;

static int returnhome_fork_down_Time = 500;

static int returnhome_reverse_L = -695 * rate_damper;
static int returnhome_reverse_R = -700 * rate_damper;
static int returnhome_reverse_Time = 700 / rate_damper;

static int returnhome_ccw_L = -600 * rate_damper;
static int returnhome_ccw_R = 600 * rate_damper;
static int returnhome_ccw_Time = 250 / rate_damper;

static int returnhome_cw_L = 600 * rate_damper;
static int returnhome_cw_R = -600 * rate_damper;
static int returnhome_cw_Time = 250 / rate_damper;

static int returnhome_handle_L = -100 * rate_damper;
static int returnhome_handle_R = -550 * rate_damper;
static int returnhome_handle_Time = 400 / rate_damper;

static int returnhome_throne_L = -200 * rate_damper;
static int returnhome_throne_R = -500 * rate_damper;
static int returnhome_throne_Time = 470 / rate_damper;

static int shake_L = -400;
static int shake_R = 400;

static int checkstuck_Time = 1600;
static int shake_Time = 400;

ES_Event RETURN_HOME_RunSubHSM(ES_Event ThisEvent);

uint8_t RETURN_HOME_InitSubHSM(void) {
    ES_Event returnEvent;

    currentState = INIT_RETURN_HOME_STATE;
    returnEvent = RETURN_HOME_RunSubHSM(INIT_EVENT);
    dbugprintf("RETURN_HOME_INITFUNCTION, currentState = %d\n", currentState);

    return returnEvent.EventType == ES_NO_EVENT;
}

ES_Event RETURN_HOME_RunSubHSM(ES_Event ThisEvent) {
    uint8_t makeTransition = FALSE;
    SubReturnHome_t nextState;
    ES_Event PostEvent;
    static uint8_t sensorType = 0;
    static shake_Times = 0;

    switch (currentState) {
        case INIT_RETURN_HOME_STATE:
            if (ThisEvent.EventType == ES_INIT) {
                currentState = RETURN_HOME_RETURN_CASTLE;
                ThisEvent.EventType = ES_NO_EVENT;
                dbugprintf("INIT_RETURN_HOME = %d\n", currentState);
                //makeTransition = TRUE;
            }
            break;

        case RETURN_HOME_RETURN_CASTLE:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    PostSearchCastle(RETURN_HOME_CASTLE, startingCastle, MAIN_HSM);
                    break;

                case COMPLETE:
                    nextState = RETURN_HOME_FORWARD;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case RETURN_HOME_FORWARD:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        Motor_LeftSpeed(returnhome_forward_L);
                        Motor_RightSpeed(returnhome_forward_R);
                        break;

                    case BUMPED:
                        if (BUMPER(BUMPER_NOTCH))
                        {
//                            Motor_LeftSpeed(0);
  //                          Motor_RightSpeed(0);

                            Mech_Grabber(GRAB_DOWN);

                            ES_Timer_InitTimer(HSM_TIMER, returnhome_fork_down_Time);

                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        else if (BUMPER(BUMPER_FRONT_LEFT|BUMPER_FRONT_RIGHT))
                        {
                            ES_Timer_InitTimer(HSM_SAMPLE_TIMER, checkstuck_Time);
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                       
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == HSM_TIMER)
                        {
                            nextState = RETURN_HOME_SHAKE;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                        else
                        {
                            if (Sensors_CheckBumperStatus(BUMPER_NOTCH))
                            {
                                Motor_LeftSpeed(0);
                                Motor_RightSpeed(0);
                                Mech_Grabber(GRAB_DOWN);
                                ES_Timer_InitTimer(HSM_TIMER, returnhome_fork_down_Time);
                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                            else if (Sensors_CheckBumperStatus(BUMPER_FRONT_LEFT))
                            {
                                nextState = RETURN_HOME_ERROR_HANDLING;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                            else if (Sensors_CheckBumperStatus(BUMPER_FRONT_RIGHT))
                            {
                                nextState = RETURN_HOME_THRONE_HANDLING;
                                makeTransition = TRUE;
                                ThisEvent.EventType = ES_NO_EVENT;
                            }

                        }
                        break;

                    default:
                        break;
                }
            }
            break;

        case RETURN_HOME_SHAKE:
            switch(ThisEvent.EventType)
            {
                case ES_ENTRY:
                    Mech_Grabber(SHAKE_UP);
                    ES_Timer_InitTimer(HSM_TIMER, shake_Time);
                    break;

                case ES_TIMEOUT:
                    if (ThisEvent.EventParam == HSM_TIMER)
                    {
                        if (shake_Times % 2)
                        {
                            Mech_Grabber(SHAKE_DOWN);
                        }
                        else
                        {
                            Mech_Grabber(SHAKE_UP);
                        }

                        shake_Times++;
                        ES_Timer_InitTimer(HSM_TIMER, shake_Time);

                        if (shake_Times > 1)
                        {
                            nextState = RETURN_HOME_REVERSE;
                            makeTransition = TRUE;
                            ThisEvent.EventType = ES_NO_EVENT;
                        }
                    }
                    break;
            }
            break;

        case RETURN_HOME_ERROR_HANDLING:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    Motor_RightSpeed(returnhome_handle_R);
                    Motor_LeftSpeed(returnhome_handle_L);
                    ES_Timer_InitTimer(HSM_TIMER, returnhome_handle_Time);
                    break;

                case ES_TIMEOUT:
                    nextState = RETURN_HOME_FORWARD;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;

        case RETURN_HOME_THRONE_HANDLING:
            switch (ThisEvent.EventType) {
                case ES_ENTRY:
                    Motor_RightSpeed(returnhome_throne_R);
                    Motor_LeftSpeed(returnhome_throne_L);
                    ES_Timer_InitTimer(HSM_TIMER, returnhome_throne_Time);
                    break;

                case ES_TIMEOUT:
                    nextState = RETURN_HOME_FORWARD;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;
            }
            break;


        case RETURN_HOME_REVERSE:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        Motor_LeftSpeed(returnhome_reverse_L);
                        Motor_RightSpeed(returnhome_reverse_R);
                        ES_Timer_InitTimer(HSM_TIMER, returnhome_reverse_Time);
                        break;

                    case ES_TIMEOUT:
                        if (ThisEvent.EventParam == HSM_TIMER)
                        {
                            //nextState = RETURN_HOME_TWELVELEVELPARTYHIERARCHICALSTATE;
//                            makeTransition = TRUE;
                            ThisEvent.EventType = COMPLETE;
                            testing = !testing;
                            Mech_Grabber(GRAB_UP);
                        }
                        break;

                    default:
                        break;
                }
            }
            break;

        case RETURN_HOME_TWELVELEVELPARTYHIERARCHICALSTATE:
            if (ThisEvent.EventType != ES_NO_EVENT) {
                switch (ThisEvent.EventType) {
                    case ES_ENTRY:
                        Motor_RightSpeed(-500);
                        Motor_LeftSpeed(500);
                        while (1)
                        {
                            for (;;);
                            do
                            {
                                ;;;;       ;;;;  ;;;;;;;;;;;;;;;  ;;;;;;;;;;;      ;;;;;;;;;;;;;;;  ;;;;;;;;;;;;;;;
                                ;;;;       ;;;;  ;;;;;;;;;;;;;;;  ;;;;;;;;;;;;     ;;;;;;;;;;;;;;;  ;;;;;;;;;;;;;;;
                                ;;;;       ;;;;  ;;;;       ;;;;  ;;;;       ;;    ;;;;       ;;;;  ;;;;       ;;;;
                                ;;;;       ;;;;  ;;;;       ;;;;  ;;;;       ;;;   ;;;;       ;;;;  ;;;;       ;;;;
                                ;;;;       ;;;;  ;;;;       ;;;;  ;;;;       ;;;;  ;;;;       ;;;;  ;;;;       ;;;;
                                ;;;;;;;;;;;;;;;  ;;;;       ;;;;  ;;;;       ;;;;  ;;;;       ;;;;  ;;;;;;;;;;;;;;;
                                ;;;;;;;;;;;;;;;  ;;;;       ;;;;  ;;;;       ;;;;  ;;;;       ;;;;  ;;;;;;;;;;;;;;;
                                ;;;;;;;;;;;;;;;  ;;;;       ;;;;  ;;;;       ;;;;  ;;;;       ;;;;  ;;;;  ;;;;
                                ;;;;       ;;;;  ;;;;       ;;;;  ;;;;       ;;;;  ;;;;       ;;;;  ;;;;   ;;;;
                                ;;;;       ;;;;  ;;;;       ;;;;  ;;;;       ;;;   ;;;;       ;;;;  ;;;;    ;;;;
                                ;;;;       ;;;;  ;;;;       ;;;;  ;;;;       ;;    ;;;;       ;;;;  ;;;;     ;;;;
                                ;;;;       ;;;;  ;;;;;;;;;;;;;;;  ;;;;;;;;;;;;     ;;;;;;;;;;;;;;;  ;;;;      ;;;;
                                ;;;;       ;;;;  ;;;;;;;;;;;;;;;  ;;;;;;;;;;;      ;;;;;;;;;;;;;;;  ;;;;       ;;;;
                            }while(1);
                        }

                        break;

                    default:
                        break;
                }
            }
            break;

        default:
            break;
    }

    if (makeTransition) {
        RETURN_HOME_RunSubHSM(EXIT_EVENT);
        currentState = nextState;
        RETURN_HOME_RunSubHSM(ENTRY_EVENT);
    }

    return ThisEvent;
}


void reset(void)
{
    reset();
}