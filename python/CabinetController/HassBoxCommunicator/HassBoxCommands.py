import sys
sys.path.insert(0,'..')


BAUD_RATE = 9600
COM_PORT = "/dev/ttyACM1"

NUMBER_OF_RETURN_BYTES = 6 

FAN_OUTPUT = 8
REQUEST_STATE_OF_ALL_OUTPUTS = "0xF000"
REQUEST_CABINET_HUMIDITY = "0xB000"
REQUEST_CABINET_TEMPERATURE = "0xA000"
REQUEST_MICROCONTROLLER_TEMPERATURE = "0x9000"
TURN_ON_ALL_OUTPUTS = "0x000F"
TURN_OFF_ALL_OUTPUTS = "0x0000"

OUTPUT_START_BIT = 11 
MAXIMUM_BLINK_FREQUENCY = 3 
MINIMUM_BLINK_FREQUENCY = 0
MAXIMUM_TEMPERATURE = 15
MINIMUM_TEMPERATURE = 0
ENABLED = 1 
DISABLED = 0

TEMPERATURE_CONTROL_BIT = 8
LOGGING_BIT = 9
OUTPUT_ENABLE_BIT = 5
LED_ENABLE_BIT = 4
BLINK_FREQUENCY_BIT = 6
NUMBER_OF_INPUTS = 4


class HassBoxCommunicator:
	def __init__(self): 
		#self.serial.Open()

		#self.__outputState = np.uint16(self.GetOutputState())
		self.__outputState = 0

	def UpdateOutputSettings(self, outputNumber): 
		self.__outputState |= 1 << OUTPUT_START_BIT+(outputNumber + 1)
	
	def ClearOutputNumber(self): 
		for i in range(NUMBER_OF_INPUTS+1): 
			self.__clearBit(OUTPUT_START_BIT + i)

	def ClearMessage(self): 
		self.__outputState = 0; 

	def GetCurrentOutputSettings(self, outputNumber): 
		pass

	def TurnOnFan(self): 
		pass

	def ResetToDefaultSettings(self): 
		self.__clearBit(LOGGING_BIT)
		self.__clearBit(TEMPERATURE_CONTROL_BIT)
	
	def ResetToDefaultOutputSettings(self): 
		self.__setBit(LED_ENABLE_BIT)
		self.__clearBit(OUTPUT_ENABLE_BIT)
		self.__clearBit(BLINK_FREQUENCY_BIT)
		self.__clearBit(BLINK_FREQUENCY_BIT+1)

	def GetMicrocontrollerTemperature(self):
		return REQUEST_MICROCONTROLLER_TEMPERATURE
		
	def GetBoxTemperature(self): 
		return REQUEST_CABINET_TEMPERATURE

	def GetBoxHumidity(self): 
		return REQUEST_CABINET_HUMIDITY

	def TurnOnOutputNo(self, outputNumber): 
		#currentOutputState
		#newoutputstate
		self.__setBit(outputNumber)
		
	def TurnOffOutputNo(self, outputNumber):
		self.__clearBit(outputNumber)
	
	def UpdateOutputState(self, outputNumber): 
		if(self.__getBit(outputNumber) == DISABLED):
			self.TurnOnOutputNo(outputNumber)
		else:
			self.TurnOffOutputNo(outputNumber)

	def UpdateLoggingState(self):
		if(self.__getBit(LOGGING_BIT) == DISABLED):
			self.__setBit(LOGGING_BIT)
		else:
			self.__clearBit(LOGGING_BIT)
	
	def EnableTemperatureControl(self): 
		if(self.__getBit(TEMPERATURE_CONTROL_BIT) == DISABLED):
			self.__setBit(TEMPERATURE_CONTROL_BIT)
		else:
			self.__clearBit(TEMPERATURE_CONTROL_BIT)

	def UpdateOutputAvailability(self): 
		self.__updateBit(OUTPUT_ENABLE_BIT)

	def UpdateLedAvailability(self): 
		self.__updateBit(LED_ENABLE_BIT)

	def UpdateBlinkFrequency(self, blinkFrequency): 
		self.__clearBit(BLINK_FREQUENCY_BIT)
		self.__clearBit(BLINK_FREQUENCY_BIT + 1)
		#self.__outputState |= int(blinkFrequency) << int(BLINK_FREQUENCY_BIT)

		if(blinkFrequency == 1):
			self.__setBit(BLINK_FREQUENCY_BIT)
		elif(blinkFrequency == 2): 
			self.__setBit(BLINK_FREQUENCY_BIT+1)
		elif(blinkFrequency == 3): 
			self.__setBit(BLINK_FREQUENCY_BIT)
			self.__setBit(BLINK_FREQUENCY_BIT+1)
		else:
			pass

	def GetOutputState(self):
		#self.__readOutputState()
		#return self.__outputState
		return self.__outputState

	def TurnOnAllOutputs(self): 
		return TURN_ON_ALL_OUTPUTS

	def TurnOffAllOutputs(self): 
		return TURN_OFF_ALL_OUTPUTS
	
	def __updateBit(self, bit): 
		if(self.__getBit(bit) == DISABLED):
			self.__setBit(bit)
		else:
			self.__clearBit(bit)

	def __setBit(self, bit):
		self.__outputState |= 1 << int(bit)

	def __clearBit(self, bit): 
		self.__outputState &= ~(1 << (int(bit)))
	
	def __getBit(self, bit):
		return (self.__outputState >> int(bit)) & 1

	def __readOutputState(self):
		self.__outputState = self.serial.WriteReadBytes(REQUEST_STATE_OF_ALL_OUTPUTS, NUMBER_OF_RETURN_BYTES)


