#ifndef __output_handler__
#define __output_handler__

#include "io_controller_group.hpp"
#include "settings.hpp"
#include "io_configuration.hpp"

#ifndef NO_ARDUINO_LIBS
	#include "Arduino.h"
#endif

#define RELAY_STATE_NOT_AVAILABLE 101
#define LED_STATE_NOT_AVAILABLE 101

class OutputHandler
{
	public:
		OutputHandler(io_information relay0, io_information led0, io_information relay1, io_information led1, io_information relay2, io_information led2, io_information relay3, io_information led3);
		void Initialize(void); 
		void ChangeOutput(uint16_t message, SettingsHandler currentSettings);
		uint8_t GetRelayStateOfAllOutputs(void);
		uint8_t GetRelayStateOfOutput(uint8_t outputNumber);
		uint8_t GetLedStateOfAllOutputs(void);
		uint8_t GetLedStateOfOutput(uint8_t outputNumber);
		IOControllerGroup * _getOutputObject(uint8_t outputNumber); 
		void UpdateLEDs(SettingsHandler currentSettings);

	private:
		IOControllerGroup _output_0;
		IOControllerGroup _output_1;
		IOControllerGroup _output_2;
		IOControllerGroup _output_3;

		uint8_t _getRelayCurrentState(uint8_t outputNumber);
		uint8_t _getLedCurrentState(uint8_t outputNumber); 
		uint8_t _changeOutput(uint16_t message); 
		
		uint8_t _toggleSelectedOutput(uint8_t outputNumber, SettingsHandler currentSettings);
		void _startupLEDSequence(void); 
};

#endif