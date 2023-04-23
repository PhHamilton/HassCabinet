from SerialHandler import SerialInformation, NO_TIMEOUT

class TestSerialInfo: 
	def setup_method(self):
		self.port = "/dev/USB0"
		self.baudrate = 9600
		self.serialInfo = SerialInformation(self.port, self.baudrate)
	
	def test_GetBaudRate(self): 
		assert  self.serialInfo.GetBaudrate() == self.baudrate

	def test_UpdateBaudrate(self): 
		baudrate = 115200
		self.serialInfo.SetBaudrate(baudrate)

		assert self.serialInfo.GetBaudrate() == baudrate
	
	def test_GetSerialPort(self): 
		assert self.serialInfo.GetSerialPort() == self.port

	def test_UpdateSerialPort(self): 
		port = "/dev/USB1"
		self.serialInfo.SetSerialPort(port)

		assert self.serialInfo.GetSerialPort() == port

	
	def test_GetDefaultTimeout(self): 
		assert self.serialInfo.GetTimeout() == NO_TIMEOUT

	def test_GetTimeout(self): 
		timeout = 10
		self.serialInfo.SetTimeout(timeout)

		assert self.serialInfo.GetTimeout() == timeout