class OutputSettings(): 
	def __init__(self): 
		self.__temperatureLimit = DISABLED
		self.__led = ENABLED
		self.__forceOnStatus = DISABLED
		self.__blinkFrequency = DISABLED
		self.__fanController = DISABLED
		self.__logging = DISABLED
	
	def SetTemperatureLimit(self, maximunTemperature):
		if(maximunTemperature > MAXIMUM_TEMPERATURE): 
			self.__temperatureLimit = MAXIMUM_TEMPERATURE
		elif(maximunTemperature < MINIMUM_TEMPERATURE):
			self.__temperatureLimit = MINIMUM_TEMPERATURE
		else:	
			self.__temperatureLimit = maximunTemperature
	
	def GetTemperatureLimit(self): 
		return self.__temperatureLimit

	def EnableLed(self):
		self.__led = ENABLED

	def DisableLed(self): 
		self.__led = DISABLED

	def GetLedStatus(self):
		return self.__led

	def ForceLedOn(self):
		self.__forceOnStatus = ENABLED

	def ForceLedOff(self): 
		self.__forceOnStatus = DISABLED 

	def GetForcedLedStatus(self): 
		return self.__forceOnStatus
	
	def SetBlinkFrequency(self, frequency):
		if(frequency > MAXIMUM_BLINK_FREQUENCY): 
			self.__blinkFrequency = MAXIMUM_BLINK_FREQUENCY
		elif(frequency < MINIMUM_BLINK_FREQUENCY):
			self.__blinkFrequency = MINIMUM_BLINK_FREQUENCY
		else:	
			self.__blinkFrequency = frequency

	def GetBlinkFrequency(self): 
		return self.__blinkFrequency

	def EnableFanController(self): 
		self.__fanController = ENABLED

	def DisableFanController(self): 
		self.__fanController = DISABLED

	def GetFanControllerStatus(self): 
		return self.__fanController

	def EnableLogging(self): 
		self.__logging = ENABLED

	def DisableLogging(self): 
		self.__logging = DISABLED 

	def GetLoggingStatus(self): 
		return self.__logging

class OutputStringBuilder(): 
	def __init__(self): 
		pass

	def CreateHexNumber(self, outputNumber, settings = None): 
		pass 
		
	def ConvertToHexNumber(self, outputNo): 
		hexNumber |= __shiftBit(OUTPUT_START_BIT + (outputNumber - 1))


		return "0x000" + self.__numberToString(self.__shiftBit(outputNumber))

	def __shiftBit(self, bitpos):
		return 1 << bitpos

	def __numberToString(number):
		return string(number)


