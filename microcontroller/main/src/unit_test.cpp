#include "header/acutest.h"
#include "header/digital_io_controller.hpp"
#include "header/settings.hpp"
#include "header/uart_handler.hpp"
#include <stdint.h>
#include <stdlib.h>


uint8_t ddrAddress  = 0x00; 
uint8_t portAddress = 0x00; 
uint8_t pinAddress  = 0x00; 

io_information io {.DDR = &ddrAddress, .PORT = &portAddress, .PIN = &pinAddress, .BIT = 0}; 
DigitalIOController controller(io); 

void test_digital_io_controller_initialize(void)
{
	TEST_CASE("Test");
	controller.Initialize(); 
	TEST_CHECK_(ddrAddress == 1,"Testing Initialize(): Expected %d, actual %d", 1, ddrAddress); 

}

void test_digital_io_controller_TurnOn(void)
{
	// TurnOn test
	controller.TurnOn(); 
	TEST_CHECK_(portAddress == 1,"Testing TurnOn(): Expected %d, actual %d", 1, portAddress); 
}

void test_digital_io_controller_TurnOff(void)
{
	controller.TurnOff(); 
	TEST_CHECK_(portAddress == 0,"Testing TurnOff(): Expected %d, actual %d", 0, portAddress); 
	
}

void test_settings_handler_UpdateSettings(void)
{

	SettingsHandler settings;
	
	uint16_t settingsMsg[4] = {0x1B50, 0x2E20, 0x4000, 0x8F70};
	uint8_t ExpectedLoggingFrequency[4] = {2, 3, 0, 3}; 
	uint8_t ExpectedEnableLogging[4] = {1, 1, 0, 1}; 
	uint8_t ExpectedEnableFanController[4] = {1, 0, 0, 1}; 
	uint8_t ExpectedBlinkFrequency[4] = {1, 0, 0, 1}; 
	uint8_t ExpectedForceOn[4] = {0, 1, 0, 1}; 
	uint8_t ExpectedEnableLed[4] = {1, 0, 0, 1}; 

	for(int i = 0; i < 4; i++)
	{
		settings.UpdateSettings(settingsMsg[i]); 
		
		TEST_CHECK_(settings.GetLoggingFrequency() == ExpectedLoggingFrequency[i], "Testing GetLoggingFrequency(%i): Expected : %d, actual %d", i, ExpectedLoggingFrequency[i], settings.GetLoggingFrequency());
		TEST_CHECK_(settings.GetLoggingStatus() == ExpectedEnableLogging[i], "Testing GetLoggingStatus(%i): Expected : %d, actual %d", i, ExpectedEnableLogging[i], settings.GetLoggingStatus());
		TEST_CHECK_(settings.GetFanController() == ExpectedEnableFanController[i], "Testing GetFanController(%i): Expected : %d, actual %d",i,  ExpectedEnableFanController[i], settings.GetFanController());
		TEST_CHECK_(settings.GetBlinkFrequency(i) == ExpectedBlinkFrequency[i], "Testing GetBlinkFrequency(%i): Expected : %d, actual %d",i,  ExpectedBlinkFrequency[i], settings.GetBlinkFrequency(i));
		TEST_CHECK_(settings.IsForced(i) == ExpectedForceOn[i], "Testing IsForced(%i): Expected : %d, actual %d",i,  ExpectedForceOn[i], settings.IsForced(i));
		TEST_CHECK_(settings.IsEnabled(i) == ExpectedEnableLed[i], "Testing IsEnabled(%i): Expected : %d, actual %d",i,  ExpectedEnableLed[i], settings.IsEnabled(i));
	}
	/*
		* Settings: 
			Output: 1 
				Logging Frequency: 2 Hz
				Enable Logging: 1 
				Enable Fan Controller: 1
				
				Blink: 1 Hz
				Force on: 0 
				Enable Led: 1 
				
				0001 1011 0101 0000  

			Output: 2 
				Logging Frequency: 3 Hz
				Enable Logging: 1 
				Enable Fan Controller: 0
				
				Blink: 0 Hz
				Force on: 1 
				Enable Led: 0 
			
			0010 1110 0010 0000  

			Output: 3
				Logging Frequency: 0 Hz
				Enable Logging: 0 
				Enable Fan Controller: 0

				Blink: 0 Hz
				Force on: 0 
				Enable Led: 0 
				
				0100 0000 0000 0000  

			Output: 4 
				Logging Frequency: 3 Hz
				Enable Logging: 1 
				Enable Fan Controller: 1
				
				Blink: 1 Hz
				Force on: 1 
				Enable Led: 1 
		
				1000 1111 0111 0000
				*/
	 
}

void test_uart_handler_ConvertFromHexToUint16(void)
{
	const uint8_t nTests = 5;
	char *msg[nTests] =  {"0x0000", "0x000F", "0x00F0", "0x0F00", "0xF000"};
	uint16_t expected[nTests] = {0, 15, 240, 3840, 61440};


	// char *msg[nTests] =  {"0xF000"};
	// uint16_t expected[nTests] = {61440};

	UartHandler handler; 

	for(int i = 0; i < nTests; i++)
	{
		uint16_t result = handler.ConvertFromHexToUint16(msg[i]);
		TEST_CHECK_(result == expected[i], "Testing ConvertFromHexToUint16(%s): Expected : %d, actual %d", msg[i],  expected[i], result);
	}
}

void test_uart_handler_GetMessageType(void)
{
	const uint8_t nTests = 8;
	uint16_t msg[nTests] =  {61440, 36864, 0, 40960, 4096, 8192, 16384, 32768};
	MessageType expected[nTests] = {UNKNOWN, REQUEST_MICROCONTROLLER_TEMPERATURE, CHANGE_OUTPUT, REQUEST_CABINET_TEMPERATURE, UPDATE_SETTINGS, UPDATE_SETTINGS, UPDATE_SETTINGS, UPDATE_SETTINGS};


	// char *msg[nTests] =  {"0xF000"};
	// uint16_t expected[nTests] = {61440};

	UartHandler handler; 

	for(int i = 0; i < nTests; i++)
	{
		MessageType result = handler.GetMessageType(msg[i]);
		TEST_CHECK_(result == expected[i], "Testing GetMessageType(%i): Expected : %d, actual %d", msg[i],  expected[i], result);
	}
}



TEST_LIST = 
{
    {"DigitalIOController.Initialize();", test_digital_io_controller_initialize},
    {"DigitalIOController.TurnOn();", test_digital_io_controller_TurnOn},
    {"DigitalIOController.TurnOff();", test_digital_io_controller_TurnOff},
    {"SettingsHandler.UpdateSettings();", test_settings_handler_UpdateSettings},
    {"UartHandler.ConvertFromHexToUint16(char hexString[MESSAGE_BUFFER]);" ,test_uart_handler_ConvertFromHexToUint16},
    {"UartHandler.GetMessageType();",test_uart_handler_GetMessageType},
    {0}
};
