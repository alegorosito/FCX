#include "Status.h"

void Status::Init()
{

}

void Status::setArming(int arming)
{
	if (arming == ARMING_ARM_STATE) {
		Serial.println("Armado");
		_arming = ARMING_ARM_STATE;
	}
	if (arming == ARMING_DISARM_STATE) {
		Serial.println("Desarmado");
		_arming = ARMING_DISARM_STATE;
	}
}

bool Status::getArming()
{
	return _arming;	
}

void Status::setMode(int aux)
{
	if (aux < GESTURE_LIMIT_1) _mode = MODE_LEVEL;
	if (aux > GESTURE_LIMIT_1 && aux < GESTURE_LIMIT_2) _mode = MODE_LOITER;
	if (aux > GESTURE_LIMIT_2) _mode = MODE_HOLDPOS;
}

int Status::getMode()
{
	return _mode;
}