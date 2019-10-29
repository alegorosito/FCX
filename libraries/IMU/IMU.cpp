#include "IMU.h"
#include "RC.h"

void IMU::Init( int compass ) 
{
	Wire.begin();
    Wire.beginTransmission( MPU );
    Wire.write( P_ACTIVACION_MPU );
    Wire.write( 0 );
    Wire.endTransmission();

    Wire.beginTransmission( MPU );
    Wire.write( ACCEL_CONFIG );
    Wire.write( ACCEL_SENS  << 3 );
    Wire.endTransmission();
    
    Wire.beginTransmission( MPU );
    Wire.write( GYRO_CONFIG );
    Wire.write( GYRO_SENS  << 3 );
    Wire.endTransmission();

    _compass = compass;
}

rawAxis IMU::getRaw()
{
	rawAxis raw = rawAxis();
	
	Wire.beginTransmission( MPU );

	Wire.write( ACELEROMETRO );
	Wire.endTransmission( false );
	// Se leen registros. Cada valor ocupa 2 registros
	Wire.requestFrom( MPU,6,true );

	raw.acc[0] = Wire.read() << 8 | Wire.read(); 
	raw.acc[1] = Wire.read() << 8 | Wire.read();
	raw.acc[2] = Wire.read() << 8 | Wire.read();

	Wire.beginTransmission( MPU );

	Wire.write( GIROSCOPIO );
	Wire.endTransmission( false );
	
	// Se leen 6 registros. Cada valor ocupa 2 registros
	Wire.requestFrom( MPU,6,true );

    raw.giro[1] =  Wire.read() << 8 | Wire.read();
	raw.giro[0] =  Wire.read() << 8 | Wire.read();
	raw.giro[2] =  Wire.read() << 8 | Wire.read();

	return raw;
}

rawAxis IMU::Compute() 
{

	rawAxis computed;
	rawAxis raw = getRaw();	

	raw.acc[0] =  (	raw.acc[0] / ACCESC	);
	raw.acc[1] =  (	raw.acc[1] / ACCESC );
	raw.acc[2] =  (	raw.acc[2] / ACCESC );	

	computed.acc[0] = atan( ( raw.acc[0] ) / sqrt( pow( ( raw.acc[1] ),2 ) + pow( ( raw.acc[2] ),2 ) ) ) * RADAGRADOS;
	computed.acc[1] = atan( ( raw.acc[1] ) / sqrt( pow( ( raw.acc[0] ),2 ) + pow( ( raw.acc[2] ),2 ) ) ) * RADAGRADOS;

	computed.giro[0] = raw.giro[0] / GYESC;
	computed.giro[1] = raw.giro[1] / GYESC;
	computed.giro[2] = raw.giro[2] / GYESC;

	computed.giro[0] -= offsets.giroPitch;
	computed.giro[1] -= offsets.giroRoll;
	computed.giro[2] -= offsets.giroYaw;

	return computed;
}


axis IMU::ComplementaryFilter( float mag )
{
	/*
	 *
	 * Complementary Filter
	 *
	 *	
	 */

	rawAxis computed = Compute();

	unsigned long t = micros();
	t2 = t - t3;
	t3 = t;

	float dt = ( float ) ( t2 / MICROS );

	float z_sin = sin(  (  computed.giro[2] * dt  ) * (  PI/180  )  );

	float last_pitch = filtered.pitch;

	// Pitch
	filtered.pitch = ( FPA * ( filtered.pitch - computed.giro[0] * dt ) + FPB * computed.acc[0] ) - ( z_sin * filtered.roll ); 

	// Roll
	filtered.roll = ( FPA * ( filtered.roll + computed.giro[1] * dt ) + FPB * computed.acc[1] ) + ( z_sin * last_pitch ); 

	if (!init)
	{
		filtered.pitch = offsets.giroPitch;
		filtered.roll =	offsets.giroRoll;
		init = true;
	}

	if ( _compass == 0 ) {

		filtered.yaw += ( computed.giro[2] * dt );

	} else {

		filtered.yaw =  0.8 * ( filtered.yaw - computed.giro[2] * dt ) + 0.2 * ( mag );
	}

	filtered.yaw = RestrictYaw( filtered.yaw );

	return filtered;
}


float IMU::RestrictYaw( float yaw ) {

	if( yaw < -180 ) {

	    yaw = 180;

	} else if ( yaw > 180 ) {

		yaw = -180;
	}

	return yaw;
}

offsetsAxis IMU::CalibrateGyro() {
	
	Serial.println( "Calibrando Giro" );

	offsets.giroPitch = 0;
	offsets.giroRoll = 0;
	offsets.giroYaw = 0;

	while ( countGyro < GYROCOUNT ){
		
		rawAxis raw = getRaw();

		offsets.giroPitch += raw.giro[0];
		offsets.giroRoll += raw.giro[1];
		offsets.giroYaw += raw.giro[2];
		
		countGyro++;
	}

	if( countGyro >= GYROCOUNT ){

		offsets.giroPitch = ( offsets.giroPitch / countGyro ) / GYESC;;
		offsets.giroRoll = ( offsets.giroRoll / countGyro ) / GYESC;;
		offsets.giroYaw = ( offsets.giroYaw / countGyro ) / GYESC;;

		Serial.print( "Calibrado >> " );
		Serial.print( offsets.giroPitch );
		Serial.print( ";" );
		Serial.println( offsets.giroRoll );

		countGyro = 0;

	}

	return offsets;

}

offsetsAxis IMU::CalibrateAcc() {

	Serial.println( "Calibrando Accelerometro" );

	while ( countAcc < ACCCOUNT ){
		
		axis angles = ComplementaryFilter();

		offsets.accPitch += angles.pitch;
		offsets.accRoll += angles.roll;

		countAcc++;
	}

	if( countAcc >= ACCCOUNT ){

		offsets.accPitch /= ACCCOUNT;
		offsets.accRoll /= ACCCOUNT;

		Serial.print( "Calibrado  ACC >> " );
		Serial.print( offsets.accPitch );
		Serial.print( ";" );
		Serial.println( offsets.accRoll );

		countAcc = 0;
	}

	return offsets;
}

void IMU::SetOffsetData( offsetsAxis offset ) {
	offsets.accPitch = offset.accPitch;
	offsets.accRoll = offset.accRoll;
	offsets.giroPitch = offset.giroPitch;
	offsets.giroRoll = offset.giroRoll;
	offsets.giroYaw = offset.giroYaw;
}

offsetsAxis IMU::GetOffsetData() {
	return offsets;
}