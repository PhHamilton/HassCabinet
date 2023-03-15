#ifndef __output_handler__
#define __output_handler__
#include "io_controller_group.hpp"
#include "settings.hpp"

#include "io_configuration.hpp"

class OutputHandler
{
	public:
		OutputHandler(io_information relay0, io_information led0, io_information relay1, io_information led1, io_information relay2, io_information led2, io_information relay3, io_information led3);
		void Initialize(void);  
		void ChangeOutput(uint16_t message, SettingsHandler currentSettings);
		uint8_t GetStateOfAllOutputs(void);
		uint8_t GetStateOfOutput(uint8_t outputNumber);

	private:
		IOControllerGroup _output_0;
		IOControllerGroup _output_1;
		IOControllerGroup _output_2;
		IOControllerGroup _output_3;

		uint8_t _currentStatus;
		uint8_t _getCurrentState(uint8_t outputNumber); 
		uint8_t _changeOutput(uint16_t message); 
		uint8_t _toggleSelectedOutput(uint8_t outputNumber, SettingsHandler currentSettings);
};

#endif