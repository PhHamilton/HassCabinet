#include "header/io_configuration.hpp"
#include "header/io_controller.hpp"
#include "header/relay_controller.hpp"
#include "header/temperature_sensor_controller.hpp"
#include "header/uart_handler.hpp"


io_information io; 
 
IOController light(io);

typedef struct {
    uint8_t *portb_addr;
} Memory;

// Define a macro to shift 5 bits in a memory address

#define SHIFT_PORTB(ar, bits) (*(ar.portb_addr) = (1 << (bits)))


Memory ar; 

void setup() 
{
  Serial.begin(9600); 
  ar.portb_addr = &PORTB;
  DDRB |= 1<<5; 
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
	delay(1000);
}
