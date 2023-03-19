#include "header/io_configuration.hpp"
#include "header/digital_io_controller.hpp"
#include "header/temperature_sensor_controller.hpp"
#include "header/settings.hpp"
#include "header/uart_handler.hpp"
#include "header/output_handler.hpp"
#include <math.h>

#define BUFFER_SIZE 6
io_information io_0 {.DDR = 0x24, .PORT = 0x25, .PIN = 0x23, .BIT = 3}; 
io_information led_0 {.DDR = &PORTD, .PORT = &PORTD, .PIN = &PORTD, .BIT = 7}; 

io_information io_1 {.DDR = &DDRB, .PORT = &PORTB, .PIN = &PINB, .BIT = 2}; 
io_information led_1 {.DDR = &PORTD, .PORT = &PORTD, .PIN = &PORTD, .BIT = 6};

io_information io_2 {.DDR = &DDRB, .PORT = &PORTB, .PIN = &PINB, .BIT = 1}; 
io_information led_2 {.DDR = &PORTD, .PORT = &PORTD, .PIN = &PORTD, .BIT = 5};

io_information io_3 {.DDR = &DDRB, .PORT = &PORTB, .PIN = &PINB, .BIT = 0}; 
io_information led_3 {.DDR = &PORTD, .PORT = &PORTD, .PIN = &PORTD, .BIT = 4};

 
UartHandler uartHanlder; 
OutputHandler outputHandler(io_0, led_0, io_1, led_1, io_2, led_2, io_3, led_3); 
SettingsHandler settingsHandler;

typedef struct {
    uint8_t *portb_addr;
} Memory;

Memory ar; 

uint16_t UartMessage; 

void setup() 
{
  Serial.begin(9600);
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
        settingsHandler.UpdateSettings(UartMessage); 
        break; 
      case UPDATE_SETTINGS:
        break;
      case CHANGE_OUTPUT: 
        outputHandler.ChangeOutput(UartMessage, settingsHandler); 
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
