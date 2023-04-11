#include "../header/temperature_sensor_controller.hpp"

#define SENSOR_BYTES 40 
#define INITIALIZATION_DELAY_IN_MS 18
#define HIGHT_BIT_THRESH 

TemperatureSensor::TemperatureSensor(io_information sensorPin)
{
	_sensorPinInfo = sensorPin; 
}

void TemperatureSensor::Initialize(void)
{
	// Set Sensor as an output: 
	SET_BIT_AT_ADDRESS(_sensorPinInfo.DDR, _sensorPinInfo.BIT);


	_isInitialized = 1; 
	_dataSent = 0; 
	_dataRetrieved = 0; 
}

double TemperatureSensor::ReadSensorData(void)
{
	#ifndef NO_ARDUINO_LIBS
		uint64_t measuredData = 0;
		// Initiate Communication
		//_sendStartSignal(); 
		//_waitForDHTResponse();

		pinMode(3, OUTPUT);
		digitalWrite(3, LOW);
		delay(18);
		digitalWrite(3, HIGH);
		delayMicroseconds(40);
		pinMode(3, INPUT);
		Serial.println(" ");

		while(digitalRead(3) == LOW){}
		while(digitalRead(3) == HIGH){}

		for(int i = 0; i < 40; i++)
		{
			while(digitalRead(3) == LOW){}
			unsigned long t = micros();

			while(digitalRead(3) == HIGH){}


			if((micros() - t) > 40)
			{
				measuredData |= 1 << (39-i); 
				Serial.print("1");
			}
			else
				Serial.print("0");

			if((i+1)%8 == 0)
				Serial.print(" ");



		}
		measuredData = 38656149543;
		Serial.println(" ");

		_temperature = ((measuredData >> 16) & 0xFF);
		_humidity = (measuredData >> 32);
	#endif
	return 0;
}

uint8_t TemperatureSensor::_sendStartSignal(void)
{
	/* DHT11 start sequence: 
		* MCU pulls the line low for atleast 18 ms 
		* MCU pulls upp voltage and wait for DHT response
	*/
	#ifndef NO_ARDUINO_LIBS
		pinMode(sensorPin, OUTPUT); 
		digitalWrite(sensorPin, LOW); 
		delay(18); 
		digitalWrite(sensorPin, HIGH); 
	#endif
	return 0; 
}

uint8_t TemperatureSensor::_waitForDHTResponse(void)
{
	/* DHT11 response sequence: 
		* MCU pulls the line low for 80 us
		* MCU pulls upp voltage for 80 us
	*/
	#ifndef NO_ARDUINO_LIBS
		pinMode(sensorPin, INPUT); 
		while(digitalRead(sensorPin) == HIGH); 
		while(digitalRead(sensorPin) == LOW); 
		while(digitalRead(sensorPin) == HIGH)
	#endif
	return 0; 
}

double TemperatureSensor::GetTemperature(void)
{	
	return _temperature; 
}

double TemperatureSensor::GetHumidity(void)
{
	return _humidity; 
}

double TemperatureSensor::GetRawData(void)
{
	return _rawSensorData;
}

uint64_t TemperatureSensor::_readSensorData(void)
{
	

	return 0; 
}

double TemperatureSensor::_extractMeasurements(void)
{
	_rawSensorData = _readSensorData(); 
	_humidity = (_rawSensorData & 0xFF0000) >> 16;
	_temperature = (_rawSensorData & 0xFF00) >> 8;
	_checksum = (_rawSensorData & 0xFF);
}