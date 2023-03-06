#ifndef __uart_handler__
#define __uart_handler__
#include "settings.hpp"
#include <stdint.h>

#define BAUDRATE 9600
#define MESSAGE_BUFFER 6 //Format: 0x0000
/*
	Message type: Hex 
	Last four bytes indicates the status of the relay 
	First four bytes indicates if settings should be updated
	Second byte indicates the global settings,
	Third byte is individual and depends on what setting is 
	being updated
	
	0000 0000 0000 0000 

*/

/*
	Message types: 
	0000 xxxx xxxx xxxx // Configure settings for all (no output specific)
	0001 xxxx xxxx xxxx // Configure settings for output 1
	1111 xxxx xxxx xxxx // 
*/

enum MessageType
{
	UNKNOWN,
	UPDATE_SETTINGS,
	CHANGE_OUTPUT,
	REQUEST_MICROCONTROLLER_TEMPERATURE,
	REQUEST_CABINET_TEMPERATURE
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
		MessageType GetMessageType(uint16_t messageType); 
		uint16_t GetMessage(void); 
		uint8_t SendMessage(uint16_t message); 
		uint16_t ConvertFromHexToUint16(char hexString[MESSAGE_BUFFER]);

	private: 
		uint8_t _message; 
		MessageType _messageType; 
		uint8_t convertFromBase16(char hexValue);
}; 


#endif