#include "../header/digital_io_controller.hpp"
#include "../header/io_configuration.hpp"

DigitalIOController::DigitalIOController(io_information ioInfo)
{
	_ioInfo = ioInfo;
}

void DigitalIOController::Initialize(void)
{
	SET_BIT_AT_ADDRESS(_ioInfo.DDR, _ioInfo.BIT); 
	_isInitialized = 1; 
}

void DigitalIOController::TurnOn(void)
{
	SET_BIT_AT_ADDRESS(_ioInfo.PORT, _ioInfo.BIT);
	//digitalWrite(_ioPin, 1); 
}

void DigitalIOController::TurnOff(void)
{
	CLR_BIT_AT_ADDRESS(_ioInfo.PORT, _ioInfo.BIT); 
}

void DigitalIOController::Toggle(void)
{
	TOGGLE_BIT_AT_ADDRESS(_ioInfo.PORT, _ioInfo.BIT); 
}

uint8_t DigitalIOController::GetState(void)
{
	return GET_BIT_AT_ADDRESS(_ioInfo.PIN, _ioInfo.BIT);
}