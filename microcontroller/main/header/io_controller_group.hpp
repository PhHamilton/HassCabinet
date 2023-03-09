#ifndef __io_controller_group__
#define __io_controller_group__

#include "digital_io_controller.hpp"

class IOControllerGroup
{
	public: 
		IOControllerGroup(io_information relayInformation, io_information ledInformation);
		void Initialize(void); 
		void ToggleRelay(void);
		void ToggleLed(void); 
		void TurnOnLed(void); 
		void TurnOffLed(void);
		uint8_t GetState(void); 

	private: 
		DigitalIOController _relayOutput; 
		DigitalIOController _ledOutput; 
}; 

#endif