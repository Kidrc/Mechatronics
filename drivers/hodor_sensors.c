#include "hodor_sensors.h"
#include "globalmacros.h"

#include <stdio.h>


void Sensors_Init(void)
{
	IO_PortsSetPortInputs(BUMPER_PORT, BUMPER_ALL);
	
	AD_Init();
	AD_AddPins(TAPE_ALL|BEACON_ANALOG_PIN);

        IO_PortsSetPortInputs(TRACKWIRE_PORT, TRACKWIRE_PIN);
        IO_PortsSetPortInputs(BEACON_PORT, BEACON_PIN);
}

uint16_t Sensors_CheckBumperStatus(uint16_t bumper)
{
	return (~(uint16_t)IO_PortsReadPort(BUMPER_PORT)) & bumper;
}

uint16_t Sensors_CheckTapeStatus(uint16_t tape)
{
	static uint8_t status = 0;
        unsigned int value = 0;
        const uint8_t TAPE[TAPE_COUNT] = {TAPE_RIGHT1, TAPE_LEFT1, TAPE_MIDDLE, TAPE_LEFT2, TAPE_RIGHT2};
        uint8_t i;


        for (i = 0; i < TAPE_COUNT; ++i)
        {
            value = AD_ReadADPin(tape & TAPE[i]);


            if (value > TAPE_HIGH)
            {
                status |= tape & TAPE[i];
            }
            else if (value < TAPE_LOW)
            {
                status &= ~(tape & TAPE[i]);
            }
#ifdef _HODOR_TEST

            if (tape & TAPE_LEFT2)
                printf("Value = %d\n", value);

#endif
        }

	return status & tape;
}

uint16_t Sensors_CheckTrackwire(void)
{
    static uint8_t lastread = 0;
    uint8_t read, ret;
    static int startTime;
    static uint8_t reset = 1;

    if (reset)
    {
        startTime = ES_Timer_GetTime();
        reset = 0;
    }

   return (IO_PortsReadPort(TRACKWIRE_PORT) & TRACKWIRE_PIN) == 0;
   
   
}

uint16_t Sensors_CheckBeacon(void)
{
    //return ((IO_PortsReadPort(BEACON_PORT) & BEACON_PIN) == 0);
    uint16_t value;
    static uint16_t status = 0;
    
    value = AD_ReadADPin(BEACON_ANALOG_PIN);

    if (value > BEACON_HIGH)
    {
        return status = 0;
    }
    else if (value < BEACON_LOW)
    {
        return status = 1;
    }
    else
    {
        return status;
    }
}

#ifdef _HODOR_TEST
void Sensors_Test(void)
{
	char c = 0;
	
	printf("Sensor Test\n");
	printf("Instructions: 'b'->show bumpers status; 't'->show tapes status; 'w'->show trackwire status; 'd'->show beacon status\n");
	
	while(c != 'q')
	{
		c = getchar();
		
		if (c != 0)
		{
			switch(c)
			{
				case 'b':
					printf("Bumpers:\n");
					printf("RIGHT=%d, ", Sensors_CheckBumperStatus(BUMPER_RIGHT));
					printf("FRONT_RIGHT=%d, ", Sensors_CheckBumperStatus(BUMPER_FRONT_RIGHT));
					printf("FRONT_LEFT=%d, ", Sensors_CheckBumperStatus(BUMPER_FRONT_LEFT));
					printf("LEFT=%d, ", Sensors_CheckBumperStatus(BUMPER_LEFT));
					printf("NOTCH=%d\n", Sensors_CheckBumperStatus(BUMPER_NOTCH));
					break;
				
				case 't':
					printf("Tapes:\n");
					printf("RIGHT2=%d, ", Sensors_CheckTapeStatus(TAPE_RIGHT2));
					printf("RIGHT1=%d, ", Sensors_CheckTapeStatus(TAPE_RIGHT1));
					printf("LEFT2=%d, ", Sensors_CheckTapeStatus(TAPE_LEFT2));
					printf("LEFT1=%d, ", Sensors_CheckTapeStatus(TAPE_LEFT1));
					printf("MIDDLE=%d\n", Sensors_CheckTapeStatus(TAPE_MIDDLE));
					break;
                            case 'w':
                                printf("Trackwire=%d\n", Sensors_CheckTrackwire());
                                break;

                            case 'd':
                                printf("Beacon=%d\n", Sensors_CheckBeacon());
                                break;
                        }
		}
	}
	printf("Sensor test ended\n");
}
#endif