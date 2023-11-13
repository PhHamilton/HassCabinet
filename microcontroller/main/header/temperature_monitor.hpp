#ifndef TEMPERATURE_MONITOR_H
#define TEMPERATURE_MONITOR_H

#include "temperature_sensor_controller.hpp"

#define MAXIMUM_CABINET_TEMPERATURE     30
#define MAXIMUM_CONTROLLER_TEMPERATURE  50
#define MAXIMUM_ON_TIME_IN_MINUTES      10
#define MEASUREMENT_FREQUENCY           0.1

typedef struct
{
    uint8_t CabinetTemperature; 
    uint8_t ArduinoTemperature; 
    uint8_t RaspberryPiTemperature; 
}temperature_struct;


class TemperatureController
{
    public:
        TemperatureController(void);
        uint8_t IsAboveLimits(temperature_struct temperatures);
        uint8_t TimeToMeasure();
    private: 
        uint64_t _previousMillis = 0; 
        uint64_t _currentMillis; 
        uint16_t _convertFrequencyToCorrectTimeFormat(float frequencyInSeconds);
};

#endif