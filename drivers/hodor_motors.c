#include "hodor_motors.h"
#include "globalmacros.h"
#include "hodor_battery.h"
#include <stdio.h>

void Motor_Init(void)
{
	PWM_Init();
	
	PWM_SetFrequency(PWM_FREQ);
	PWM_AddPins(PIN_PWMA|PIN_PWMB);
	
	IO_PortsSetPortOutputs(PORT_DIR, PIN_DIRA|PIN_DIRB);
}


void Motor_LeftSpeed(int speed)
{
    speed /= (Battery_Percentage()/1.02);
    if (speed < -1000)
    {
        speed = -1000;
    }
    else if (speed > 1000)
    {
        speed = 1000;
    }

	if (speed < 0)
	{
		IO_PortsClearPortBits(PORT_DIR, PIN_DIRB);
		PWM_SetDutyCycle(PIN_PWMB, -speed);
	}
	else
	{
		IO_PortsSetPortBits(PORT_DIR, PIN_DIRB);
		PWM_SetDutyCycle(PIN_PWMB, speed);
	}
}

void Motor_RightSpeed(int speed)
{
    if (speed < -1000)
    {
        speed = -1000;
    }
    else if (speed > 1000)
    {
        speed = 1000;
    }
    
	if (speed < 0)
	{
		IO_PortsSetPortBits(PORT_DIR, PIN_DIRA);
		PWM_SetDutyCycle(PIN_PWMA, -speed);
	}
	else
	{
		IO_PortsClearPortBits(PORT_DIR, PIN_DIRA);
		PWM_SetDutyCycle(PIN_PWMA, speed);			
	}	
}

int getInt(char *c)
{
	char temp;
	int result = 0;
	char negative = 0;
	int invalid = MAX_SPEED+MAX_SPEED+1;
	
        scanf("%c", &temp);
	*c = 0;
	
	while(temp != -1)
	{
            if (temp == '-')
            {
                    negative = 1;
            }
            else if (temp >= '0' && temp <= '9')
            {
                    result = result*10 + temp - '0';
                    invalid = 0;
            }
            else if (temp >= 'a' && temp <= 'z')
            {
                    *c = temp;
            }
	
            scanf("%c", &temp);
	}
	
	if (negative)
	{
		result = -result;
	}
	return result+invalid;
}

#ifdef _HODOR_TEST
void Motor_Test(void)
{
	char c = 0;
	int lspeed = 0, rspeed = 0, tempspeed = 0;
	char state = 0;
        char change = 0;

	
	printf("Motor test\n");
	printf("Instructions: 'q'->quit test; 't'->switch between motors; 'z'->increase positive speed; 'x'->increase negative speed; 'r'->reverse'\n", MAX_SPEED, MAX_SPEED);
	printf("LSpeed = %d, RSpeed = %d\n", lspeed, rspeed);
	
	while(c != 'q')
	{
		//tempspeed = getInt(&c);
            c = getchar();

            switch(c)
            {
                case 'z':
                    tempspeed += 100;
                    change = 1;
                    break;

                case 'x':
                    tempspeed -= 100;
                    change = 1;
                    break;

                case 's':
                    tempspeed = 0;
                    change = 1;
                    break;

                case 'r':
                    tempspeed = -tempspeed;
                    change = 1;
                    break;
                    
                default:
                    change = 0;
                    break;
            }

		if (tempspeed <= MAX_SPEED && tempspeed >= -MAX_SPEED && change)
		{
			if (state == 0)
			{
				lspeed = tempspeed;
				Motor_LeftSpeed(lspeed);
				printf("LSpeed = %d, RSpeed = %d\n", lspeed, rspeed);
			}
			else
			{
				rspeed = tempspeed;
				Motor_RightSpeed(rspeed);
				printf("LSpeed = %d, RSpeed = %d\n", lspeed, rspeed);
			}
		}
		
		if (c == 't')
		{
			state = !state;
			
			if (state == 0)
			{
                            tempspeed = 0;
				printf("Setting left speed\n");	
			}
			else
			{
                            tempspeed = 0;
				printf("Setting right speed\n");
			}
			printf("LSpeed = %d, RSpeed = %d\n", lspeed, rspeed);
		}

            change = 0;
	}
	printf("Motor test ended\n");
}
#endif