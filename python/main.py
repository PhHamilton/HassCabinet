import sys 
import time
sys.path.insert(0,'..')

from InputHandler.InputHandler import InputHandler
from MenuHandler.MenuHandler import MenuHandler

from HassBoxCommunicator.HassBoxCommands import HassBoxCommunicator
from SerialHandler.SerialHandler import SerialHandler

DISABLE_SERIAL = False

inputHandler = InputHandler() 
menu = MenuHandler() 
communicator = HassBoxCommunicator()

currentOutputState = None
currentSettings = 0x00
currentOutputSettings = []

if(DISABLE_SERIAL == False):
    serialHandler = SerialHandler()
    serialHandler.Open()

    currentOutputState = serialHandler.WriteReadBytes(b'0xF000', 1)
#    print(currentOutputState)
    currentOutputSettings.append(serialHandler.WriteReadBytes(b'0xE000', 1))    
    currentOutputSettings.append(serialHandler.WriteReadBytes(b'0xD000', 1))    
    currentOutputSettings.append(serialHandler.WriteReadBytes(b'0xB000', 1))    
    currentOutputSettings.append(serialHandler.WriteReadBytes(b'0x7000', 1))    

#    for i in range(len(currentOutputSettings)):
#        print(currentOutputSettings[i])
#    while(1):
#        pass

    communicator.UpdateOutputSettings
else: 
    currentOutputState = 0x5 
    currentSettings = 0x3
    currentOutputSettings.append(0x0)    
    currentOutputSettings.append(0x4)    
    currentOutputSettings.append(0x9)    
    currentOutputSettings.append(0xE)    

#Problem med att ladda inställningar! 

menu.SetMenuOption(currentOutputState)


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
                menu.SetMenuOption(currentSettings)

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
            
            if(prevMenu == 1):
                prevMenu = 2
                for i in range(4):
                    menu.SetMenuOption(currentOutputSettings[i], i) 
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

