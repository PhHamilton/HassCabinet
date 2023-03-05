#include "header/acutest.h"
#include "header/digital_io_controller.hpp"
#include "header/settings.hpp"
#include <stdint.h>


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


TEST_LIST = 
{
    {"DigitalIOController.Initialize();", test_digital_io_controller_initialize},
    {"DigitalIOController.TurnOn();", test_digital_io_controller_TurnOn},
    {"DigitalIOController.TurnOff();", test_digital_io_controller_TurnOff},
    {"SettingsHandler.UpdateSettings()", test_settings_handler_UpdateSettings},
    {0}
};