#include "../header/output_handler.hpp"


OutputHandler::OutputHandler(io_information relay0, io_information led0, io_information relay1, io_information led1, io_information relay2, io_information led2, io_information relay3, io_information led3)
							: _output_0(relay0, led0), _output_1(relay1, led1), _output_2(relay2, led2), _output_3(relay3, led3){}

void OutputHandler::Initialize(void)
{
	_output_0.Initialize();
	_output_1.Initialize();
	_output_2.Initialize();
	_output_3.Initialize();
}

void OutputHandler::ChangeOutput(uint16_t message, SettingsHandler currentSettings)
{
	uint8_t outputMessage = (uint8_t) message; // Last four bits are output status

	for(uint8_t i = 0; i < NUMBER_OF_OUTPUTS; i++)
	{
		uint8_t outputStatus = GET_BIT(outputMessage, i);
		uint8_t currentStatus = _getRelayCurrentState(i);

		if(outputStatus != currentStatus)		
			_toggleSelectedOutput(i, currentSettings);

		// Add failure if it does not manage to change state? 
	}	
}

uint8_t OutputHandler::_getRelayCurrentState(uint8_t outputNumber)
{
	// First 4 bits LED state, Second 4 bits RelayStates
	switch(outputNumber)
	{
	case 0: 
		return _output_0.GetRelayState();
	case 1: 
		return _output_1.GetRelayState();
	case 2:  
		return _output_2.GetRelayState();
	case 3: 
		return _output_3.GetRelayState();
	default: 
		// Error! 
		return RELAY_STATE_NOT_AVAILABLE; 
		break;
	}
}

uint8_t OutputHandler::GetRelayStateOfAllOutputs(void)
{
	uint8_t msg = 0x00; 
	for(uint8_t i = 0; i < NUMBER_OF_OUTPUTS; i++)
	{
		msg |= _getRelayCurrentState(i) << i;
	}
	return msg; 
}

uint8_t OutputHandler::GetRelayStateOfOutput(uint8_t outputNumber)
{
	return _getRelayCurrentState(outputNumber);  
}

uint8_t OutputHandler::_toggleSelectedOutput(uint8_t outputNumber, SettingsHandler currentSettings)
{
	
	switch(outputNumber)
	{
	case 0: 
		_output_0.ToggleRelay();
		currentSettings.IsEnabled(outputNumber) ? _output_0.ToggleLed() : _output_0.TurnOffLed();
		break;
	case 1: 
		_output_1.ToggleRelay();
		currentSettings.IsEnabled(outputNumber) ? _output_1.ToggleLed() : _output_1.TurnOffLed();
		break; 
	case 2: 
		_output_2.ToggleRelay();
		currentSettings.IsEnabled(outputNumber) ? _output_2.ToggleLed() : _output_2.TurnOffLed();
		break;
	case 3: 
		_output_3.ToggleRelay();
		currentSettings.IsEnabled(outputNumber) ? _output_3.ToggleLed() : _output_3.TurnOffLed();
		break; 
	default: 
		// Error! 
		break;
	}
	return 0; 
}

uint8_t OutputHandler::GetLedStateOfAllOutputs(void)
{
	uint8_t msg = 0x00; 
	for(uint8_t i = 0; i < NUMBER_OF_OUTPUTS; i++)
	{
		msg |= _getLedCurrentState(i) << i;
	}
	return msg; 
}

uint8_t OutputHandler::GetLedStateOfOutput(uint8_t outputNumber)
{
	return _getLedCurrentState(outputNumber);  
}

void OutputHandler::UpdateLEDs(SettingsHandler currentSettings)
{
	for(int i = 0; i < NUMBER_OF_OUTPUTS; i++)
	{
		IOControllerGroup *currentOutput = _getOutputObject(i);
		currentSettings.IsEnabled(i) == TRUE ? (currentOutput->GetRelayState() == ON ? currentOutput->TurnOnLed() : currentOutput->TurnOffLed()) : currentOutput->TurnOffLed();
	}
}

uint8_t OutputHandler::_getLedCurrentState(uint8_t outputNumber)
{
	// First 4 bits LED state, Second 4 bits RelayStates
	switch(outputNumber)
	{
	case 0: 
		return _output_0.GetLedState();
	case 1: 
		return _output_1.GetLedState();
	case 2:  
		return _output_2.GetLedState();
	case 3: 
		return _output_3.GetLedState();
	default: 
		return LED_STATE_NOT_AVAILABLE;
		// Error! 
		break;
	}
}

uint8_t OutputHandler::_changeOutput(uint16_t message)
{
	switch(message >> 12)
	{
		case 1:
			return 0;
		case 2: 
			return 1;
		case 4: 
			return 2; 
		case 8: 
			return 3;  

		default: 
			//Unknown state, do nothing.. 
			return -1;  
	}
}

IOControllerGroup * OutputHandler::_getOutputObject(uint8_t outputNumber)
{
	switch(outputNumber)
	{
		case 0: 
			return &_output_0;
		case 1: 
			return &_output_1;
		case 2: 
			return &_output_2;
		case 3: 
			return &_output_3;
		default:
			return &_output_0; 
	}
}