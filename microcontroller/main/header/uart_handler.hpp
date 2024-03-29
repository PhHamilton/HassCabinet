#ifndef __uart_handler__
#define __uart_handler__
#include <stdint.h>

#ifndef NO_ARDUINO_LIBS
#include <Arduino.h>
#endif

#define BAUDRATE 9600
#define MESSAGE_BUFFER 6 //Format: 0x0000
#define TRUE 1
#define FALSE 0
#define VALID 1
#define NOT_VALID 0 
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
	REQUEST_CABINET_TEMPERATURE,
	REQUEST_CABINET_HUMIDITY,
	REQUEST_OUTPUT_SETTINGS,
	REQUEST_OUTPUT_STATE,
	REQUEST_FAN_SPEED
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
		uint8_t MessageIsValid(const char message[MESSAGE_BUFFER]); 
		MessageType GetMessageType(uint16_t messageType); 
		uint16_t GetMessage(void); 
		uint8_t SendMessage(const char *message); 
		uint8_t SendIntMessage(uint16_t message); 
		uint8_t SendLargeIntMessage(uint32_t message); 
		uint16_t ConvertFromHexToUint16(const char hexString[MESSAGE_BUFFER]);

	private: 
		uint8_t _message; 
		MessageType _messageType; 
		uint8_t convertFromBase16(char hexValue);
		uint8_t _isValidHex(char character);
		uint16_t doubleToUint16(double dValue);
}; 


#endif