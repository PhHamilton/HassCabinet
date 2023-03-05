#ifndef __uart_handler__
#define __uart_handler__
#include "settings.hpp"
#include <stdint.h>

/*
	Message type: Hex 
	Last four bytes indicates the status of the relay 
	First four bytes indicates if settings should be updated
	Second byte indicates the global settings,
	Third byte is individual and depends on what setting is 
	being updated
	
	0000 0000 0000 0000 

*/

class UartHandler
{
	public: 
		UartHandler(void);
		void Initialize(); 
		uint8_t NewMessageAvailable(void); 
		uint8_t GetMessage(void); 
	private: 


}; 


#endif