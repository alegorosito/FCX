#ifndef PID_h
#define PID_h
#define LIBRARY_VERSION 1.0

#ifndef MICROS
	#define MICROS 100000.000 // Un segundo
#endif

#define PITCH 0
#define ROLL 1
#define YAW 2
#define BARO 3
#define LATLON 4

struct pidOut
{
  float pitch;
  float roll;
  float yaw;
};

struct pidData {
  float p;
  float i;
  float d;
};

class PID
{

  /** Constructor PID ***************************************************  
    Se setean las variables por defecto, establecidas por el usuario.
  *******************************************************************/
  public:

    /** Funciones *********************************
      Funciones publicas.
    **********************************************/

      float Process(float InputP, float SetPointP, int axis);
      void SetTunings(float KpP, float KiP, float KdP);
      void SetLimits(float limit);
      void SetILimits(float iLimit);
      void Initialize();
      void Reset();

    /** Funciones *********************************
      Funciones y/o variables privadas.
    **********************************************/
    private:
      unsigned long _lastTime, t, time1;
      float _Input = 0, _Output = 0, _Setpoint = 0;
      float _ITerm = 0, _lastInput = 0, _Error = 0;
      float _last_derivative = 0, _filter = 95;
      float _Kp = 0, _Ki = 0, _Kd = 0;
      float _outMin, _outMax, _outMinI, _outMaxI;
};

#endif