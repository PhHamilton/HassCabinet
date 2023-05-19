import sys 
sys.path.insert(0,'..')

from InputHandler.InputHandler import InputHandler
from MenuHandler.MenuHandler import MenuHandler

from HassBoxCommunicator.HassBoxCommands import HassBoxCommunicator
from SerialHandler.SerialHandler import SerialHandler

DISABLE_SERIAL = True

inputHandler = InputHandler() 
menu = MenuHandler() 
communicator = HassBoxCommunicator()

currentOutputState = None
currentOutputSettings = []

if(DISABLE_SERIAL == False):
    serialHandler = SerialHandler()
    serialHandler.Open()

    currentOutputState = serialHandler.WriteReadBytes(b'0xF000', 1)
    currentOutputSettings.append(serialHandler.WriteReadBytes(b'0xE000', 1))    
    currentOutputSettings.append(serialHandler.WriteReadBytes(b'0xD000', 1))    
    currentOutputSettings.append(serialHandler.WriteReadBytes(b'0xB000', 1))    
    currentOutputSettings.append(serialHandler.WriteReadBytes(b'0x7000', 1))    
else: 
    currentOutputState = 0x5 
    currentOutputSettings.append(5)    
    currentOutputSettings.append(5)    
    currentOutputSettings.append(5)    
    currentOutputSettings.append(5)  
  
menu.UpdateMenuOption(currentOutputState)



outputSettings = 0x0010 #default
prevMenu = 0 

keyPress = None
while(keyPress != 'q'): 
    keyPress = inputHandler.WaitForKeyInput()
    
    menu.Update(keyPress)
    currentMenu = menu.GetCurrentMenu()

    if(keyPress == 'q'): 
        continue 
    else:
        if(currentMenu == 0):
            if(prevMenu == 1):
                prevMenu = 0
            else:
                communicator.UpdateOutputState(keyPress)
        elif(currentMenu == 1):
            if(prevMenu == 0): 
                prevMenu = 1
            elif(prevMenu == 2):
                prevMenu == 1
            else:
                if(keyPress == '0'): 
                    communicator.UpdateLoggingState()
                elif(keyPress == '1'): 
                    communicator.EnableTemperatureControl()
                elif(keyPress == '2'): 
                    communicator.ResetToDefaultSettings()
                else: 
                    pass
        
        elif(currentMenu == 2):
            currentOutput = menu.GetCurrentOutputSetting()
            if(currentMenu == 1):
                prevMenu = 2
            else: 
                if(keyPress == '0'): 
                    communicator.ClearOutputNumber()
                elif(keyPress == '1'): 
                    communicator.UpdateOutputAvailability()
                elif(keyPress == '2'):
                    communicator.UpdateLedAvailability()
                elif(keyPress == '3'): 
                    communicator.UpdateBlinkFrequency(menu.GetCurrentOutputsBlinkFrequency())
                elif(keyPress == '4'):
                    communicator.ResetToDefaultOutputSettings()
                else: 
                    pass

            communicator.UpdateOutputSettings(currentOutput)

        else: 
            pass
        

    strval = format(communicator.GetOutputState(), '#06x')
    if(DISABLE_SERIAL == False):
        serialHandler.Write(bytes(strval, 'utf-8'))
    #elif(currentMenu == 1 and keyPress != 'q' and menu._isValid(keyPress)): 
    #    
if(DISABLE_SERIAL == False):
    serialHandler.Close()

