#include "CopterControl.h"


int* CopterControl::level(int throttle, pidOut pidx)
{

	motors[0] = throttle;
	motors[1] = throttle;
	motors[2] = throttle;
	motors[3] = throttle;
	/*int nmotors = _motors.getMotors();
	int motorsSpd[nmotors];*/
	
	// Sum of PIDs results
	//		for Pitch 
	motors[0] += pidx.pitch;
    motors[1] -= pidx.pitch;
    motors[2] += pidx.pitch;
    motors[3] -= pidx.pitch;

    motors[0] += pidx.roll;
	motors[1] -= pidx.roll;
	motors[2] -= pidx.roll;
	motors[3] += pidx.roll;
	
/*	if (nmotors > 4) motors[4] = pidx.roll;
    if (nmotors > 5) motors[5] = pidx.roll;*/

	// Yaw
	motors[0] += pidx.yaw;
	motors[1] += pidx.yaw;
	motors[2] -= pidx.yaw;
	motors[3] -= pidx.yaw;

/*    if (nmotors > 4) motors[4] = pidx.yaw;
    if (nmotors > 5) motors[5] = pidx.yaw;*/


    _m.speeds[0] = motors[0];
    _m.speeds[1] = motors[1];
    _m.speeds[2] = motors[2];
    _m.speeds[3] = motors[3];

    return (_m.speeds);
}
