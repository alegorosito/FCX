#ifndef IMU_h
#define IMU_h
#define LIBRARY_VERSION 1.0

#include <Arduino.h>
#include <Wire.h>
#include "RC.h"

#define MPU 0x68
#define P_ACTIVACION_MPU 0x6B
#define ACELEROMETRO 0x3B
#define GIROSCOPIO 0x43

#define ACCEL_CONFIG 0x1C //Accelerometer configuration address
#define GYRO_CONFIG 0x1B //Gyro configuration address

#define ACCEL_SENS 0 // 0 = 2g, 1 = 4g, 2 = 8g, 3 = 16g
#define GYRO_SENS 0 // 0 = 250rad/s, 1 = 500rad/s, 2 1000rad/s, 3 = 2000rad/s
 
// Ratios de conversion
#define ACCESC 16384.0
#define GYESC 131.0
#define TEMPESC 340.0

#define MICROS 1000000.0

#define FPA 0.998
#define FPB 0.002

#define GYROLPF 0.99

#define GYROCOUNT 2000.0
#define ACCCOUNT 2000.0

#define RADAGRADOS 57.295779

struct offsetsAxis
{
	float giroPitch;
	float accPitch;
	float giroRoll;
	float accRoll;
	float giroYaw;
};

struct rawAxis
{
	float acc[3];
	float giro[3];
};

struct giroRates
{
	long pitch;
	long roll;
	long yaw;
};

struct axis
{
	float pitch;
	float roll;
	float yaw;
	float rateP;
	float rateR;
	float rateY;
};

class IMU
{

public:
	void Init(int compass);
	axis ComplementaryFilter(float mag = 0);
	offsetsAxis CalibrateGyro();
	offsetsAxis CalibrateAcc();
	void SetOffsetData(offsetsAxis offset);
	offsetsAxis GetOffsetData();
	float RestrictYaw(float yaw);
	rawAxis getRaw();
	rawAxis Compute();
	giroRates getGiro();

private:

	unsigned long t2, t3, tiempo;
	float anglePitch = 0, angleRoll = 0, pitch2;
	axis filtered = axis();
	offsetsAxis offsets;
	float roll2, roll3;
	int countGyro = 0, countAcc = 0, _compass = 0;
	int incrementDT = 0;
	bool calAcc = false, init = false;
	giroRates rates;
};

#endif