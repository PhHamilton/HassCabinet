/*#include "header/acutest.h"
#include "header/digital_io_controller.hpp"
#include "header/settings.hpp"
#include "header/uart_handler.hpp"
#include "header/output_handler.hpp"
#include "header/temperature_monitor.hpp"
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

	for(int i = 0; i < NUMBER_OF_OUTPUTS; i++)
	{
		settings.UpdateSettings(settingsMsg[i]); 
		
		TEST_CHECK_(settings.GetLoggingFrequency() == ExpectedLoggingFrequency[i], "Testing GetLoggingFrequency(%i): Expected : %d, actual %d", i, ExpectedLoggingFrequency[i], settings.GetLoggingFrequency());
		TEST_CHECK_(settings.GetLoggingStatus() == ExpectedEnableLogging[i], "Testing GetLoggingStatus(%i): Expected : %d, actual %d", i, ExpectedEnableLogging[i], settings.GetLoggingStatus());
		TEST_CHECK_(settings.GetFanController() == ExpectedEnableFanController[i], "Testing GetFanController(%i): Expected : %d, actual %d",i,  ExpectedEnableFanController[i], settings.GetFanController());
		TEST_CHECK_(settings.GetBlinkFrequency(i) == ExpectedBlinkFrequency[i], "Testing GetBlinkFrequency(%i): Expected : %d, actual %d",i,  ExpectedBlinkFrequency[i], settings.GetBlinkFrequency(i));
		TEST_CHECK_(settings.IsForced(i) == ExpectedForceOn[i], "Testing IsForced(%i): Expected : %d, actual %d",i,  ExpectedForceOn[i], settings.IsForced(i));
		TEST_CHECK_(settings.IsEnabled(i) == ExpectedEnableLed[i], "Testing IsEnabled(%i): Expected : %d, actual %d",i,  ExpectedEnableLed[i], settings.IsEnabled(i));
	}			
	 
}

void test_settings_handler_DefaultSettings(void)
{
	SettingsHandler settings;

	uint8_t ExpectedLoggingFrequency = 0;
	uint8_t ExpectedEnableLogging = 0;
	uint8_t ExpectedEnableFanController = 0;
	uint8_t ExpectedBlinkFrequency = 0;
	uint8_t ExpectedForceOn = 0;
	uint8_t ExpectedEnableLed = 1;

	settings.LoadDefaultSettings();

	for(int i = 0; i < NUMBER_OF_OUTPUTS; i++)
	{ 	
		TEST_CHECK_(settings.GetLoggingFrequency() == ExpectedLoggingFrequency, "Testing GetLoggingFrequency(%i): Expected : %d, actual %d", i, ExpectedLoggingFrequency, settings.GetLoggingFrequency());
		TEST_CHECK_(settings.GetLoggingStatus() == ExpectedEnableLogging, "Testing GetLoggingStatus(%i): Expected : %d, actual %d", i, ExpectedEnableLogging, settings.GetLoggingStatus());
		TEST_CHECK_(settings.GetFanController() == ExpectedEnableFanController, "Testing GetFanController(%i): Expected : %d, actual %d",i,  ExpectedEnableFanController, settings.GetFanController());
		TEST_CHECK_(settings.GetBlinkFrequency(i) == ExpectedBlinkFrequency, "Testing GetBlinkFrequency(%i): Expected : %d, actual %d",i,  ExpectedBlinkFrequency, settings.GetBlinkFrequency(i));
		TEST_CHECK_(settings.IsForced(i) == ExpectedForceOn, "Testing IsForced(%i): Expected : %d, actual %d",i,  ExpectedForceOn, settings.IsForced(i));
		TEST_CHECK_(settings.IsEnabled(i) == ExpectedEnableLed, "Testing IsEnabled(%i): Expected : %d, actual %d",i,  ExpectedEnableLed, settings.IsEnabled(i));
	}	

}

void test_settings_get_output_settings(void)
{
	SettingsHandler settings;

	uint16_t settingsMsg[4] = {0x1B50, 0x2E20, 0x4000, 0x8F70};
	uint8_t expected[4] = {0xB5, 0xE2,0x00, 0xF7};

	for(int i = 0; i < NUMBER_OF_OUTPUTS; i++)
	{
		settings.UpdateSettings(settingsMsg[i]); 
		TEST_CHECK_(settings.GetOutputSettings(i) == expected[i], "Testing GetOutputSettings(%i): Expected: %d, actual: %d", i, expected[i], settings.GetOutputSettings(i));
	}


}

void test_uart_handler_ConvertFromHexToUint16(void)
{
	const uint8_t nTests = 8;
	const char *msg[nTests] =  {"0x0000", "0x000F", "0x00F0", "0x0F00", "0xF000", "0x1000", "0x0010", "0x0040"};
	uint16_t expected[nTests] = {0, 15, 240, 3840, 61440, 4096, 16, 64};


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
	const uint8_t nTests = 12;
	uint16_t msg[nTests] =  {61440, 36864, 0, 40960, 4096, 8192, 16384, 32768, 57344, 53248, 45056, 28672};
	MessageType expected[nTests] = {REQUEST_OUTPUT_STATE, REQUEST_MICROCONTROLLER_TEMPERATURE, CHANGE_OUTPUT, REQUEST_CABINET_TEMPERATURE, UPDATE_SETTINGS, UPDATE_SETTINGS, UPDATE_SETTINGS, UPDATE_SETTINGS, REQUEST_OUTPUT_SETTINGS, REQUEST_OUTPUT_SETTINGS, REQUEST_OUTPUT_SETTINGS, REQUEST_OUTPUT_SETTINGS};

 
	// char *msg[nTests] =  {"0xF000"};
	// uint16_t expected[nTests] = {61440};

	UartHandler handler; 

	for(int i = 0; i < nTests; i++)
	{
		MessageType result = handler.GetMessageType(msg[i]);
		TEST_CHECK_(result == expected[i], "Testing GetMessageType(%i): Expected : %d, actual %d", msg[i],  expected[i], result);
	}
}

void test_uart_handler_MessageIsValid(void)
{
	uint8_t nTests = 7;
	const char *msg[] =  {"0x0000", "0x", "00000", "0xTT0x", "", "0xFF02", "0xFAEC"};
	uint8_t expected[] = {VALID, NOT_VALID, NOT_VALID, NOT_VALID, NOT_VALID, VALID, VALID};


	// char *msg[nTests] =  {"0xF000"};
	// uint16_t expected[nTests] = {61440};
 
	UartHandler handler; 

	for(int i = 0; i < nTests; i++)
	{
		uint8_t result = handler.MessageIsValid(msg[i]);
		TEST_CHECK_(result == expected[i], "Testing GetMessageType(%s): Expected : %d, actual %d", msg[i],  expected[i], result);
	}
}

void test_uart_get_message(void)
{
	
	const uint8_t nTests = 3; 
	const char *msg[] = {"0x1000", "0x2000", "0x9000"};
	uint16_t expected[] = {4096, 8192, 36864};

	UartHandler handler;

	for(int i = 0; i < nTests; i++)
	{
		//uint8_t result = handler.GetMessage(msg[i]);
		//TEST_CHECK_(result == expected[i], "Testing GetMessage(%s): Expected : %d, actual %d", msg[i],  expected[i], result);
	}
}

void test_output_handler_ChangeOutput(void)
{

	const uint8_t nTests = 7;
	uint16_t msg[nTests] =  {0x0001, 0x0002, 0x0004, 0x0008, 0x000D, 0x0005, 0x0000};
	uint8_t expected[nTests] = {0x1, 0x2, 0x4, 0x8, 0xD, 0x5, 0x0};

	SettingsHandler settings; 
	settings.LoadDefaultSettings(); 

	uint8_t io_0_addr  = 0x00; 
	uint8_t led_0_addr = 0x00;
	uint8_t io_1_addr  = 0x00;
	uint8_t led_1_addr = 0x00;
	uint8_t io_2_addr  = 0x00;
	uint8_t led_2_addr = 0x00;
	uint8_t io_3_addr  = 0x00;
	uint8_t led_3_addr = 0x00;

	io_information io_0 {.DDR = &io_0_addr, .PORT = &io_0_addr, .PIN = &io_0_addr, .BIT = 0}; 
	io_information led_0 {.DDR = &led_0_addr, .PORT = &led_0_addr, .PIN = &led_0_addr, .BIT = 0}; 
	io_information io_1 {.DDR = &io_1_addr, .PORT = &io_1_addr, .PIN = &io_1_addr, .BIT = 0}; 
	io_information led_1 {.DDR = &led_1_addr, .PORT = &led_1_addr, .PIN = &led_1_addr, .BIT = 0};
	io_information io_2 {.DDR = &io_2_addr, .PORT = &io_2_addr, .PIN = &io_2_addr, .BIT = 0}; 
	io_information led_2 {.DDR = &led_2_addr, .PORT = &led_2_addr, .PIN = &led_2_addr, .BIT = 0};
	io_information io_3 {.DDR = &io_3_addr, .PORT = &io_3_addr, .PIN = &io_3_addr, .BIT = 0}; 
	io_information led_3 {.DDR = &led_3_addr, .PORT = &led_3_addr, .PIN = &led_3_addr, .BIT = 0};

	OutputHandler outputHandler(io_0, led_0, io_1, led_1, io_2, led_2, io_3, led_3);


	for(int i = 0; i < nTests; i++)
	{
		outputHandler.ChangeOutput(msg[i], settings);

		uint8_t result = outputHandler.GetRelayStateOfAllOutputs();
		uint8_t ledResult = outputHandler.GetLedStateOfAllOutputs();
		TEST_CHECK_(result == expected[i], "Testing ChangeOutput(%d, settings): Expected : %d, actual %d", msg[i],  expected[i], result);
		TEST_CHECK_(ledResult == expected[i], "Testing ChangeOutput(%d, settings): Expected : %d, actual %d", msg[i],  expected[i], result);
		TEST_MSG("Message: %d, Values: %d, %d, %d, %d", msg[i], outputHandler.GetRelayStateOfOutput(0), outputHandler.GetRelayStateOfOutput(1), outputHandler.GetRelayStateOfOutput(2), outputHandler.GetRelayStateOfOutput(3));
	}

	// Disable led on pin zero
	settings.UpdateSettings(0x1000);
	outputHandler.ChangeOutput(0x0003, settings); 
	TEST_CHECK_(outputHandler.GetLedStateOfOutput(0) == 0, "Testing ChangeOutput(%d, settings): Expected : %d, actual %d", 0x00000,  0x0001, outputHandler.GetLedStateOfOutput(0));
	TEST_CHECK_(outputHandler.GetLedStateOfOutput(1) == 1, "Testing ChangeOutput(%d, settings): Expected : %d, actual %d", 0x00001,  0x0001, outputHandler.GetLedStateOfOutput(1));

	// Disable led three without changing the output
	settings.UpdateSettings(0x2000);
	outputHandler.UpdateLEDs(settings);
	TEST_CHECK_(outputHandler.GetLedStateOfOutput(1) == 0, "Testing ChangeOutput(%d, settings): Expected : %d, actual %d", 0x00001,  0x0000   , outputHandler.GetLedStateOfOutput(1));	

	settings.UpdateSettings(0x1010);
	outputHandler.UpdateLEDs(settings);
	TEST_CHECK_(outputHandler.GetLedStateOfOutput(0) == 1, "Testing ChangeOutput(%d, settings): Expected : %d, actual %d", 0x00001,  0x0001   , outputHandler.GetLedStateOfOutput(0));	
}

void test_temperatureController(void)
{
	TEST_CHECK_(0==1, "dummy_test");
}

TEST_LIST = 
{
    {"DigitalIOController.Initialize();", test_digital_io_controller_initialize},
    {"DigitalIOController.TurnOn();", test_digital_io_controller_TurnOn},
    {"DigitalIOController.TurnOff();", test_digital_io_controller_TurnOff},
    {"SettingsHandler.UpdateSettings();", test_settings_handler_UpdateSettings},
    {"SettingsHandler.LoadDefaultSettings();", test_settings_handler_DefaultSettings},
    {"SettingsHandler.GetOutputSettings();", test_settings_get_output_settings},
    {"UartHandler.ConvertFromHexToUint16(char hexString[MESSAGE_BUFFER]);" ,test_uart_handler_ConvertFromHexToUint16},
    {"UartHandler.GetMessageType();",test_uart_handler_GetMessageType},
    {"UartHandler.MessageIsValid();",test_uart_handler_MessageIsValid},
    {"UartHandler.GetMessage()", test_uart_get_message}, 
    {"OutputHandler.ChangeOutput();",test_output_handler_ChangeOutput},
	{"Testing the temperature controller", test_temperatureController},    
	{0}
};
*/