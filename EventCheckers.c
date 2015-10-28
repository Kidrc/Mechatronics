#include "EventCheckers.h"
#include "ES_Framework.h"

#include <stdio.h>
#include "globalmacros.h"
#include "SearchCastle.h"

uint8_t CheckBumpers(void) {
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    uint16_t currentState = 0;
    uint16_t result = 0;
    static uint16_t lastState = 0;

    currentState = Sensors_CheckBumperStatus(BUMPER_ALL);

    result = lastState ^ currentState;

    if ((currentState & 0xFF) != 0xF8) {
        if (result) {
            thisEvent.EventType = BUMPED;
            thisEvent.EventParam = result;
            PostToplevelHSM(thisEvent);
            PostReturnCenterFSM(thisEvent);
            PostSearchCastleFSM(thisEvent);
            PostRotateFSM(thisEvent);
            dbugprintf("BUMPED = 0x%X\n", result);

            lastState = currentState;
            returnVal = TRUE;
        }
    }
    return returnVal;
}

uint8_t CheckTapes(void) {
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    static uint8_t currentState = 0, lastState = TAPE_RIGHT2 | TAPE_LEFT2;
    uint16_t result = TAPE_RIGHT2 | TAPE_LEFT2;

    currentState = Sensors_CheckTapeStatus(TAPE_RIGHT2 | TAPE_LEFT2);

    result = lastState ^ currentState;

    if (result) {
        thisEvent.EventType = TAPE;
        thisEvent.EventParam = result;

        PostToplevelHSM(thisEvent);
        PostReturnCenterFSM(thisEvent);
        PostSearchCastleFSM(thisEvent);

        lastState = currentState;
        dbugprintf("TAPE = 0x%X\n", result);
        returnVal = TRUE;
    }

    return returnVal;
}

uint8_t CheckTrackwire(void) {
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    static uint8_t currentState = 0, lastState = 0;
    static uint8_t lock = 0;
    static int count = 0;

    if (!lock) {
        currentState = Sensors_CheckTrackwire();

        if (currentState) {
            ++count;
        } else {
            count = 0;
        }

        if (count > 2) {
            lock = 1;
            thisEvent.EventType = TRACKWIRE;
            PostToplevelHSM(thisEvent);
            PostAlignFSM(thisEvent);
            returnVal = TRUE;

        }
    }
    return returnVal;
}

uint8_t CheckBeacon(void) {
    ES_Event thisEvent;
    uint8_t returnVal = FALSE;
    static uint8_t currentState = 0, lastState = 0, sum = 0;
    static uint8_t lock = 0;
    static int count = 0;

    static unsigned short int i = 0;
    static unsigned int *shifter, temp = 0;

    /*
    currentState = Sensors_CheckBeacon();
    for (i = 0; i < FILTER_DEPTH; i++) {
        shifter = &filterArray[(FILTER_DEPTH - i - 1)];
        temp = *shifter;
        *(shifter + 1) = temp;
        sum = sum + temp;

        if (i == (FILTER_DEPTH - 1)) {
            filterArray[0] = currentState;
            sum = sum + currentState;
        }
    }
    currentState = sum >> SHIFT_ITERATIONS;
    currentState = (lastState - (lastState * .05)) + (currentState * .05);

    if (beaconlock) {
        if ((currentState != lastState) && (currentState == 1)) {
            thisEvent.EventType = FOUND_BEACON;
            PostToplevelHSM(thisEvent);
            returnVal = TRUE;
        }
    }

    return returnVal;
     */

    if (beaconlock) {
        currentState = Sensors_CheckBeacon();
        if (currentState) {
            ++count;
        } else {
            count = 0;
        }

        if (count > 0) {
            beaconlock = 0;
            count = 0;

            thisEvent.EventType = FOUND_BEACON;
            PostToplevelHSM(thisEvent);

            returnVal = TRUE;

        }
    }
    return returnVal;

}
