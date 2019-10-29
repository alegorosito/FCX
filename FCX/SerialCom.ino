void SerialCom(String e) {
    //Serial.println(e);
    if (e.substring(0,4) == String("PID;")) {
      float PID[9];
      int index1 = 0, index2 = 0; // PID;100;50;20;800;30;20;
      for (int i = 0; i < 7; i++) {
        index1 = e.indexOf(';', index1);
        index2 = e.indexOf(';', index1 + 1);
        PID[i] = (e.substring(index1 + 1,index2).toInt()) / SCALEPID;
        // Serial.println(PID[i],5);
        index1 = index2;
      }
      
            
      PIDPitch.p = PID[0];
      PIDPitch.i = PID[1];
      PIDPitch.d = PID[2];

      PIDRoll.p = PID[0];
      PIDRoll.i = PID[1];
      PIDRoll.d = PID[2];
      
      PIDYaw.p = PID[3];
      PIDYaw.i = PID[4];
      PIDYaw.d = PID[5];
      
      EscribirPid(PIDPitch, PIDRoll, PIDYaw);
      LeerPID(&PIDPitch, &PIDRoll, &PIDYaw);

      pitch.SetTunings(PIDPitch.p, PIDPitch.i, PIDPitch.d);
      roll.SetTunings(PIDRoll.p, PIDRoll.i, PIDRoll.d);
      
      yaw.SetTunings(PIDYaw.p, PIDYaw.i, PIDYaw.d);
 
      SerialSend();
  }
 
  if (e.substring(0,5) == String("cntd;")) { 
      SerialSend();
  }


}

void SerialSend() {
  Serial.flush();
  delayMicroseconds(1000);
  
  Serial.println("PIDS;" + String((int) (PIDPitch.p * 1000)) + ";" + String((int) (PIDPitch.i * 1000)) + ";" + String((int) (PIDPitch.d * 1000)) + ";" + String((int) (PIDYaw.p * 1000)) + ";" + String((int) (PIDYaw.i * 1000)) + ";" + String((int) (PIDYaw.d * 1000)) + ";");
}
