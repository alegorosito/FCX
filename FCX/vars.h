IMU imu;
Motors motors;
PID pitch, roll, yaw, altH;
RC radio;
Status quadStatus;
LED led;

// Definicion de estructuras
pidOut pidLevel, pidRate;
rcData rc;
axis angles;
rawAxis raw;

// Contadores
int armCount = 0, auxCount, countAcc = 0, error = 0;

pidData PIDPitch, PIDRoll, PIDYaw, PIDAltH;
int pidBytes = sizeof(pidData);

offsetsAxis offsetsData;
int offsetsBytes = sizeof(offsetsData);

// Compass config
//HMC5883L compass;

bool calMag = false;

//DeviationAxis Mag;
//int magBytes = sizeof(Mag);

// Definicion de funciones para EEPROM
void EscribirPid(pidData PIDPitch, pidData PIDRoll, pidData PIDYaw);
void LeerPID(pidData *pitch, pidData *roll, pidData *yaw);
void EscribirOffSets(offsetsAxis offsetsData);
void LeerOffSets(offsetsAxis *offsetsData);

//void EscribirMagOffSets(DeviationAxis Mag);
//void LeerMagOffSets(DeviationAxis *Mag);

float Alt, pressAlt, pressBase, ground, VectZ, setAlt, altVal = 0, pres, initYaw = 0;

rawAxis zAxis;

//float promBuff[32];
//int promI=0;

unsigned long time2 = micros(), time1 = 50000;

float RCSCALE = 5.0;

// GPS
boolean gpsMode = true;
