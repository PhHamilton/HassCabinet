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

		#self.__msg = np.uint16(self.GetOutputState())
		self.__outputState = 0
		self.__outputSettings = []
		self.__msg = 0

	def UpdateOutputSettings(self, outputNumber): 
		self.__outputSettings[outputNumber] |= 1 << OUTPUT_START_BIT+(outputNumber + 1)

	def SetOutputSettings(self, outputSettings):
		#for setting in enumerate(outputSettings): 
		self.__outputSettings = outputSettings
	
	def ClearOutputNumber(self): 
		for i in range(NUMBER_OF_INPUTS+1): 
			self.__clearOutputBit(OUTPUT_START_BIT + i)

	def ClearMessage(self): 
		self.__msg = 0; 

	def GetCurrentOutputSettings(self, outputNumber): 
		return self.__outputSettings[outputNumber]

	def TurnOnFan(self): 
		pass

	def ResetToDefaultSettings(self): 
		for i in range(4):
			self.__clearSettingsBit(i, LOGGING_BIT)
			self.__clearSettingsBit(i, TEMPERATURE_CONTROL_BIT)
	
	def ResetToDefaultOutputSettings(self): 
		for i in range(4):
			self.__setSettingsBit(i, LED_ENABLE_BIT)
			self.__clearSettingsBit(i, OUTPUT_ENABLE_BIT)
			self.__clearSettingsBit(i, BLINK_FREQUENCY_BIT)
			self.__clearSettingsBit(i, BLINK_FREQUENCY_BIT+1)

	def TurnOnOutputNo(self, outputNumber): 
		self.__setOutputBit(outputNumber)
		
	def TurnOffOutputNo(self, outputNumber):
		self.__clearOutputBit(outputNumber)
	
	def UpdateStateOfAllOutputs(self, state): 
		self.__outputState = state

	def UpdateOutputState(self, outputNumber): 
		if(self.__getBit(self.__outputState, outputNumber) == DISABLED):
			self.TurnOnOutputNo(outputNumber)
		else:
			self.TurnOffOutputNo(outputNumber)

	def UpdateLoggingState(self):
		for i in range(4):
			if(self.__getBit(self.__outputSettings[i], LOGGING_BIT) == DISABLED):
				self.__setSettingsBit(i, LOGGING_BIT)
			else:
				self.__clearSettingsBit(i, LOGGING_BIT)
	
	def EnableTemperatureControl(self): 
		for i in range(4):
			if(self.__getBit(self.__outputSettings[i], TEMPERATURE_CONTROL_BIT) == DISABLED):
				self.__setSettingsBit(i, TEMPERATURE_CONTROL_BIT)
			else:
				self.__clearSettingsBit(i, TEMPERATURE_CONTROL_BIT)

	def UpdateOutputAvailability(self, outputNumber): 
		if(self.__getBit(self.__outputSettings[outputNumber], OUTPUT_ENABLE_BIT) == DISABLED):
			self.__setSettingsBit(outputNumber, OUTPUT_ENABLE_BIT)
		else:
			self.__clearSettingsBit(outputNumber, OUTPUT_ENABLE_BIT)

	def UpdateLedAvailability(self, outputNumber): 
		if(self.__getBit(self.__outputSettings[outputNumber], LED_ENABLE_BIT) == DISABLED):
			self.__setSettingsBit(outputNumber, LED_ENABLE_BIT)
		else:
			self.__clearSettingsBit(outputNumber, LED_ENABLE_BIT)

	def UpdateBlinkFrequency(self, outputNumber, blinkFrequency): 
		self.__clearSettingsBit(outputNumber, BLINK_FREQUENCY_BIT)
		self.__clearSettingsBit(outputNumber, BLINK_FREQUENCY_BIT + 1)

		if(blinkFrequency == 1):
			self.__setSettingsBit(outputNumber, BLINK_FREQUENCY_BIT)
		elif(blinkFrequency == 2): 
			self.__setSettingsBit(outputNumber, BLINK_FREQUENCY_BIT+1)
		elif(blinkFrequency == 3): 
			self.__setSettingsBit(outputNumber, BLINK_FREQUENCY_BIT)
			self.__setSettingsBit(outputNumber, BLINK_FREQUENCY_BIT+1)
		else:
			pass

	def GetStateOfOutput(self, outputnumber): 
		return int(self.__getBit(self.__outputState, outputnumber))

	def GetOutputState(self):
		return self.__outputState
	
	def GetSettings(self, outputNumber): 
		self.__clearSettingsBit(outputNumber, 12 + outputNumber)
		self.__setSettingsBit(outputNumber, 12 + outputNumber)
		return self.__outputSettings[outputNumber]

	def TurnOnAllOutputs(self): 
		return TURN_ON_ALL_OUTPUTS

	def TurnOffAllOutputs(self): 
		return TURN_OFF_ALL_OUTPUTS
	
	def __updateBit(self, bit): 
		if(self.__getBit(bit) == DISABLED):
			self.__setBit(bit)
		else:
			self.__clearBit(bit)

	def __setOutputBit(self, bit):
		self.__outputState |= 1 << int(bit)

	def __clearOutputBit(self, bit): 
		self.__outputState &= ~(1 << (int(bit)))

	def __setSettingsBit(self, settingsNo, bit):
		self.__outputSettings[settingsNo] |= 1 << int(bit); 
	
	def __clearSettingsBit(self, settingsNo, bit): 
		self.__outputSettings[settingsNo] &= ~(1 << (int(bit)))
	
	def __getBit(self, byte, bit):
		return (byte >> int(bit)) & 1

	def __readOutputState(self):
		self.__msg = self.serial.WriteReadBytes(REQUEST_STATE_OF_ALL_OUTPUTS, NUMBER_OF_RETURN_BYTES)


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


