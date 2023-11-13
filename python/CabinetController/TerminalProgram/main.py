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

else: 
    currentOutputState = 0x5 
    currentSettings = 0x3
    currentOutputSettings.append(0x1)    
    currentOutputSettings.append(0x2)    
    currentOutputSettings.append(0x3)    
    currentOutputSettings.append(0x0)    


#Problem med att ladda inställningar! 
communicator.SetOutputSettings(currentOutputSettings)
communicator.UpdateStateOfAllOutputs(currentOutputState)
menu.SetMenuOption(currentOutputState)


outputSettings = 0x0010 #default
prevMenu = 0 
sendMsg = True

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
                communicator.ClearMessage()
                sendMsg = False
            else:
                communicator.UpdateOutputState(keyPress)
        elif(currentMenu == 1):
            if(prevMenu == 0): 
                prevMenu = 1
                communicator.ClearMessage()
                sendMsg = False
                menu.SetMenuOption(currentSettings)

            elif(prevMenu == 2):
                prevMenu = 1
                communicator.ClearMessage()
                sendMsg = False
            else:
                if(keyPress == '0'): 
                    communicator.UpdateLoggingState()
                elif(keyPress == '1'): 
                    communicator.EnableTemperatureControl()
                elif(keyPress == '3'): 
                    communicator.ResetToDefaultSettings()
                elif(keyPress == '4'):
                    sendMsg = False
                    communicator.ClearMessage()
                    
                else: 
                    sendMsg = False
                    communicator.ClearMessage()
        
        elif(currentMenu == 2):
            currentOutput = menu.GetCurrentOutputSetting()                
            if(prevMenu == 1):
                prevMenu = 2
                communicator.ClearMessage()
                sendMsg = False
                
                #for i in range(4):
                    #pass
                    #menu.SetMenuOpion(communicator.GetSettings(i), i) 
                continue
            else:  
                if(keyPress == '0'): 
                    communicator.ClearOutputNumber()
                    sendMsg = False
                elif(keyPress == '1'): 
                    communicator.UpdateOutputAvailability(currentOutput)
                elif(keyPress == '2'):
                    communicator.UpdateLedAvailability(currentOutput)
                elif(keyPress == '3'): 
                    communicator.UpdateBlinkFrequency(currentOutput, menu.GetCurrentOutputsBlinkFrequency())
                elif(keyPress == '4'):
                    communicator.ResetToDefaultOutputSettings()
                else: 
                    sendMsg = False
                    communicator.ClearMessage() 
                    pass

            communicator.UpdateOutputSettings(currentOutput)
        else: 
            pass
        
    if(currentMenu == 0):
        strval = format(communicator.GetOutputState(), '#06x')
    else:
        strval = format(communicator.GetSettings(menu.GetCurrentOutputSetting()), '#06x')

    if(DISABLE_SERIAL == False and sendMsg == True):
        serialHandler.Write(bytes(strval, 'utf-8'))
    if(sendMsg == True):
        print(strval)
    if(sendMsg == False): 
        sendMsg = True
    #elif(currentMenu == 1 and keyPress != 'q' and menu._isValid(keyPress)): 
if(DISABLE_SERIAL == False):
    serialHandler.Close()

