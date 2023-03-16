#include "../header/io_controller_group.hpp"

IOControllerGroup::IOControllerGroup(io_information relayInformation, io_information ledInformation) : _relayOutput(relayInformation), _ledOutput(ledInformation){}

void IOControllerGroup::Initialize(void)
{
	_relayOutput.Initialize(); 
	_ledOutput.Initialize();
}

void IOControllerGroup::ToggleRelay(void)
{
	_relayOutput.Toggle(); 
}

uint8_t IOControllerGroup::GetRelayState(void)
{
	return _relayOutput.GetState();
}

uint8_t IOControllerGroup::GetLedState(void)
{
	return _ledOutput.GetState();
}

void IOControllerGroup::ToggleLed(void)
{
	_ledOutput.Toggle();
}

void IOControllerGroup::TurnOnLed(void)
{
	_ledOutput.TurnOn();
}

void IOControllerGroup::TurnOffLed(void)
{
	_ledOutput.TurnOff();
}