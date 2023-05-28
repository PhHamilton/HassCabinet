from InputHandler import InputHandler

class TestMenuHandler: 
	def setup_method(self):
		self.inputHandler = InputHandler()
	
	def test_default_settings(self): 
		assert  1 == 1 