#ifndef CopterControl_h
#define CopterControl_h
#define LIBRARY_VERSION 1.0

#include "Arduino.h"
#include "../PID/PID.h"
#include "../Motors/Motors.h"
#include "../RC/RC.h"
#include "../Status/Status.h"
#include "../IMU/IMU.h"

struct motorsOut
{
	int speeds[4] = {0, 0, 0, 0};
};

class CopterControl
{
	public:
		int* level(int throttle, pidOut pidx);

	private:
		Motors _motors;
		Status _status;
		int motors[4];
		motorsOut _m;
};

#endif