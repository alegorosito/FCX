/*
BMP180.h - Header file for the BMP180 Barometric Pressure Sensor Arduino Library.
Copyright (C) 2012 Love Electronics Ltd (loveelectronics.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the version 3 GNU General Public License as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

 Datasheet for BMP180:
 http://www.bosch-sensortec.com/content/language1/downloads/BST-BMP180-DS000-07.pdf

*/

#ifndef BMP180_h
#define BMP180_h

#include <inttypes.h>
#include "../Wire/Wire.h"

#define BMP180_Address 0x77

#define ChipIdData 0x55
#define ControlInstruction_MeasureTemperature 0x2E
#define ControlInstruction_MeasurePressure 0x34

#define Reg_ChipId 0xD0
#define Reg_Control 0xF4
#define Reg_CalibrationStart 0xAA
#define Reg_CalibrationEnd 0xBE
#define Reg_AnalogConverterOutMSB 0xF6
#define Reg_SoftReset 0xE0
#define SoftResetInstruction 0xB6

#define ErrorCode_1 "Entered sample resolution was invalid. See datasheet for details."
#define ErrorCode_1_Num 1

#define BMP180_Mode_UltraLowPower		0
#define BMP180_Mode_Standard			1
#define BMP180_Mode_HighResolution		2
#define BMP180_Mode_UltraHighResolution	3

class BMP180 {

	public:
	  BMP180();

	  void Initialize();

	  int GetUncompensatedTemperature();
	  float CompensateTemperature(int uncompensatedTemperature);
	  
	  long GetUncompensatedPressure();
	  long CompensatePressure(long uncompensatedPressure);
	  
	  float GetTemperature();
	  long GetPressure();

	  float GetAltitude(float currentSeaLevelPressureInPa);
	  
	  void SoftReset();
	  uint8_t SetResolution(uint8_t sampleResolution, bool oversample);

	  void PrintCalibrationData();

	  uint8_t EnsureConnected();
	  uint8_t IsConnected;
	  char* GetErrorText(int errorCode);
	protected:
	  void Write(int address, int byte);
	  uint8_t* Read(int address, int length);
	  void Read2(int address, int length, uint8_t buffer[]);
	private:
		uint8_t OversamplingSetting;
        bool Oversample;
		int ConversionWaitTimeMs;
		int LastTemperatureData;
		int LastTemperatureTime;
		int AcceptableTemperatureLatencyForPressure;
		
		int Calibration_AC1;
        int Calibration_AC2;
        int Calibration_AC3;
        unsigned int Calibration_AC4;
        unsigned int Calibration_AC5;
        unsigned int Calibration_AC6;
        int Calibration_B1;
        int Calibration_B2;
        int Calibration_MB;
        int Calibration_MC;
        int Calibration_MD;
        int value_ant, pressure_ant;
        unsigned long time1 = 0, time2 = 0;
};

#endif