#include "header/io_configuration.hpp"
#include "header/digital_io_controller.hpp"
#include "header/temperature_sensor_controller.hpp"
#include "header/settings.hpp"
#include "header/uart_handler.hpp"
#include "header/output_handler.hpp"
#include <math.h>

#define BUFFER_SIZE 6
io_information io_4 {.DDR = &DDRB, .PORT = &PORTB, .PIN = &PINB, .BIT = 3}; 
io_information led_4 {.DDR = &DDRD, .PORT = &PORTD, .PIN = &PIND, .BIT = 4}; 

io_information io_3 {.DDR = &DDRB, .PORT = &PORTB, .PIN = &PINB, .BIT = 2}; 
io_information led_3 {.DDR = &DDRD, .PORT = &PORTD, .PIN = &PIND, .BIT = 5};

io_information io_2 {.DDR = &DDRB, .PORT = &PORTB, .PIN = &PINB, .BIT = 1}; 
io_information led_2 {.DDR = &DDRD, .PORT = &PORTD, .PIN = &PIND, .BIT = 6};

io_information io_1 {.DDR = &DDRB, .PORT = &PORTB, .PIN = &PINB, .BIT = 0}; 
io_information led_1 {.DDR = &DDRD, .PORT = &PORTD, .PIN = &PIND, .BIT = 7};

 
UartHandler uartHanlder; 
OutputHandler outputHandler(io_1, led_1, io_2, led_2, io_3, led_3, io_4, led_4); 
SettingsHandler settingsHandler;


io_information DHT11 {.DDR = &DDRD, .PORT = &PORTD, .PIN = &PIND, .BIT = 3};
TemperatureSensor temperatureSensor(DHT11);

typedef struct {
    uint8_t *portb_addr;
} Memory;

Memory ar; 

uint32_t UartMessage; 

void setup() 
{
  Serial.begin(9600);
  settingsHandler.LoadDefaultSettings(); 
  uartHanlder.Initialize(); 
  outputHandler.Initialize(); 
  temperatureSensor.Initialize(); 
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
        settingsHandler.UpdateSettings(UartMessage); 
        outputHandler.UpdateLEDs(settingsHandler);
        break;

      case CHANGE_OUTPUT: 
        outputHandler.ChangeOutput(UartMessage, settingsHandler); 
        break; 

      case REQUEST_MICROCONTROLLER_TEMPERATURE:
       
        break; 

      case REQUEST_CABINET_TEMPERATURE:
          temperatureSensor.ReadSensorData(); 
          uartHanlder.SendIntMessage(temperatureSensor.GetTemperature()); 
        break; 
      case REQUEST_CABINET_HUMIDITY:
          temperatureSensor.ReadSensorData(); 
          uartHanlder.SendIntMessage(temperatureSensor.GetHumidity()); 
        break; 
      case REQUEST_OUTPUT_SETTINGS: 
        //uartHandler.SendMessage(settingsHndler.GetOutputSettings(~((UartMessage >> 12) && 0xF)));
        break; 

      case REQUEST_OUTPUT_STATE: 
        //uartHanlder.SendMessage(outputHandler.GetStateOfAllOutputs());
        break;
      default: 
        // UNKNOWN STATE
        break;
    }
  }

  
  // Idle state! 
  
}
