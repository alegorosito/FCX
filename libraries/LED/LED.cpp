#include "LED.h"

void LED::config(unsigned long on, int pint)
{
	PINLED = pint;
	pinMode(PINLED, OUTPUT);
	tOn = on;
}

void LED::go()
{

	if (micros() - t1 > tOn * 1000)
	{
		status = !status;
		digitalWrite(PINLED, status);
		t1 = micros();
	}

}