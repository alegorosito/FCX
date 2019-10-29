#ifndef LED_h
#define LED_h
#define LIBRARY_VERSION 1.0

#include "Arduino.h"

class LED
{

	public:
		void config(unsigned long on, int pint);
		void go();
	private:
		unsigned long timeLed = micros(), t1, tOn, tOff;
		int times, PINLED;
		bool status = true;

};

#endif
