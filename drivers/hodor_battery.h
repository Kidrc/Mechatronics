#ifndef BATTERY_H
#define BATTERY_H

#include "AD.h"

void Battery_Init(void);

double Battery_Percentage(void);

void Battery_Test(void);

#endif