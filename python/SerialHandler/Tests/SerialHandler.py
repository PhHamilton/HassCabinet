import serial 

NO_TIMEOUT = -1 

class SerialHandler(): 
	def __init__(self, serialInfo): 
		self.__serialInfo = serialInfo

		self.__serialObject = serial.Serial()

	def Open(self): 
		self.__initiateSerialPortParameters()
		self._-serialObject.open()

	def Close(self): 
		self.__serialObject.close()

	def Write(self, text):
		self.__serialObject.write(text)

	def Read(self):
		return self.__serialObject.read()

	def ReadBytes(self, nBytes): 
		return self.__serialObject.read(nBytes)

	def WriteRead(self, text): 
		self.Write(text)
		return self.Read()

	def WriteReadBytes(self, text, nBytes):
		self.Write(text)
		return self.ReadBytes(nBytes)

	def __initiateSerialPortParameters(self): 
		self.__serialObject.baudrate = self.serialInfo.GetBaudRate()
		self.__serialObject.port = self.serialInfo.GetSerialPort()
		self.__serialObject.timeout = self.serialInfo.GetTimeout()

class SerialInformation(): 
	def __init__(self, serialport, baudrate, timeout = NO_TIMEOUT):
		self.__baudrate = baudrate
		self.__serialPort = serialport
		self.__timeout = timeout

	def SetBaudrate(self, baudrate):
		self.__baudrate = baudrate

	def SetSerialPort(self, port):
		self.__serialPort = port

	def SetTimeout(self, timeout):
		self.__timeout = timeout

	def GetBaudrate(self): 
		return self.__baudrate; 
	def GetSerialPort(self): 
		return self.__serialPort
	def GetTimeout(self): 
		return self.__timeout