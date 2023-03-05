#ifndef __uart_handler__
#define __uart_handler__
#include "settings.hpp"
#include <stdint.h>

#define BAUDRATE 9600

/*
	Message type: Hex 
	Last four bytes indicates the status of the relay 
	First four bytes indicates if settings should be updated
	Second byte indicates the global settings,
	Third byte is individual and depends on what setting is 
	being updated
	
	0000 0000 0000 0000 

*/

enum MessageType
{
	UNKNOWN,
	UPDATE_SETTINGS,
	CHANGE_OUTPUT,
	REQUEST_TEMPERATURE
};

enum MessageSequence
{
	IDLE,
	MESSAGE_TYPE,
	MESSAGE
};

class UartHandler
{
	public: 
		UartHandler(void);
		void Initialize(); 
		uint8_t MessageAvailable(void); 
		MessageType GetMessageType(uint8_t messageType); 
		uint8_t GetMessage(void); 
	private: 
		MessageType _messageType; 
		uint8_t _message; 


}; 


#endif