from MenuHandler.MenuHandler import MenuHandler

GO_TO_SETTINGS_KEY = '4'
CHANGE_OUPUT_SETTINGS_KEY = '2'
NUMBER_OF_OUTPUTS = 4 
NUMBER_OF_SETTINGS = 2 
NUMBER_OF_OUTPUT_SETTINGS = 3


def GetBitFromByte(byte, bit): 
	return (int(byte) >> int(bit)) & 1

class TestNavigateMenu: 
	def setup_method(self):
		self.menu = MenuHandler(True)
	
	def test_changeMenu(self): 
		assert self.menu.GetCurrentMenu() == 0 
		
		self.menu.Update(GO_TO_SETTINGS_KEY)
		assert self.menu.GetCurrentMenu() == 1

		self.menu.Update(CHANGE_OUPUT_SETTINGS_KEY)
		assert self.menu.GetCurrentMenu() == 2

class TestLoadOutputs:
	def setup_method(self):
		self.menu = MenuHandler(True)
	
	def test_changeOutputState(self): 
		outputState = 0xF

	def test_changeOutputSettings(self): 
		self.SetAndCheckOutputState(0x05)
		self.SetAndCheckOutputState(0x01)
		self.SetAndCheckOutputState(0x0F)
		self.SetAndCheckOutputState(0x04)
	
	def SetAndCheckOutputState(self, options): 
		self.menu.SetMenuOption(options)
		currentOutput = self.menu.GetOutputOptions()

		for i in range(NUMBER_OF_OUTPUTS): 
			assert currentOutput[i].action == GetBitFromByte(options, i)

class TestLoadSettings: 
	def setup_method(self):
		self.menu = MenuHandler(True)
		self.menu.Update(GO_TO_SETTINGS_KEY)
	
	def test_changeSettings(self): 
		assert self.menu.GetCurrentMenu() == 1

		self.SetAndCheckSettings(0x00)
		self.SetAndCheckSettings(0x01)
		self.SetAndCheckSettings(0x02)
		self.SetAndCheckSettings(0x03)

	def SetAndCheckSettings(self, settings): 
		self.menu.SetMenuOption(settings)
		currentSetting = self.menu.GetCurrentSettings()

		for i in range(NUMBER_OF_SETTINGS): 
			assert currentSetting[i].action == GetBitFromByte(settings, i)

class TestChangeOutputSettings: 
	def setup_method(self): 
		self.menu = MenuHandler(True)
		self.menu.Update(GO_TO_SETTINGS_KEY)
		self.menu.Update(CHANGE_OUPUT_SETTINGS_KEY)

	def test_changeOutputSettings(self): 
		assert self.menu.GetCurrentMenu() == 2

		self.menu.SetMenuOption(0x0, 0)
		assert self.menu.GetOutputSettings(0)[1].action == 0
		assert self.menu.GetOutputSettings(0)[2].action == 0
		assert self.menu.GetOutputSettings(0)[3].action == 0

		self.menu.SetMenuOption(0x1, 0)
		assert self.menu.GetOutputSettings(0)[1].action == 1
		assert self.menu.GetOutputSettings(0)[2].action == 0
		assert self.menu.GetOutputSettings(0)[3].action == 0

		self.menu.SetMenuOption(0x2, 0)
		assert self.menu.GetOutputSettings(0)[1].action == 0
		assert self.menu.GetOutputSettings(0)[2].action == 1
		assert self.menu.GetOutputSettings(0)[3].action == 0

		self.menu.SetMenuOption(0x3, 0)
		assert self.menu.GetOutputSettings(0)[1].action == 1
		assert self.menu.GetOutputSettings(0)[2].action == 1
		assert self.menu.GetOutputSettings(0)[3].action == 0

		self.menu.SetMenuOption(0x1, 1)
		

		assert self.menu.GetOutputSettings(1)[1].action == 1
		assert self.menu.GetOutputSettings(1)[2].action == 0
		assert self.menu.GetOutputSettings(1)[3].action == 0

		assert self.menu.GetOutputSettings(0)[1].action == 1
		assert self.menu.GetOutputSettings(0)[2].action == 1
		assert self.menu.GetOutputSettings(0)[3].action == 0
	


		self.SetAndCheckOutputSetting(0, 0x1)

		#self.SetAndCheckOutputSetting(0, 0x00)
		#self.SetAndCheckOutputSetting(1, 0x01)
		#self.SetAndCheckOutputSetting(2, 0x02)
		#self.SetAndCheckOutputSetting(3, 0x02)

		#self.SetAndCheckOutputSetting(0, 0x0F)
		#self.SetAndCheckOutputSetting(1, 0x08)
		#self.SetAndCheckOutputSetting(2, 0x04)
		#self.SetAndCheckOutputSetting(3, 0x09)

		#self.SetAndCheckOutputSetting(0, 0x06)
		#self.SetAndCheckOutputSetting(1, 0x02)
		#self.SetAndCheckOutputSetting(2, 0x07)
		#self.SetAndCheckOutputSetting(3, 0x0D)

	def SetAndCheckOutputSetting(self, outputNumber, setting): 
		self.menu.SetMenuOption(setting, outputNumber)
		currentSetting = self.menu.GetOutputSettings(outputNumber)

		for i in range(NUMBER_OF_SETTINGS): 
			assert currentSetting[i+1].action == GetBitFromByte(setting, i)
			
 