#ifndef HODOR_MOTORS_H
#define HODOR_MOTORS_H

#include "pwm.h"
#include "IO_Ports.h"

//pin mapping
#define PORT_DIR PORTZ //portx
#define PIN_DIRA PIN8 //pin5
#define PIN_DIRB PIN9 //pin7
#define PIN_PWMA PWM_PORTY10
#define PIN_PWMB PWM_PORTY12

#define PWM_FREQ PWM_20KHZ

#define MAX_SPEED 1000

void Motor_Init(void);
void Motor_LeftSpeed(int speed);
void Motor_RightSpeed(int speed);


void Motor_Test(void);

#endif