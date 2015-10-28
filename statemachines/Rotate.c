#include "Rotate.h"

#include "hodor_motors.h"
#include "hodor_sensors.h"

#define ROTATE_ENUMFORM(STATE) STATE,

#define LIST_OF_ROTATE_STATES(STATE)\
STATE(ROTATE)\
STATE(IDLE)\

typedef enum
{
    INIT_ROTATE_STATE=0, LIST_OF_ROTATE_STATES(ROTATE_ENUMFORM)
}Rotate_t;

static Rotate_t currentState;

static int rotate = 700*rate_damper;
static int rotate_sample_Time = 60;

extern uint8_t startingCastle;
extern uint8_t returnTurn;
extern uint8_t crownTurn;
extern uint8_t startpointTurn;
static uint8_t MyPriority;
extern uint8_t lefthome;

uint8_t PostRotateFSM(ES_Event ThisEvent)
{
	return ES_PostToService(MyPriority, ThisEvent);
}


uint8_t ROTATE_InitFSM(uint8_t Priority)
{
    MyPriority = Priority;
    currentState = INIT_ROTATE_STATE;
    dbugprintf("ROTATE_INITFUNCTION, currentState = %d\n", currentState);

    return ES_PostToService(MyPriority, INIT_EVENT);
}


ES_Event ROTATE_RunFSM(ES_Event ThisEvent)
{
    uint8_t makeTransition = FALSE;
    Rotate_t nextState;
    static uint8_t dir = 0;
    static uint8_t source = 0;
    static uint8_t once = 0;
    static int16_t left = 0;
    static int16_t right = 0;
    static double currentAngle = 0;
    static double lastGyroZ = 0;
    static int angular = 0;
    static int velocity = 0;
    static double kp = 7;
    static double ki = 1;
    static int intangle = 0;
    static int startTime = 0;
    static uint8_t condition = 0;
    static int cw_target = CW_TARGET;
    static int ccw_target = CCW_TARGET;

    ES_Event PostEvent;

    switch(currentState)
    {
        case INIT_ROTATE_STATE:
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
                    source = 0;
                    intangle = 0;
                    startTime = 0;
                    currentAngle = 0;
                    kp = 7;
                    ki = 1;
                    condition = 0;
                    cw_target = CW_TARGET;
                    ccw_target = CCW_TARGET;
                   break;

                case START_ROTATE:
                    source = ThisEvent.EventParam & 0x03;
                    left = (uint16_t)(ThisEvent.EventParam & 0xFE00) >> 9;
                    right = (uint16_t)(ThisEvent.EventParam & 0x01FC) >> 2;

                    if (left & 0x40)
                    {
                        left = -(left & 0x003F)*10;
                    }
                    else
                    {
                        left = (left & 0x003F)*10;
                    }

                    if (right & 0x40)
                    {
                        right = -(right & 0x003F)*10;
                    }
                    else
                    {
                        right = (right & 0x003F)*10;
                    }

                    if (left < right)
                    {
                        dir = CCW;
                        angular = (right-left)/2;
                        velocity = (right+left)/2;
                    }
                    else
                    {
                        dir = CW;
                        angular = (left-right)/2;
                        velocity = (left+right)/2;
                    }
                    printf("left = %d, right = %d\n", left, right);
                    nextState = ROTATE;
                    makeTransition = TRUE;
                    ThisEvent.EventType = ES_NO_EVENT;
                    break;

                default:
                    break;
            }
            break;

        case ROTATE:
            if (ThisEvent.EventType != ES_NO_EVENT)
            {
                switch(ThisEvent.EventType)
                {
                    case ES_ENTRY:
                        ES_Timer_InitTimer(ROTATE_TIMER, rotate_sample_Time);
                        Motor_LeftSpeed(left);
                        Motor_RightSpeed(right);
                        lastGyroZ = Gyro_ReadZ();
                        dbugprintf("ROTATE\n");
                        break;

                    case ES_TIMEOUT:
                        currentAngle += lastGyroZ/32.8/1000*rotate_sample_Time;
                        //dbugprintf("currentAngle = %d, lastGyroZ = %d\n", currentAngle, lastGyroZ);
                        if (dir == CW)
                        {
                            if (crownTurn)
                            {
                                cw_target = CW_TARGET-25;
                            }
                            else if (startTime == 0 && lefthome)
                            {
                                velocity = 150;
                                cw_target = CW_TARGET;
                            }
                            if (startTime == 0 && currentAngle < -cw_target)
                            {
                                startTime = ES_Timer_GetTime();
                            }
                            if (startTime != 0 && ES_Timer_GetTime() - startTime > ROTATE_LIMIT_TIME)
                            {
                                if ((!crownTurn&&(currentAngle < -cw_target-TOLERANCE || currentAngle > -cw_target+TOLERANCE)))
                                {
                                    kp = 12;
                                    ki = 1;
                                    startTime = ES_Timer_GetTime();
                                    ES_Timer_InitTimer(ROTATE_TIMER, rotate_sample_Time);
                                }
                                else
                                {
                                    PostEvent.EventType = COMPLETE;

                                    switch(source)
                                    {
                                        if (crownTurn)
                                        {
                                            crownTurn = 0;
                                        }
                                        case MAIN_HSM:
                                            PostToplevelHSM(PostEvent);
                                            break;

                                        case RETURN_CENTER_FSM:
                                            PostReturnCenterFSM(PostEvent);
                                            break;

                                        case SEARCH_CASTLE_FSM:
                                            PostSearchCastleFSM(PostEvent);
                                            break;
                                    }

                                    nextState = IDLE;
                                    makeTransition = TRUE;
                                    ThisEvent.EventType = ES_NO_EVENT;
                                }
                            }
                            else
                            {
                                intangle += rotate_sample_Time*(currentAngle+cw_target)/1000;
                                angular = kp*(currentAngle+cw_target)+ki*intangle;
                                if (angular < 200 || angular > -200)
                                {
                                    kp = 12;
                                    ki = 1;
                                }
                                else if (angular > 500)
                                {
                                    angular = 500;
                                }
                                Motor_LeftSpeed(velocity+angular);
                                Motor_RightSpeed(velocity-angular);
                                lastGyroZ = Gyro_ReadZ();
                                ES_Timer_InitTimer(ROTATE_TIMER, rotate_sample_Time);
                            }
                        }
                        else if (dir == CCW)
                        {
                            if (startpointTurn && startingCastle)
                            {
                                ccw_target = CCW_TARGET+20;
                            }
                            else
                            {
                                ccw_target = CCW_TARGET;
                            }
                            if (!returnTurn && !startpointTurn && startTime == 0 && velocity < 200 && lefthome)
                            {
                                velocity = 150;
                                //kp = 6;
                                //ki = 0.5;
                            }
                            ccw_target = CCW_TARGET;

                            if (startTime == 0 && currentAngle > ccw_target)
                            {
                                dbugprintf("angle\n");
                                startTime = ES_Timer_GetTime();
                            }
                            if (startTime != 0 && ES_Timer_GetTime() - startTime > ROTATE_LIMIT_TIME)
                            {
                                if ((crownTurn&&(currentAngle < cw_target-TOLERANCE || currentAngle > cw_target+TOLERANCE)))
                                {
                                    kp = 12;
                                    ki = 1;
                                    startTime = ES_Timer_GetTime();
                                    ES_Timer_InitTimer(ROTATE_TIMER, rotate_sample_Time);
                                }
                                else
                                {
                                    dbugprintf("complete\n");
                                    PostEvent.EventType = COMPLETE;

                                    switch(source)
                                    {
                                        case MAIN_HSM:
                                            PostToplevelHSM(PostEvent);
                                            break;

                                        case RETURN_CENTER_FSM:
                                            PostReturnCenterFSM(PostEvent);
                                            break;

                                        case SEARCH_CASTLE_FSM:
                                            PostSearchCastleFSM(PostEvent);
                                            break;
                                    }

                                    nextState = IDLE;
                                    makeTransition = TRUE;
                                    ThisEvent.EventType = ES_NO_EVENT;
                                }
                            }
                            else
                            {
                                intangle += rotate_sample_Time*(ccw_target-currentAngle)/1000;
                                angular = kp*(ccw_target-currentAngle)+ki*intangle;
                                if (angular < 200 || angular > -200)
                                {
                                    kp = 12;
                                    ki = 1;
                                }
                                else if (angular > 600)
                                {
                                    angular = 600;
                                }

                                Motor_LeftSpeed(velocity-angular);
                                Motor_RightSpeed(velocity+angular);
                                lastGyroZ = Gyro_ReadZ();
                                ES_Timer_InitTimer(ROTATE_TIMER, rotate_sample_Time);

                                ThisEvent.EventType = ES_NO_EVENT;
                            }
                        }
                        break;

                    case BUMPED:
                        velocity = -200*rate_damper;
                        break;
                }
            }
            break;

        default:
            break;
    }

    if (makeTransition)
    {
        ROTATE_RunFSM(EXIT_EVENT);
        currentState = nextState;
        ROTATE_RunFSM(ENTRY_EVENT);
    }
}

void PostRotate(ES_EventTyp_t EventType, uint8_t src, int16_t left, int16_t right)
{
    ES_Event PostEvent;

    left = left/10;
    if (left < 0)
    {
        left = (-left)|0x40;
    }
    right = right/10;
    if (right < 0)
    {
        right = (-right)|0x40;
    }

    PostEvent.EventType = EventType;
    PostEvent.EventParam = src|(right << 2)|(left << 9);
    PostRotateFSM(PostEvent);
}

