import sys 
import time 
from TerminalProgram.SerialHandler.SerialHandler import SerialHandler

nCommands = len(sys.argv) - 1
if(nCommands == 0): 
    exit() 
    
serial = SerialHandler() 
serial.Open() 
for i in range(nCommands): 
    serial.Write(bytes(str(sys.argv[i + 1]), 'utf-8'))
serial.Close() 