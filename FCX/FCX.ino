#include <Arduino.h>
#include <avr/eeprom.h>
#include "config.h"
#include <Wire.h>
#include <IMU.h>
#include <Motors.h>
#include <PID.h>
#include <Status.h>
#include <RC.h>
//#include <TinyGPS.h>
#include "LED.h"
#include "vars.h"

void setup() {


  Serial.begin(115200);
  
  LeerPID(&PIDPitch, &PIDRoll, &PIDYaw);

  //  ------------------------- Pitch --------------------------------- //
  
  // PITCH LEVEL
  pitch.SetLimits(150);
  pitch.SetILimits(50); 
  pitch.SetTunings(PIDPitch.p,PIDPitch.i,PIDPitch.d);  

  //  -------------------------- Roll --------------------------------- //

  // ROLL LEVEL
  roll.SetLimits(150);
  roll.SetILimits(50);
  roll.SetTunings(PIDRoll.p,PIDRoll.i,PIDRoll.d); 


  //  ------------------------ YAW ----------------------------------- //
  
  // YAW
  yaw.SetLimits(100);
  yaw.SetILimits(50);
  yaw.SetTunings(PIDYaw.p,PIDYaw.i,PIDYaw.d);
  
  // altH.SetLimits(100);
  // altH.SetILimits(50);
  // altH.SetTunings(2.00,0.20,0.10);

  //  --------------------------------------------------------------- //
  
  
  LeerOffSets(&offsetsData);
  
  // Inicializa Librerias
      
  motors.Init(MOTORS);
  radio.Init(CHANNELS);
  imu.Init(COMPASS);
  imu.ComplementaryFilter();

  LeerOffSets(&offsetsData);
  imu.SetOffsetData(offsetsData);

  // Calibrar Giroscopio
  
  EscribirOffSets(imu.CalibrateGyro());
  imu.SetOffsetData(offsetsData);

  // LED
  led.config(500, LEDPIN); // tiempo encendido, tiempo apagado, veces, pin // 50 = 50 milis

  SerialSend();
  
}

void loop() {

led.go();
  
#if COMPASS == 1

  if (!calMag) {
    
    angles = imu.ComplementaryFilter(compass.getHeading());
    
  } else {
    
    calMag = !compass.magCalibration();
    
  }
  
#else

  angles = imu.ComplementaryFilter();


#endif

  
  statusControl();
 // copterControl();
  if (quadStatus.getArming()) {
    
    copterControl();
  
  }
  
  else {
    if (Serial.available()) SerialCom(Serial.readStringUntil('\n'));
    motors.stop();  
  }
  
}

ISR(PCINT0_vect){
	radio.ISR_Read();
}

void DisableMillisTimer() {

  cli();

  TIMSK0 &= -(1 << TOIE0);

  sei();

}
