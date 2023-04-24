FAN_OUTPUT = 8
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

class HassBoxCommands():
	def __init__(): 
		stringBuilder = OutputStringBuilder()

	def UpdateOutputSettings(self, outputNumber, settings): 
		pass

	def GetCurrentOutputSettings(self, outputNumber): 
		pass

	def TurnOnFan(self): 
		return stringBuilder.ConvertToHexNumber(FAN_OUTPUT) 

	def GetMicrocontrollerTemperature(self):
		return REQUEST_MICROCONTROLLER_TEMPERATURE
		
	def GetBoxTemperature(self): 
		return REQUEST_CABINET_TEMPERATURE

	def GetBoxHumidity(self): 
		return REQUEST_CABINET_HUMIDITY

	def TurnOnOutputNo(self, outputNumber): 
		#currentOutputState
		#newoutputstate
		return stringBuilder.ConvertToHexNumber(outputNumber)

	def TurnOffOutputNo(self, outputNumber):
		#currentOutputState = Get output state! 
		#newOutputState |= ~self.__shiftBit(outputNumber)

		return stringBuilder.ConvertToHexNumber(outputNumber)

	def TurnOnAllOutputs(self): 
		return TURN_ON_ALL_OUTPUTS

	def TurnOffAllOutputs(self): 
		return TURN_OFF_ALL_OUTPUTS


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
		return self.__led;

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


