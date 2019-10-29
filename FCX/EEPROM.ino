void EscribirPid(pidData PIDPitch, pidData PIDRoll, pidData PIDYaw){
	// Escritura de datos en EEPROM de PID
	eeprom_write_block((const void*)&PIDPitch, (void*)0,pidBytes);
	eeprom_write_block((const void*)&PIDRoll, (void*)pidBytes,pidBytes);
	eeprom_write_block((const void*)&PIDYaw, (void*)(2*pidBytes),pidBytes);
}

void EscribirOffSets(offsetsAxis offsetsData){
	// Escritura de datos en EEPROM de los angulos objetivo
	int pos = 3*pidBytes;
	eeprom_write_block((const void*)&offsetsData, (void*)pos, offsetsBytes);
}

// void EscribirMagOffSets(DeviationAxis offsetsMagData){
//    // Escritura de datos en EEPROM de los angulos objetivo
//    int pos = 3*pidBytes + offsetsBytes;
//    eeprom_write_block((const void*)&offsetsMagData, (void*)pos, magBytes);
// }

void LeerPID(pidData *pitch, pidData *roll, pidData *yaw){
	pidData p, r, y;
	eeprom_read_block((void*)&p, (void*)0,pidBytes);
	eeprom_read_block((void*)&r, (void*)pidBytes,pidBytes);
	eeprom_read_block((void*)&y, (void*)(2*pidBytes),pidBytes);
	*pitch = p;
	*roll = r;
	*yaw = y;
}

void LeerOffSets(offsetsAxis *offsetsData){
	offsetsAxis offSetsA;
	int pos = 3*pidBytes;
	eeprom_read_block((void*)&offSetsA, (void*)pos,offsetsBytes);
	*offsetsData = offSetsA;
}

//void LeerMagOffSets(DeviationAxis *offsetsData){
//	DeviationAxis offSetsMag;
//	int pos = 3*pidBytes + offsetsBytes;
//	eeprom_read_block((void*)&offSetsMag, (void*)pos, magBytes);
//	*offsetsData = offSetsMag;
//}
//




