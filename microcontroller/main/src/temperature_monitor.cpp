#include "../header/temperature_monitor.hpp"

#define MILLISECONDS_TO_SECONDS    1000

TemperatureController::TemperatureController(void)
{

}

uint8_t TemperatureController::IsAboveLimits(temperature_struct temperature)
{
    return temperature.CabinetTemperature > MAXIMUM_CABINET_TEMPERATURE; 
}

uint8_t TemperatureController::TimeToMeasure()
{
    #ifndef NO_ARDUINO_LIBS
        _currentMillis = millis(); 
    #endif

    if(_currentMillis - _previousMillis > _convertFrequencyToCorrectTimeFormat(MEASUREMENT_FREQUENCY))
    {
        _previousMillis = _currentMillis; 
        return true;
    }
    return false; 
}

uint16_t TemperatureController::_convertFrequencyToCorrectTimeFormat(float frequencyInSeconds)
{
    return MILLISECONDS_TO_SECONDS / frequencyInSeconds;
}
