#define MICROS 1000000.0
// Configurations
#define COMPASS 0 // If compass is not available the COMPASS 0

//#define QUAD
#define HEXA

#ifdef QUAD
  #define MOTORS 4
#endif
#ifdef HEXA
  #define MOTORS 6
#endif

#define CHANNELS 5

#define CENTERSTICK 1500

#define ARMCOUNT 500 // Time to arm/disarm the copter

#define AUTOTRIM 0

#define TIMETRIMACC 30000000
#define TIMEGROUNDT 30000000

//#define BMP180_BARO // uncomment if baro is the BMP180
//#define MS5611 // uncomment if baro is the MS5611

#define ALTHOLD 0 // if not baro available then ALTHOLD 0

#define PRESPROM 10

#define SEALEVELPRESSURE 101302.16

#define LEDPIN 13 // pin donde se encuentra conectado el LED

#ifdef QUADX
  int motorCount = 4;
#endif

#ifdef HEXA
  int motorCount = 6;
#endif

#define SCALEPID 1000.0
