#ifndef Status_h
#define Status_h
#define LIBRARY_VERSION 1.0

#include <Arduino.h>
#include "Status.h"

#define MODE_LEVEL 0
#define MODE_LOITER 1
#define MODE_HOLDPOS 2

#define ARMING_ARM_STATE 1
#define ARMING_DISARM_STATE 0

#define GESTURE_LIMIT_1 1200
#define GESTURE_LIMIT_2 1700

class Status
{
	public:
		void Init();

		void setArming(int arming);
		bool getArming();

		void setMode(int mode);
		int getMode();

	private:
		int _mode = MODE_LEVEL;
		bool _arming;

};

#endif