#ifndef __io_configuration__
#define __io_configuration__

#define GET_BIT(byte, bitpos) (uint8_t)((byte >> bitpos) & 1); 
#define SET_BIT(bitpos) (1 << bitpos)

#define SET_BIT_AT_ADDRESS(BYTEADDR, BITPOS) ((*BYTEADDR) |= (1ULL<<(BITPOS)))
#define CLR_BIT_AT_ADDRESS(BYTEADDR, BITPOS) ((*BYTEADDR) &= ~(1ULL<<(BITPOS)))
#define TOGGLE_BIT_AT_ADDRESS(BYTEADDR, BITPOS) ((*BYTEADDR) ^= (1ULL<<BITPOS))
#define GET_BIT_AT_ADDRESS(BYTEADDR, BITPOS) ((*BYTEADDR) >> BITPOS) & 1

#define OFF 0
#define ON 1
#define FALSE 0
#define TRUE 1 
#define NUMBER_OF_OUTPUTS 4

#define RELAY_DDR DDRB
#define RELAY_1_PIN 5 
#define RELAY_2_PIN 6
#define RELAY_3_PIN 7
#define RELAY_4_PIN 8 

#define RELAY_LIGHT_DDR 
#define RELAY_1_LIGHT_PIN 1
#define RELAY_2_LIGHT_PIN 2 
#define RELAY_3_LIGHT_PIN 3
#define RELAY_4_LIGHT_PIN 4

#define TEMPERATURE_PIN 9

#endif 