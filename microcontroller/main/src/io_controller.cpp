#include "../header/io_controller.hpp"
#include "../header/io_configuration.hpp"

IOController::IOController(io_information ioInfo)
{
	_ioInfo = ioInfo;
}

void IOController::Initialize(void)
{
	SET_BIT(_ioInfo.DDR, _ioInfo.BIT); 
	_isInitialized = 1; 
}

void IOController::TurnOn(void)
{
	SET_BIT(_ioInfo.PORT, _ioInfo.BIT);
	//digitalWrite(_ioPin, 1); 
}

void IOController::TurnOff(void)
{
	CLR_BIT(_ioInfo.PORT, _ioInfo.BIT); 
}

void IOController::Toggle(void)
{
	TOGGLE_BIT(_ioInfo.PORT, _ioInfo.BIT); 
}

uint8_t IOController::GetState(void)
{
	return GET_BIT(_ioInfo.PIN, _ioInfo.BIT);
}