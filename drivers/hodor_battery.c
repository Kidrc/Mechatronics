#include "hodor_battery.h"
#include "globalmacros.h"


#include <stdio.h>

const double vol_div = 10/0.98;

void Battery_Init(void)
{
    AD_Init();

    AD_AddPins(BAT_VOLTAGE);
}

double Battery_Percentage(void)
{
    //return AD_ReadADPin(BAT_VOLTAGE)*vol_div/1023/3;
    return AD_GetBatVoltage()*vol_div/1023/3;
}

#ifdef _HODOR_TEST
void Battery_Test(void)
{
    char c = 0;

    printf("Battery Percentage Test\n");

    while(c != 'q')
    {
        c = getchar();

        if (c != -1)
        {
            printf("Battery Percentage = %.2f\n", Battery_Percentage());
        }
    }
}
#endif