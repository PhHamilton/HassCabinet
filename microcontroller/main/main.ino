#include "header/io_configuration.hpp"
#include "header/digital_io_controller.hpp"
#include "header/temperature_sensor_controller.hpp"
#include "header/uart_handler.hpp"


io_information io; 
 
DigitalIOController light(io);

typedef struct {
    uint8_t *portb_addr;
} Memory;

Memory ar; 

void setup() 
{
  Serial.begin(9600); 
  ar.portb_addr = &PORTB;
  light.Initialize();
  //CLR_BIT(PORTB, 5); 
	light.Initialize(); 
	light.TurnOff(); 
}

void loop() 
{
  //PORTB |= 1<<5;
	//delay(500); 
  //SHIFT_PORTB(ar, -5);
  light.Toggle();
  Serial.println(light.GetState());
	delay(250);
}
