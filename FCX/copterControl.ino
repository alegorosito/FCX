void copterControl() {
   
    #if AUTOTRIM == 0
      

      if (gpsMode) {
        
        rc = Headless(radio.getRcData());
            
        // Pitch Headless
        pidLevel.pitch = pitch.Process(angles.pitch - offsetsData.accPitch, rc.pitch * RCSCALE, PITCH);
        
        // Roll Headless
        pidLevel.roll = roll.Process(angles.roll - offsetsData.accRoll, rc.roll * RCSCALE, ROLL); 
        
        
      } else {

        rc = radio.getRcData();
        
        // PITCH PID ANGLE AND ANGULAR RATE 
        pidLevel.pitch = pitch.Process((angles.pitch - offsetsData.accPitch), rc.pitch * RCSCALE, PITCH);
  
        // ROLL PID ANGLE AND ANGULAR RATE
        pidLevel.roll  = roll.Process((angles.roll - offsetsData.accRoll), rc.roll * RCSCALE, ROLL);
        
      }

      // YAW RATE
      pidLevel.yaw = yaw.Process(angles.yaw, rc.yaw, YAW);
 
     #elif AUTOTRIM == 1
      
       pidLevel.pitch = pitch.Process(angles.pitch, rc.pitch);
       pidLevel.roll = roll.Process(angles.roll, rc.roll);
       pidLevel.yaw = yaw.Process(angles.rateY, rc.yaw);
      
       trimAcc();

     #endif

     #if ALTHOLD == 1
    
       altVal = altH.Process(Alt, setAlt);
      
     #endif
   
  //if(radio.getChannel(5) < GESTURE_LIMIT_1) 
  
  level(altVal);

}

void level(float altVal) {
 
  
  #ifdef QUAD
  
    int m[4];
   
    m[0] = rc.throttle + pidRate.pitch + pidLevel.roll + pidLevel.yaw;
    m[1] = rc.throttle + pidRate.pitch - pidLevel.roll - pidLevel.yaw;
    m[2] = rc.throttle - pidRate.pitch - pidLevel.roll + pidLevel.yaw;
    m[3] = rc.throttle - pidRate.pitch + pidLevel.roll - pidLevel.yaw;

    #if ALTHOLD == 1
      m[0] += altVal;
      m[1] += altVal;
      m[2] += altVal;
      m[3] += altVal;
    #endif
    
  #endif
  
  #ifdef HEXA
  
    int m[6];
             
      m[0] = rc.throttle + (pidLevel.pitch * 0.87) +  (pidLevel.roll * 0.50) - pidLevel.yaw; // CCW
      m[1] = rc.throttle + (pidLevel.pitch * 0.87) -  (pidLevel.roll * 0.50) + pidLevel.yaw; // CW
      m[2] = rc.throttle -                            (pidLevel.roll)        - pidLevel.yaw; // CCW
      m[3] = rc.throttle - (pidLevel.pitch * 0.87) -  (pidLevel.roll * 0.50) + pidLevel.yaw; // CW
      m[4] = rc.throttle - (pidLevel.pitch * 0.87) +  (pidLevel.roll * 0.50) - pidLevel.yaw; // CCW
      m[5] = rc.throttle +                            (pidLevel.roll)        + pidLevel.yaw; // CW

   
    #if ALTHOLD == 1

      m[0] += altVal;
      m[1] += altVal;
      m[2] += altVal;
      m[3] += altVal;
      m[4] += altVal;
      m[5] += altVal; 

    #endif
    
  #endif

  motors.setSpeed(m);

  if (micros() - time1 > 50000) {
      Serial.print(angles.yaw);
      Serial.print(";");
      Serial.print(pidLevel.pitch);
      Serial.print(";");
      Serial.print(pidLevel.roll);
      Serial.println(";");
     time1 = micros();
  }

}

rcData Headless(rcData rc) {

  rcData rcHeadless = rc;

  // Formula Headless
  // Para el calculo headless debemos calular la influencia de ambos angulos pitch y roll 
  // multiplicado por el cos de la diferencia entre el angulo yaw inicial y el angulo ya actual

  // Para el calculo del angulo pitch:
  rcHeadless.pitch = rc.pitch * ( cos ( ( ( initYaw - angles.yaw ) * PI ) / 180 ) ) + rc.roll * ( cos ( ( ( ( ( initYaw - angles.yaw ) ) ) * PI ) / 180 ) );

  // Para el calculo del angulo roll:
  rcHeadless.roll = rc.roll * ( cos ( ( ( initYaw - angles.yaw ) * PI ) / 180 ) ) + rc.pitch * ( cos ( ( ( ( ( initYaw - angles.yaw ) ) - 90 ) * PI ) / 180 ) );

  return rcHeadless;

}

void trimAcc() {

  if( (micros() < TIMETRIMACC) && quadStatus.getArming() ){                          
       
    offsetsData.accPitch += angles.pitch;
    offsetsData.accRoll += angles.roll;

    countAcc++;
               
  }
        
        
  if( countAcc >= 1000 && quadStatus.getArming() && (micros() > TIMETRIMACC) ){

    offsetsData.accPitch /= countAcc;
    offsetsData.accRoll /= countAcc;
                
    countAcc = 0;
//    Serial.print(offsetsData.accPitch);
//    Serial.print(";");
//    Serial.println(offsetsData.accRoll); 
    EscribirOffSets(offsetsData);

  }

}
