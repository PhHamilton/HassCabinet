#include "../header/uart_handler.hpp"
#include <math.h>
#include <string.h>

UartHandler::UartHandler(void){}

void UartHandler::Initialize(void)
{
	#ifndef NO_ARDUINO_LIBS
		Serial.begin(BAUDRATE);
	#endif
}

uint8_t UartHandler::MessageAvailable(void)
{
	#ifndef NO_ARDUINO_LIBS
		if(Serial.available() > 0)
			return TRUE; 
		else
			return FALSE;
	#endif

	return 0; 
}

uint16_t UartHandler::GetMessage(void) 
{
	char serialBuffer[MESSAGE_BUFFER];
	memset(serialBuffer, 0, MESSAGE_BUFFER);

	#ifndef NO_ARDUINO_LIBS
	Serial.readBytes(serialBuffer, MESSAGE_BUFFER);
	Serial.println(serialBuffer);
	#endif

	if(MessageIsValid(serialBuffer)) 
	{
		SendMessage("OK");
		return ConvertFromHexToUint16(serialBuffer);   
	}
	else
	{
		SendMessage("Unknown Message");
		return NOT_VALID;
	}
}

uint8_t UartHandler::SendMessage(const char *message)
{
	#ifndef NO_ARDUINO_LIBS
		Serial.println(message);
	#endif
	return 0;
}

uint8_t UartHandler::SendIntMessage(uint16_t message)
{
	#ifndef NO_ARDUINO_LIBS
		Serial.println(message);
	#endif
	return 0;
}

uint8_t UartHandler::MessageIsValid(const char message[MESSAGE_BUFFER])
{

	if(message[0] != '0') return NOT_VALID;
	if(message[1] != 'x') return NOT_VALID;
	for(int i = 2; i < 6; i++)
	{
		if(!_isValidHex(message[i])) return FALSE; 
	}


	return VALID; 
}

uint8_t UartHandler::_isValidHex(char character)
{
	int charAsInt = character - '0';

	for(int i = 0; i < 10; i++)
		if(charAsInt == i) return TRUE;

	if(charAsInt >= 17 && charAsInt <= 22) return TRUE;


	return FALSE;
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
	case 7: 
	case 11:
	case 13: 
	case 14:
		return REQUEST_OUTPUT_SETTINGS; 

	case 15: 
		return REQUEST_OUTPUT_STATE;

	default: 
		return UNKNOWN;
	}

	return _messageType;
}
 
uint16_t UartHandler::ConvertFromHexToUint16(const char hexString[MESSAGE_BUFFER])
{
	uint16_t val = 0;
	for(int i = 2; i < MESSAGE_BUFFER; i++)
	{
			uint8_t multiplier = convertFromBase16(hexString[i]); 
			double exponent = pow(16, MESSAGE_BUFFER -1 - i );
  		val += convertFromBase16(hexString[i]) * doubleToUint16(pow(16, MESSAGE_BUFFER-1-i));
	}
	return val; 
}

uint16_t UartHandler::doubleToUint16(double dValue)
{
	return (uint16_t)(dValue + 0.5); 
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

