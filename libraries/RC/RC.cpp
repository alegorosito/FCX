#include "Arduino.h"
#include "IMU.h"
#include "RC.h"
#include "Motors.h"

void RC::Init(int numch) 
{
	#ifndef NCH
		#define NCH numch
		uint8_t prevCh[NCH];
	#endif
	
  // Habilitamos las interrupciones para la lectura del radio
	PCICR |= (1 << PCIE0);   
	PCMSK0 |= (1 << PCINT0);  
	PCMSK0 |= (1 << PCINT1);
	PCMSK0 |= (1 << PCINT2);
	PCMSK0 |= (1 << PCINT3);
	PCMSK0 |= (1 << PCINT4);

}

int RC::getChannel(int numch)
{
	return ch.val[numch];
} 

float RC::throttle()
{
  int thr = map(ch.val[1], CMIN, CMAX, CMINLIM, CMAXLIM);

	return thr;
}

float RC::roll()
{
  
  //float angle = map(ch.val[2], CMIN, CMAX, -AMAX, AMAX) / ESCALARX;

  //if (angle < 1.00 && angle > -1.00) angle = 0;

  _roll[_countRoll] = map(ch.val[2], CMIN, CMAX, -AMAX, AMAX) / ESCALARX;
  _r += _roll[_countRoll];
  _r /= 6.0;

  if (_countRoll < (CANTPROM - 1)) _countRoll++; else _countRoll = 0;
//  if (_r < 1.00 && _r > -1.00) _r = 0;
    
  return _r;
}

float RC::pitch()
{
  //float angle = map(ch.val[3], CMIN, CMAX, AMAX, -AMAX) / ESCALARX;
  
  //if (angle < 1.00 && angle > -1.00) angle = 0;

  _pitch[_countPitch] = map(ch.val[3], CMIN, CMAX, AMAX, -AMAX) / ESCALARX;
  _p += _pitch[_countPitch];
  _p /= 6.0;

  if (_countPitch < (CANTPROM - 1)) _countPitch++; else _countPitch = 0;
//	if (_p < 1.00 && _p > -1.00) _p = 0;

  return _p;
}

float RC::yaw()
{
  IMU imuY;

  float y = (map(ch.val[4], CMIN, CMAX, -AMAX, AMAX) / ESCALARX);

  if ((y > 4.00 || y < -4.00) && getChannel(1) > ARMPWM) {

    _yaw += y / 50.00;
    _yaw = imuY.RestrictYaw(_yaw);

  }


	return _yaw;
}

float RC::aux1()
{
	return ch.val[5];
}

float RC::aux2()
{
	return ch.val[6];
}

rcData RC::getRcData() {
  
  rc.pitch = pitch();
  rc.roll = roll();
  rc.yaw = yaw();
  rc.aux1 = aux1();
  rc.aux2 = aux2();
  rc.throttle = throttle();

  return rc;
}

void RC::ResetYaw(float y) {
  _yaw = y;
}

void RC::ISR_Read(){
// Lee las interrupciones y calcula el ancho de los pulsos

noInterrupts();

float dtx = micros();

// Canal 1
  if(prevCh[1] == 0 && PINB & B00000001){         
    prevCh[1] = 1;                                
    ch.temp[1] = dtx;                              
  }
  else if(prevCh[1] == 1 && !(PINB & B00000001)){  
    prevCh[1] = 0;                                 
    ch.val[1] = dtx - ch.temp[1];      
  }

// Canal 2
if(prevCh[2] == 0 && PINB & B00000010){         
    prevCh[2] = 1;                              
    ch.temp[2] = dtx;                            
  }
  else if(prevCh[2] == 1 && !(PINB & B00000010)){  
    prevCh[2] = 0;                                 
    ch.val[2] = dtx - ch.temp[2];      
  }

// Canal 3
  if(prevCh[3] == 0 && PINB & B00000100){         
    prevCh[3] = 1;                                
    ch.temp[3] = dtx;                              
  }
  else if(prevCh[3] == 1 && !(PINB & B00000100)){  
    prevCh[3] = 0;                                 
    ch.val[3] = dtx - ch.temp[3];      
  }

// Canal 4
if(prevCh[4] == 0 && PINB & B00001000){         
    prevCh[4] = 1;                              
    ch.temp[4] = dtx;                            
  }
  else if(prevCh[4] == 1 && !(PINB & B00001000)){  
    prevCh[4] = 0;                                 
    ch.val[4] = dtx - ch.temp[4];      
  }

#if NCH > 4
  // Canal 5
if(prevCh[5] == 0 && PINB & B00010000){         
    prevCh[5] = 1;                              
    ch.temp[5] = dtx;                            
  }
  else if(prevCh[5] == 1 && !(PINB & B00010000)){  
    prevCh[5] = 0;                                 
    ch.val[5] = dtx - ch.temp[5];      
  }
#endif

#if NCH > 5
  // Canal 5
if(prevCh[6] == 0 && PINB & B00010000){         
    prevCh[6] = 1;                              
    ch.temp[6] = dtx;                            
  }
  else if(prevCh[6] == 1 && !(PINB & B00010000)){  
    prevCh[6] = 0;                                 
    ch.val[6] = dtx - ch.temp[6];      
  }
#endif

interrupts();

}
