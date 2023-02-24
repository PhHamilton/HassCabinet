#ifndef __settings_h__
#define __settings_h__

#define NUMBER_OF_LEDS
#include "Arduino.h"


typedef struct
{
	uint8_t flashHighVoltage; 
	
	struct 
	{
		uint8_t forceOn; 

	} LedStatusSetting[NUMBER_OF_LEDS];		

	
	uint8_t enableFanController;
	uint8_t enableLogging;
	uint16_t loggingFrequency;

}settings;

settings ControllerSettings; 

#endif
