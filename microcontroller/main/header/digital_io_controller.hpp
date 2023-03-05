#ifndef __io_controller__
#define __io_controller__

#include <stdint.h>
//#include "Arduino.h"

typedef struct
{
	uint8_t *DDR;// = 0x24;
	uint8_t *PORT;// = 0x25; 
	uint8_t *PIN;// = 0x23; 
	uint8_t BIT;// = 0x05; 
}io_information;

class DigitalIOController
{
	public: 
		DigitalIOController(io_information ioInfo);
		void Initialize(void); 
		void TurnOn(void); 
		void TurnOff(void); 
		void Toggle(void); 
		uint8_t GetState(void); 
		uint8_t testval; 

	private: 
		io_information _ioInfo;
		uint8_t _isInitialized;
		uint8_t _state;  
};

#endif
