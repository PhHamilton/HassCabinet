#include "../header/temperature_sensor_controller.hpp"
/*
TemperatureSensor::TemperatureSensor(uint8_t temperatureSensorPin)
{
	_temperatureSensorPin = temperatureSensorPin; 
}

void TemperatureSensor::Initialize(void)
{
	pinMode(_temperatureSensorPin, INPUT); 
	_isInitialized = 1; 
	_dataSent = 0; 
	_dataRetrieved = 0; 
}

double TemperatureSensor::GetTemperature(void)
{
	return 0; 
}

double TemperatureSensor::GetHumidity(void)
{
	return 0; 
}

uint64_t _readSensorData(void)
{
	uint64_t tempData = 0; 
	pinMode(_temperatureSensorPin, OUTPUT); 
	digitalWrite(_temperatureSensorPin, 0); 
	delay(20); // Start signal 
	digitalWrite(_temperatureSensorPin, 1); 
	pinMode(_temperatureSensorPin, INPUT); 

	while(digitalRead(_temperatureSensorPin) == 1);

	for(int i = 0; i < 40; i++)
	{
		uint32_t pulse = pulseIn(_temperatureSensorPin, 1); 
		if(pulse > 50)
			tempData |= (1 << (39 - i));
	}

	//_dataRetrieved = 1; 

	return tempData; 
	return 0; 
}

double TemperatureSensor::_extractMeasurements(void)
{
	_rawSensorData = _readSensorData(); 
	//_humidity = (_rawSensorData & FF0000) >> 16;
	//_temperature = (_rawSensorData & FF00) >> 8;
	//_checksum = (_rawSensorData & FF);
}
*/
