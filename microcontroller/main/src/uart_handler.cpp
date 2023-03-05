#include "../header/uart_handler.hpp"

UartHandler::UartHandler(void){}

void UartHandler::Initialize(void)
{
	// Serial.begin(BAUDRATE)
}

uint8_t UartHandler::MessageAvailable(void)
{
	//return (Serial.Available > 0);
	return 0; 
}

MessageType UartHandler::GetMessageType(uint8_t messageType)
{
	switch(messageType)
	{
	case 1: 
		return UPDATE_SETTINGS; 
	case 2:
		return CHANGE_OUTPUT;
	case 3: 
		return REQUEST_TEMPERATURE; 
	default: 
		return UNKNOWN;
	}

	return _messageType;
}
 


