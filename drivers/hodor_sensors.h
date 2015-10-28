#ifndef HODOR_SENSORS_H
#define HODOR_SENSORS_H

#include "IO_Ports.h"
#include "AD.h"

#define BUMPER_PORT PORTZ
#define TAPE_PORT PORTV
#define TRACKWIRE_PORT PORTY
#define BEACON_PORT PORTZ
//#define BEACON_PORT PORTY

#define BUMPER_COUNT 5

#define BUMPER_RIGHT PIN3
#define BUMPER_FRONT_RIGHT PIN4
#define BUMPER_FRONT_LEFT PIN5
#define BUMPER_LEFT PIN6
#define BUMPER_NOTCH PIN7
#define BUMPER_ALL BUMPER_RIGHT|BUMPER_FRONT_RIGHT|BUMPER_FRONT_LEFT|BUMPER_LEFT|BUMPER_NOTCH

#define TAPE_COUNT 5


#define TAPE_RIGHT2 AD_PORTV7
#define TAPE_LEFT2 AD_PORTV6
#define TAPE_MIDDLE AD_PORTV5
#define TAPE_RIGHT1 AD_PORTV4
#define TAPE_LEFT1 AD_PORTV3
#define TAPE_ALL TAPE_RIGHT1|TAPE_LEFT1|TAPE_MIDDLE|TAPE_RIGHT2|TAPE_LEFT2

#define TAPE_HIGH 600
#define TAPE_LOW 300

#define TRACKWIRE_PIN PIN11
#define BEACON_PIN PIN11
//#define BEACON_PIN PIN8
#define BEACON_ANALOG_PIN AD_PORTV8

#define BEACON_HIGH 800
#define BEACON_LOW 60

#define BUMPER(x) ThisEvent.EventParam&(x)

void Sensors_Init(void);

uint16_t Sensors_CheckBumperStatus(uint16_t bumper);
uint16_t Sensors_CheckTapeStatus(uint16_t tape);
uint16_t Sensors_CheckTrackwire(void);
uint16_t Sensors_CheckBeacon(void);


void Sensors_Test(void);

#endif