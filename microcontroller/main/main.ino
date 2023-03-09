#include "header/io_configuration.hpp"
#include "header/digital_io_controller.hpp"
#include "header/temperature_sensor_controller.hpp"
#include "header/settings.hpp"
#include "header/uart_handler.hpp"
#include <math.h>

#define BUFFER_SIZE 6

io_information io; 
 
DigitalIOController light(io);
UartHandler uartHanlder; 
OutputHandler outputHandler(); 

typedef struct {
    uint8_t *portb_addr;
} Memory;

Memory ar; 

uint16_t UartMessage; 

void setup() 
{
  uartHanlder.Initialize(); 
  outputHandler.Initialize(); 
}

void loop() 
{
  if(uartHanlder.MessageAvailable())
  {
    UartMessage = uartHanlder.GetMessage(); 
    switch(uartHanlder.GetMessageType(UartMessage))
    {
      case UNKNOWN:
        break; 
      case UPDATE_SETTINGS:
        break;
      case CHANGE_OUTPUT: 
        outputHandler.ChangeOutput(UartMessage); 
        break; 
      case REQUEST_MICROCONTROLLER_TEMPERATURE:
        break; 
      case REQUEST_CABINET_TEMPERATURE:
        break; 
      default: 
        // UNKNOWN STATE
        break;
    }
  }
  // Idle state! 
  
}
