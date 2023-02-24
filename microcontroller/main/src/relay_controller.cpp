#include "../header/relay_controller.hpp"


RelayController::RelayController(uint8_t relayPin)
{
	_relayPin = relayPin; 
}

void RelayController::Initialize(void)
{
	pinMode(_relayPin, OUTPUT); 
	_isInitialized = 1; 
}

void RelayController::TurnOn(void)
{
	digitalWrite(_relayPin, 1); 
}

void RelayController::TurnOff(void)
{
	digitalWrite(_relayPin, 0); 
}

uint8_t RelayController::GetState(void)
{
	return digitalRead(_relayPin); 
}