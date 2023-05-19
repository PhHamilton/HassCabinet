from HassBoxCommands import *
#from HassBoxCommunicator.HassBoxCommands import *

class TestOutputSettings: 
	def setup_method(self):
		self.outputsettings = OutputSettings()
	
	def test_default_settings(self): 
		assert  self.outputsettings.GetTemperatureLimit() == DISABLED
		assert  self.outputsettings.GetLedStatus() == ENABLED
		assert  self.outputsettings.GetForcedLedStatus() == DISABLED
		assert  self.outputsettings.GetBlinkFrequency() == DISABLED
		assert  self.outputsettings.GetFanControllerStatus() == DISABLED
		assert  self.outputsettings.GetLoggingStatus() == DISABLED

	def test_update_parameters(self): 

		temperatureLimit = 5
		self.outputsettings.SetTemperatureLimit(temperatureLimit)
		assert  self.outputsettings.GetTemperatureLimit() == temperatureLimit

		self.outputsettings.DisableLed()
		assert  self.outputsettings.GetLedStatus() == DISABLED
		self.outputsettings.EnableLed()
		assert  self.outputsettings.GetLedStatus() == ENABLED
		
		self.outputsettings.ForceLedOn()
		assert  self.outputsettings.GetForcedLedStatus() == ENABLED
		self.outputsettings.ForceLedOff()
		assert  self.outputsettings.GetForcedLedStatus() == DISABLED

		blinkFrequency = 3 
		self.outputsettings.SetBlinkFrequency(blinkFrequency)
		assert  self.outputsettings.GetBlinkFrequency() == blinkFrequency

		self.outputsettings.EnableFanController()
		assert  self.outputsettings.GetFanControllerStatus() == ENABLED
		self.outputsettings.DisableFanController()
		assert  self.outputsettings.GetFanControllerStatus() == DISABLED

		self.outputsettings.EnableLogging()
		assert  self.outputsettings.GetLoggingStatus() == ENABLED
		self.outputsettings.DisableLogging()
		assert  self.outputsettings.GetLoggingStatus() == DISABLED

	def test_to_exceed_maximum_temperature_limits(self): 
		temperatureLimit = MAXIMUM_TEMPERATURE + 10

		self.outputsettings.SetTemperatureLimit(temperatureLimit)
		assert  self.outputsettings.GetTemperatureLimit() == MAXIMUM_TEMPERATURE

		temperatureLimit = MINIMUM_TEMPERATURE - 10
		self.outputsettings.SetTemperatureLimit(temperatureLimit)
		assert  self.outputsettings.GetTemperatureLimit() == MINIMUM_TEMPERATURE


	def test_to_exceed_maximum_blink_frequency_limits(self): 
		blinkFrequency = MAXIMUM_BLINK_FREQUENCY + 10

		self.outputsettings.SetBlinkFrequency(blinkFrequency)
		assert  self.outputsettings.GetBlinkFrequency() == MAXIMUM_BLINK_FREQUENCY

		blinkFrequency = MINIMUM_BLINK_FREQUENCY - 10

		self.outputsettings.SetBlinkFrequency(blinkFrequency)
		assert  self.outputsettings.GetBlinkFrequency() == MINIMUM_BLINK_FREQUENCY


class TestStringbuilder: 
	def setup_method(self):
		pass
	
	def test_1(self): 
		assert  1 == 1