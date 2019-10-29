#ifndef RC_h
#define RC_h
#define LIBRARY_VERSION 1.0

#ifndef NCH
	#define NCH 6 // Number of channels
#endif

#define CMIN 990
#define CMAX 2010

#define CMINLIM 1000
#define CMAXLIM 1860

// Limites de angulos deseados Pitch, Roll
#define ESCALARX 10.000
#define AMAX (30.00 * ESCALARX) // Maximo deseado de inclinacion

// Frecuencia en Hz = 1000 milisegs sobre 
// la tiempo ejecucion (6.334 milisegs.)
#define FREC (1000.00 / 6.334)

// Esta escala permite mejorar la resolusion de la salida
// debido a que la funcion map genera unicamenta salidas en enteros, 
#define ESCALAYAW 100.000

// Velocidad Deseada angular maxima en grados de Yaw
#define YAWMAX 150.000
#define VDYMAX ((YAWMAX / FREC) * ESCALAYAW)

#define CANTPROM 6

struct channels { // each position in the array represent a channel in the radio
	int val[NCH];
	int ant[NCH];
	int temp[NCH];
};

struct rcData {
	float pitch;
	float roll;
	float yaw;
	int aux1;
	int aux2;
	int throttle;
};

class RC
{

	public:
		void Init(int numch);
		int getChannel(int numch);
		float pitch();
		float roll();
		float yaw();
		float aux1();
		float aux2();
		float throttle();
		rcData getRcData();
		void ResetYaw(float y);
		void ISR_Read();
		
	private:
	uint8_t prevCh[NCH];
	channels ch; // declare a structure of channels
	rcData rc;
	int armCount = 0, _failsafeLimit, _countPitch = 0, _countRoll = 0;
	bool arming;
	float _yaw, _pitch[CANTPROM], _roll[CANTPROM], _r = 0, _p = 0;
};


#endif