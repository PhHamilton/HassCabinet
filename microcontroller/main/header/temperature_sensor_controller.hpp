#ifndef __temperature_sensor_controller__
#define __temperature_sensor_controller__

#ifndef NO_ARDUINO_LIBS
	#include "Arduino.h"
#endif
#include "digital_io_controller.hpp"
#include "io_configuration.hpp"
#include <stdint.h>

class TemperatureSensor
{
	
	public:
		TemperatureSensor(io_information sensorPin); 
		void Initialize(void); 
		double ReadSensorData(void);
		uint16_t GetTemperature(void); 
		uint16_t GetHumidity(void); 
		uint16_t GetRawData(void); 
	private: 
		io_information _sensorPinInfo; 	
		uint8_t _isInitialized; 
		uint8_t sensorPin = 3; 
		uint8_t _dataSent; 
		uint8_t _dataRetrieved; 
		uint64_t _rawSensorData; 
		uint64_t _readSensorData(void); 
		double _convert16BitToDouble(void); 
		double _extractMeasurements(void); 
		double _getHumidity(void); 
		double _checkMessageValidity(void);
		uint16_t _temperature;
		uint16_t _humidity;
		uint16_t _checksum; 

		uint8_t _sendStartSignal(void); 
		uint8_t _waitForDHTResponse(void);

		
};


#endif
