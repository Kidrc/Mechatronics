
//#define _HODOR_NORMAL
//#define _HODOR_TEST

#include "hodor_gyro.h"
#include "hodor_sensors.h"
#include "hodor_mech.h"
#include "hodor_motors.h"
#include "hodor_battery.h"
#include "toplevel.h"
#include "globalmacros.h"

#include <stdio.h>
#include <xc.h>
#include "ES_Configure.h"
#include "ES_Framework.h"
#include "serial.h"
#include "BOARD.h"

void reset(void);


#ifdef _HODOR_NORMAL
#warning _________________________________NORMAL_MODE_______________________________________

int main(void)
{
    ES_Return_t ErrorType;
    int i;

    BOARD_Init();

    printf("HODOR starts to find crown\n");
    printf("Using the 3rd Generation Events & Services Framework\n");

    Battery_Init();
    Motor_Init();
    Sensors_Init();
    Mech_Init();
    Gyro_Init();
    
    ErrorType = ES_Initialize();
    printf("ErrorType = %d\n", ErrorType);
    if (ErrorType == Success)
    {
        for (i = 0; i < 1000000; ++i);
        Mech_Grabber(GRAB_UP);

        ErrorType = ES_Run();
    }
    else
    {
        printf("Error Type: %d\n", ErrorType);
    }

    switch (ErrorType) {
    case FailedPointer:
        printf("Failed on NULL pointer\n");
        break;
    case FailedInit:
        printf("Failed Initialization\n");
        break;
    default:
        printf("Other Failure: %d\n",ErrorType);
        break;
    }
    for (;;)
        ;

}
#endif

#ifdef _HODOR_TEST
#warning ____________________________________GOD_MODE______________________________________

int main(void)
{
	char c = 0;
        
        BOARD_Init();

        Gyro_Init();

        Battery_Init();
	Motor_Init();
	Sensors_Init();
	Mech_Init();
        
        printf("God Mode\n");
        printf("Instructions: m->Motor test; s->Sensor test; r->Servo test; t->Timer test; b->Battery Test\n");
        printf("Instructions: i->show instructions again\n");
        printf("Instructions: g->Gyro test\n");

	while(1)
	{
            c = getchar();

            switch(c)
            {
                case 'm':
                        Motor_Test();
                        break;

                case 's':
                        Sensors_Test();
                        break;

                case 'r':
                        Mech_Test();
                        break;

                case 't':
                    ES_Initialize();
                    ES_Run();
                    break;

                case 'b':
                    Battery_Test();
                    break;

                case 'i':
                    printf("God Mode\n");
                    printf("Instructions: m->Motor test; s->Sensor test; r->Servo test; t->Timer test; b->Battery Test\n");
                    break;

                case 'g':
                    Gyro_Test();
                    break;

                      
            }
	}
}
#endif