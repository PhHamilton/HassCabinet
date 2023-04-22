
class HassBoxCommands()
	def __init__(): 
		pass

	def UpdateOutputSettings(self, output, settings): 
		pass

	def GetCurrentSettings(self): 
		pass

	def TurnOnFan(self): 
		pass

	def GetBoxTemperature(self): 
		return "0xA000"

	def GetBoxHumidity(self): 
		pass

	def TurnOnOutputNo(self, outputNumber): 
		pass

	def TurnOffOutputNo(self, outputNumber):
		pass

	def TurnOnAllOutputs(self): 
		return "0x000F"

	def TurnOffAllOutputs(self): 
		return "0x0000"
