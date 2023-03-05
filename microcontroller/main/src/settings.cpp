#include "../header/settings.hpp"

#define GET_BIT(byte, bitpos) (uint8_t)((byte >> bitpos) & 1); 

#define ENABLE_LED 					4
#define FORCE_ON_BIT 				5
#define BLINK_FREQUENCY_LOW_BIT 	6
#define BLINK_FREQUENCY_HIGH_BIT 	7

#define FAN_CONTROLLER_ENABLE_BIT  	8
#define LOGGING_ENABLE_BIT 		   	9
#define LOGGING_FREQUENCY_LOW_BIT  	10
#define LOGGING_FREQUENCY_HIGH_BIT 	11

SettingsHandler::SettingsHandler(void){}

void SettingsHandler::UpdateSettings(uint16_t settings)
{
	uint8_t outputNo; 
	switch(settings >> 12)
	{
		case 1:
			outputNo = 0; 
			break; 
		case 2: 
			outputNo = 1; 
			break; 
		case 4: 
			outputNo = 2; 
			break; 
		case 8: 
			outputNo = 3; 
			break; 

		default: 
			//Unknown state, do nothing.. 
			return; 
	}

	uint8_t highBit; 
	uint8_t lowBit; 

	_settings.enableFanController = GET_BIT(settings, FAN_CONTROLLER_ENABLE_BIT);
	_settings.enableLogging = GET_BIT(settings, LOGGING_ENABLE_BIT);
	
	highBit = 2 * GET_BIT(settings, LOGGING_FREQUENCY_HIGH_BIT);
	lowBit = GET_BIT(settings, LOGGING_FREQUENCY_LOW_BIT);

	_settings.loggingFrequency = highBit + lowBit; 
	_settings.LedStatusSetting[outputNo].enableLed = GET_BIT(settings, ENABLE_LED)
	_settings.LedStatusSetting[outputNo].forceOn = GET_BIT(settings, FORCE_ON_BIT)

	highBit = 2 * GET_BIT(settings, BLINK_FREQUENCY_HIGH_BIT); 
	lowBit = GET_BIT(settings, BLINK_FREQUENCY_LOW_BIT);
	_settings.LedStatusSetting[outputNo].blinkFrequency = highBit + lowBit;
}

uint8_t SettingsHandler::GetOutputSettings(uint8_t outputNumber)
{

	uint8_t settingsbyte = 0x00; 
	// settingsbyte |= _settings.loggingFrequency << 6;
	// settingsbyte |= _settings.enableLogging << 5;
	// settingsbyte |= (_settings.enableFanController << 4);

	settingsbyte |= _settings.LedStatusSetting[outputNumber].blinkFrequency << 2;
	settingsbyte |= _settings.LedStatusSetting[outputNumber].forceOn << 1;
	settingsbyte |= _settings.LedStatusSetting[outputNumber].enableLed << 0;


	return  settingsbyte; 
}

uint8_t SettingsHandler::GetLoggingFrequency(void)
{
	return _settings.loggingFrequency;
}

uint8_t SettingsHandler::GetLoggingStatus(void)
{
	return _settings.enableLogging; 
}

uint8_t SettingsHandler::GetFanController(void)
{
	return _settings.enableFanController; 
}

uint8_t SettingsHandler::GetBlinkFrequency(uint8_t outputNumber)
{
	return _settings.LedStatusSetting[outputNumber].blinkFrequency;
}

uint8_t SettingsHandler::IsForced(uint8_t outputNumber)
{
	return _settings.LedStatusSetting[outputNumber].forceOn;
}

uint8_t SettingsHandler::IsEnabled(uint8_t outputNumber)
{
	return _settings.LedStatusSetting[outputNumber].enableLed;
}


