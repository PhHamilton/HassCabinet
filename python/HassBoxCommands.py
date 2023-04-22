FAN_OUTPUT = 8

class HassBoxCommands()
	def __init__(): 
		stringBuilder = OutputStringBuilder()

	def UpdateOutputSettings(self, outputNumber, settings): 
		pass

	def GetCurrentOutputSettings(self, outputNumber): 
		pass

	def TurnOnFan(self): 
		return stringBuilder.ConvertToHexNumber(FAN_OUTPUT) 

	def GetBoxTemperature(self): 
		return "0xA000"

	def GetBoxHumidity(self): 
		return "0xB000"

	def TurnOnOutputNo(self, outputNumber): 
		#currentOutputState
		#newoutputstate
		return stringBuilder.ConvertToHexNumber(outputNumber)

	def TurnOffOutputNo(self, outputNumber):
		#currentOutputState = Get output state! 
		#newOutputState |= ~self.__shiftBit(outputNumber)

		return stringBuilder.ConvertToHexNumber(outputNumber)

	def TurnOnAllOutputs(self): 
		return "0x000F"

	def TurnOffAllOutputs(self): 
		return "0x0000"

class OutputStringBuilder(self): 
	def __init__(self): 
		pass
	def ConvertToHexNumber(self, outputNo): 
		return "0x000" + self.__numberToString(self.__shiftBit(outputNumber))

	def __shiftBit(self, bitpos)
		return 1 << bitpos

	def __numberToString(number)
		return string(number)
