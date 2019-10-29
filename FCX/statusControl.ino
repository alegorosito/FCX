void statusControl() 
{  
  // rc = radio.getRcData();
  
  if (radio.getChannel(1) < GESTURE_LIMIT_1 && radio.getChannel(4) > GESTURE_LIMIT_2 && !quadStatus.getArming()) {

    armCount++;
 
  } else {
     
      if (radio.getChannel(1) < ARMPWM && quadStatus.getArming()) {
        
        armCount++;      
        
      } else {
        
        armCount = 0;
        
      } 
      
  }
  
  if(armCount >= ARMCOUNT) {
    
    armCount = 0;
    
    quadStatus.setArming(!quadStatus.getArming());

    initYaw = angles.yaw;
    
    radio.ResetYaw(initYaw);
    
    if (quadStatus.getArming()) led.config(1, 13);
    else {
      led.config(500, 13);
    }
    
  }

  // Activa la calibracion del Magnetometro  
    if (rc.throttle < GESTURE_LIMIT_1 && !quadStatus.getArming()) {
   
      RCSCALE = map(rc.aux1, 990, 2010, 1, 100) / 10.0;
//    RCSCALE = LEVELSCALE * 0.75;

//    Serial.println(LEVEL_P);
    
//    Serial.println(PIDPitch.p,5);
//    pitch.SetTunings(PIDPitch.p, PIDPitch.i, PIDPitch.d);
//    roll.SetTunings(PIDPitch.p, PIDPitch.i, PIDPitch.d);    
  
    yaw.Reset();
    pitch.Reset();
    roll.Reset();  
            
  }
   
  if (radio.getChannel(1) > GESTURE_LIMIT_2 && radio.getChannel(2) > GESTURE_LIMIT_2 && radio.getChannel(3) > GESTURE_LIMIT_2 && radio.getChannel(4) < GESTURE_LIMIT_1) 
  {
      EscribirOffSets(imu.CalibrateAcc());
      LeerOffSets(&offsetsData);
  }
  
}


