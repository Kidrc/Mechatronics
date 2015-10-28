#include "hodor_mech.h"
#include "globalmacros.h"

#include <stdio.h>

void Mech_Init(void)
{
	RC_Init();
	
	RC_AddPins(GRAB_PIN);

        RC_SetPulseTime(GRAB_PIN, GRAB_UP_TIME);
}

void Mech_Grabber(uint8_t dir)
{
	if (dir == GRAB_INIT)
	{
		RC_SetPulseTime(GRAB_PIN, GRAB_INIT_TIME);
	}
	else if (dir == GRAB_DOWN)
	{
		RC_SetPulseTime(GRAB_PIN, GRAB_DOWN_TIME);
	}
        else if (dir == GRAB_UP)
        {
            RC_SetPulseTime(GRAB_PIN, GRAB_UP_TIME);
        }
        else if (dir == SHAKE_UP)
        {
            RC_SetPulseTime(GRAB_PIN, SHAKE_UP_TIME);
        }
        else if (dir == SHAKE_DOWN)
        {
            RC_SetPulseTime(GRAB_PIN, SHAKE_DOWN_TIME);
        }

}

#ifdef _HODOR_TEST
void Mech_Test(void)
{
	char c = 0;
	int pulsetime = GRAB_INIT_TIME;
	char modified = 0;
	
	printf("Servo test\n");
	printf("Instructions: 'a'->+1; 'b'->+10; 'c'->100; the capital cases do the minus operation;\n");
        printf("'u'->UP position; 'd'->DOWN position\n");
	printf("Instructions: pulsetime range %d ~ %d\n", MINPULSE, MAXPULSE);
        printf("pulsetime = %d\n", pulsetime);
	
	while(c != 'q')
	{
		c = getchar();
		
		switch(c)
		{
			case 'a':
				pulsetime++;
				modified = 1;
				break;
			
			case 'b':
				pulsetime += 10;
				modified = 1;
				break;
			
			case 'c':
				pulsetime += 100;
				modified = 1;
				break;
			
			case 'A':
				pulsetime--;
				modified = 1;
				break;
			
			case 'B':
				pulsetime -= 10;
				modified = 1;
				break;
			
			case 'C':
				pulsetime -= 100;
				modified = 1;
				break;

                    case 'i':
                        pulsetime = GRAB_INIT_TIME;
                        modified = 1;
                        break;

                    case 'd':
                        pulsetime = GRAB_DOWN_TIME;
                        modified = 1;
                        break;
                    case 'u':
                        pulsetime = GRAB_UP_TIME;
                        modified = 1;
                        break;

		}
		
		if (modified)
		{
			if (pulsetime >= MINPULSE)
			{
				RC_SetPulseTime(GRAB_PIN, pulsetime);
			}
			printf("pulsetime = %d\n", pulsetime);
			
			modified = 0;
		}
	}
	printf("Mechanical parts pest ended\n");
}
#endif