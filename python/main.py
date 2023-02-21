from InputHandler import InputHandler
from MenuHandler import MenuHandler

inputHandler = InputHandler() 
menu = MenuHandler() 
keyPress = None
while(keyPress != 'q'): 
    keyPress = inputHandler.WaitForKeyInput()
    menu.Update(keyPress)

