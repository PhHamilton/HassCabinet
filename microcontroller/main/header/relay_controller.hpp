#ifndef __relay_controller__
#define __relay_controller__

#include "Arduino.h"

class RelayController
{
	public:	
		RelayController(uint8_t relayPin); 
		void Initialize(void);
		void TurnOn(void); 
		void TurnOff(void); 
		uint8_t GetState(void); 
	private: 
		uint8_t _relayPin; 
		uint8_t _isInitialized; 
};

#endif
