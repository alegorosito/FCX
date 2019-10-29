#include "Arduino.h"
#include "PID.h"

float PID::Process( float Input, float SetPoint, int axis )
{

  _Input = Input;
  _Setpoint = SetPoint;

  unsigned long _now = micros();  
  unsigned long timeChange = _now - _lastTime;

  float error = _Setpoint - _Input;
 
  if( error > 180 && axis == YAW ) {

    error = error - 360;
  
  } else if ( error < -180 && axis == YAW ) {

    error = error + 360;
  
  }

    if ( timeChange > MICROS )
    {

      timeChange = 0;
      Reset();
    
    }

    float dt = timeChange / MICROS;

    if ( abs(_ITerm) < abs(error) ) { 
    
      _ITerm+= ( _Ki * dt ) * -error; 

    } else {

      _ITerm+= ( _Ki * dt ) * error;

    }
       
    if ( _ITerm < _outMinI ) _ITerm = _outMinI;
    if ( _ITerm > _outMaxI ) _ITerm = _outMaxI;

    float _derivative = ( _Kd / dt ) * ( _Input - _lastInput );

    _Output = _Kp * error + _ITerm - _derivative;

    if ( _Output < _outMin ) _Output = _outMin;
    if ( _Output > _outMax ) _Output = _outMax;

    _Error = error;

    _lastInput = _Input;
    _lastTime = _now;
  
  return _Output;

}

void PID::SetTunings( float Kp, float Ki, float Kd )
{

   _Kp = Kp;
   _Ki = Ki;
   _Kd = Kd;

   if ( _Kp < 0 ) _Kp = 0;
   if ( _Ki < 0 ) _Ki = 0;
   if ( _Kd < 0 ) _Kd = 0;  

}

void PID::SetLimits( float limit )
{


  _outMin = -limit;
  _outMax = limit;


}

void PID::SetILimits( float iLimit )
{


  _outMinI = -iLimit;
  _outMaxI = iLimit;


}

void PID::Initialize()
{

  _lastInput = _Input;
  _ITerm = _Output;

  if ( _ITerm < _outMinI ) _ITerm = _outMinI;
  if ( _ITerm > _outMaxI ) _ITerm = _outMaxI;

  Reset();

}

void PID::Reset()
{

  _ITerm = 0;

}