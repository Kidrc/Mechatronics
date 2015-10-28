#ifndef HODOR_MECH_H
#define HODOR_MECH_H

#include "RC_Servo.h"
#include "BOARD.h"

#define GRAB_PIN RC_PORTY06

#define GRAB_INIT 0
#define GRAB_DOWN 1
#define GRAB_UP 2
#define SHAKE_UP 3
#define SHAKE_DOWN 4

#define GRAB_UP_TIME 2410
#define GRAB_INIT_TIME 2000
#define GRAB_DOWN_TIME 1620

#define SHAKE_UP_TIME 1750
#define SHAKE_DOWN_TIME 1550

void Mech_Init(void);

void Mech_Grabber(uint8_t dir);

void Mech_Test(void);


#endif