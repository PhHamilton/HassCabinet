#include "header/io_configuration.hpp"
#include "header/digital_io_controller.hpp"
#include "header/temperature_sensor_controller.hpp"
#include "header/uart_handler.hpp"
#include <math.h>

#define BUFFER_SIZE 6

io_information io; 
 
DigitalIOController light(io);
UartHandler uartHanlder(); 

typedef struct {
    uint8_t *portb_addr;
} Memory;

Memory ar; 

void setup() 
{
  Serial.begin(9600); 
  handler.Initialize(); 
  char test[BUFFER_SIZE] = {'0','x','0','0','0','F'};

  Serial.println(HexValueConverter("0xFA21"));


  
}

void loop() 
{
  if(handler.MessageAvailable)
  {



    
  }
}
