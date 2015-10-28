#include "EventCheckers.h"
#include "ES_Framework.h"

#include <stdio.h>
uint8_t CheckBumpers(void)
{
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    uint16_t currentState = 0;
    uint16_t result = 0;
    static uint16_t lastState = 0;

    currentState = Sensors_CheckBumperStatus(BUMPER_ALL);

    result = lastState ^ currentState;

    if (result && (result & 0x78) != 0x78)
    {
        thisEvent.EventType = BUMPED;
        thisEvent.EventParam = result;
        PostToplevelHSM(thisEvent);

        printf("BUMPED = 0x%X\n", result);

        lastState = currentState;
        returnVal = TRUE;
    }

    return returnVal;
}

uint8_t CheckTapes(void)
{
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    static uint8_t currentState = 0, lastState = 0;

    currentState = Sensors_CheckTapeStatus(TAPE_ALL);

    lastState ^= currentState;

    if (lastState)
    {
        thisEvent.EventType = TAPE;
        thisEvent.EventParam = lastState;
        PostToplevelHSM(thisEvent);

        lastState = currentState;
        returnVal = TRUE;
    }

    return returnVal;
}

uint8_t CheckTrackwire(void)
{
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    static uint8_t currentState = 0, lastState = 0;

    currentState = Sensors_CheckTrackwire();

    if (lastState != currentState)
    {
        thisEvent.EventType = TRACKWIRE;
        PostToplevelHSM(thisEvent);

        lastState = currentState;
        returnVal = TRUE;
    }

    return returnVal;
}

uint8_t CheckBeacon(void)
{
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    uint8_t currentState = 0, lastState = 0;

    currentState = Sensors_CheckBeacon();
    
    if (lastState != currentState)
    {
        thisEvent.EventType = FOUND_RULING;
        PostToplevelHSM(thisEvent);
        
        lastState = currentState;
        returnVal = TRUE;
    }
    
    return returnVal;
    
}
