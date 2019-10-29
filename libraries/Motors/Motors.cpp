#include "Motors.h"

void Motors::Init(int ms)
{
	_ms = ms;

	if (_ms == 4) {
		DDRD |= B00111100;
	}

	if (_ms == 6) {
		DDRD |= B11111100;
	}

	pwmTime = micros();
}

void Motors::stop()
{
	int stopSpeeds[MOTORS];
	
	for (int i = 0; i < MOTORS; ++i)
	{
		stopSpeeds[i] = 1000;
	}

	setSpeed(stopSpeeds);
}

void Motors::setSpeed(int speeds[MOTORS])
{ 
	pwmTime = micros();

	if (_ms == 4) {

		M0 = speeds[0] + pwmTime; 
		M1 = speeds[1] + pwmTime; 
		M2 = speeds[2] + pwmTime; 
		M3 = speeds[3] + pwmTime; 

		PORTD |= B00111100;

		escTime = pwmTime; 

		pwmTime += PWMMAX; 
		
		while(escTime < pwmTime) {

			escTime = micros();
			
			if(M0 < escTime) PORTD &= B11111011;
			if(M1 < escTime) PORTD &= B11110111;
			if(M2 < escTime) PORTD &= B11101111;
			if(M3 < escTime) PORTD &= B11011111;
			
		}
	}

	if (_ms == 6) {

		if (M0 < PWMMIN) M0 = PWMMIN;  M0 = speeds[0] + pwmTime;
		if (M1 < PWMMIN) M1 = PWMMIN;  M1 = speeds[1] + pwmTime;
		if (M2 < PWMMIN) M2 = PWMMIN;  M2 = speeds[2] + pwmTime;
		if (M3 < PWMMIN) M3 = PWMMIN;  M3 = speeds[3] + pwmTime;
		if (M4 < PWMMIN) M4 = PWMMIN;  M4 = speeds[4] + pwmTime;
		if (M5 < PWMMIN) M5 = PWMMIN;  M5 = speeds[5] + pwmTime;

		PORTD |= B11111100;

		escTime = pwmTime; 

		pwmTime += PWMMAX; 
		
		while(escTime < pwmTime) {

			escTime = micros();
			
			//noInterrupts();

			if(M0 < escTime) PORTD &= B11111011;
			if(M1 < escTime) PORTD &= B11110111;
			if(M2 < escTime) PORTD &= B11101111;
			if(M3 < escTime) PORTD &= B11011111;
			if(M4 < escTime) PORTD &= B10111111;
			if(M5 < escTime) PORTD &= B01111111;

			//interrupts();
		}

	}
	
}