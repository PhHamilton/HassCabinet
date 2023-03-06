#include "../header/uart_handler.hpp"
#include <math.h>
#include <string.h>

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

uint16_t UartHandler::GetMessage(void) 
{
	char serialBuffer[MESSAGE_BUFFER];
	memset(serialBuffer, 0, MESSAGE_BUFFER);
	// Serial.readBytes(serialBuffer, BUFFER_SIZE);
	return ConvertFromHexToUint16(serialBuffer); 
}

MessageType UartHandler::GetMessageType(uint16_t messageType)
{
	switch(messageType >> 12)
	{
	case 0: 
		return CHANGE_OUTPUT;
	case 1: 
	case 2:
	case 4:
	case 8: 
		return UPDATE_SETTINGS; 
	case 9: 
		return REQUEST_MICROCONTROLLER_TEMPERATURE; 
	case 10: 
		return REQUEST_CABINET_TEMPERATURE;
	default: 
		return UNKNOWN;
	}

	return _messageType;
}
 
uint16_t UartHandler::ConvertFromHexToUint16(char hexString[MESSAGE_BUFFER])
{
	uint16_t val = 0;
	for(int i = 2; i < MESSAGE_BUFFER; i++)
	{
  		val += convertFromBase16(hexString[i]) * (uint16_t)pow(16,MESSAGE_BUFFER-1-i);
	}
	return val; 
}

uint8_t UartHandler::convertFromBase16(char hexValue)
{
  switch(hexValue)
  {
    case 'A':
      return 10;
      break;
    case 'B':
      return 11;
      break;      
    case 'C':
      return 12;
      break;
    case 'D':
      return 13;
      break;
    case 'E':
      return 14;
      break;
    case 'F':
      return 15;
      break;

    default:
      return hexValue - '0'; 
  }
}

