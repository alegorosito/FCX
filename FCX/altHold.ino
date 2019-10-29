//float altHold() {
//
//    if (micros() - time2 > time1) {
//      Alt = baro.GetAltitude(SEALEVELPRESSURE);
//     
//      Alt = promAlt(Alt);
//      time2 = micros();
//    }
//    
//    if (!quadStatus.getArming()) ground = Alt;
//   
//    return Alt;
//}
//
//float promAlt(float val) {
// float temp = 0;
// promBuff[promI] = val;
// 
// for (int i=0; i < PRESPROM; i++) {
//   temp += promBuff[i];
// }
// 
// if (promI < PRESPROM) {
//   promI++;
// } else {
//   promI = 0;
// }
// temp /= PRESPROM;
// 
// return temp;
// 
//}

