#ifndef __settings_h__
#define __settings_h__

#define NUMBER_OF_OUTPUTS 4

//#include "Arduino.h"
#include <stdint.h>

typedef struct
{

	struct 
	{
		uint8_t forceOn;
		uint8_t enableLed;
		uint8_t blinkFrequency;   

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
		void GetLoggingFrequency(void); 
		void GetLoggingStatus(void);
		void GetFanController(void); 
		uint8_t GetOutputSettings(uint8_t outputNumber);


	private: 
		settings _settings; 

};
 

#endif
