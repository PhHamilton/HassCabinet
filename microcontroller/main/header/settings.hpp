#ifndef __settings_h__
#define __settings_h__

#include <stdint.h>
#include "io_configuration.hpp"

typedef struct
{
	struct 
	{
		uint8_t forceOn;
		uint8_t enableLed;
		uint8_t blinkFrequency;   
		uint32_t lastBlinked; 
	} LedStatusSetting[NUMBER_OF_OUTPUTS];		
	
	uint8_t enableFanController;
	uint8_t enableLogging;
	uint16_t loggingFrequency;

}settings;


class SettingsHandler
{
	public:
		SettingsHandler(void); 
		void UpdateSettings(uint16_t settings);
		void LoadDefaultSettings(void);
		uint8_t GetLoggingFrequency(void); 
		uint8_t GetLoggingStatus(void);
		uint8_t GetFanController(void); 
		uint8_t GetOutputSettings(uint8_t outputNumber);
		uint8_t GetBlinkFrequency(uint8_t outputNumber); 
		uint8_t IsForced(uint8_t outputNumber); 
		uint8_t IsEnabled(uint8_t outputNumber); 
		uint32_t GetLastBlinked(uint8_t outputNumber);
		void SetLastBlinked(uint8_t outputNumber, uint32_t lastBlinked); 

	private: 
		settings _settings; 
		uint8_t _getOutputNumber(uint8_t settingsNumber); 

};
#endif
