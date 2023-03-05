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
	/*
		* Settings: 
			Output: 1 
			
			Logging Frequency: 2 Hz
			Enable Logging: 1 
			Enable Fan Controller: 1
			

			Blink: 1 Hz
			Force on: 0 
			Enable Led: 1 
			

			0001 1110 0101 0000  


	*/ 
	uint16_t settingsMsg = 0x1B50; 
	settings.UpdateSettings(settingsMsg); 
	uint8_t settingsVal = settings.GetOutputSettings(0); 

	uint8_t Expected = 0xB5; 
	TEST_CHECK_(settingsVal == Expected, "Testing GetOutputSettings(0): Expected :%d, actual %d", Expected, settingsVal);


}


TEST_LIST = 
{
    {"DigitalIOController.Initialize();", test_digital_io_controller_initialize},
    {"DigitalIOController.TurnOn();", test_digital_io_controller_TurnOn},
    {"DigitalIOController.TurnOff();", test_digital_io_controller_TurnOff},
    {"SettingsHandler.UpdateSettings()", test_settings_handler_UpdateSettings},
    {0}
};