#ifndef Motors_h
#define Motors_h
#define LIBRARY_VERSION 1.0

#include "Arduino.h"

#ifdef QUAD
	int _nmotors = 6;
#endif
#ifdef HEXA
	int _nmotors = 6;
#endif

#ifndef MOTORS
	#define MOTORS 6
#endif

#ifndef PWMMIN
	#define PWMMIN 1020
#endif

#ifndef PWMMAX
	#define PWMMAX 1864
#endif

#define ARMPWM 1200

class Motors
{
	public:
		void Init(int motors);
		void setSpeed(int speeds[MOTORS]);
		void stop();
	private:
		unsigned long escTime, pwmTime, M0, M1, M2, M3, M4, M5;
		int _motors[MOTORS];
		int _ms = 0;
		bool test = false;
};

#endif