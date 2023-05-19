import sys
sys.path.insert(0,'..')

from TerminalHandler.ScreenWriter import ScreenWriter
from MenuHandler.Menus import MainMenu, SettingsMenu, OutputSettingsMenu

    
class MenuHandler(): 
    def __init__(self): 
        self._screenWriter = ScreenWriter()
        self._currentMenu = 0
         
        self._mainMenu = MainMenu()
        self._settingsMenu = SettingsMenu() 
        self._outputSettingsMenu = OutputSettingsMenu()

        self._numberOfInputs = self._mainMenu.GetNumberOfOptions()
        self._screenWriter.LoadMenu(self._mainMenu.LoadOptions())

        self._previousMenu = 0

    def UpdateMenuOption(self, option): 
        if(self._currentMenu == 0): 
            self._mainMenu.SetOptions(option)
        elif(self._currentMenu == 1): 
            pass
        elif(self._currentMenu == 2):
            pass
        else: 
            pass 

    def Update(self, keyInput): 
        self._screenWriter.ClerScreen()
        if(self._isValid(keyInput)):
            if(keyInput == 'q'):
                return

            if(int(keyInput) == self._numberOfInputs): 
                self._changeMenu()
            else: 
                if(self._currentMenu == 0): 
                    self._mainMenu.UpdateOption(int(keyInput))
                elif(self._currentMenu == 1):
                    self._settingsMenu.UpdateOption(int(keyInput))
                    if(keyInput == '2'):
                        self._currentMenu = 2
                elif(self._currentMenu == 2):
                    self._outputSettingsMenu.UpdateOption(int(keyInput))
                    print(self._numberOfInputs)
                else:
                    pass

        self.UpdateMenu() # No action, ignore all


    def UpdateMenu(self):
        if(self._currentMenu == 0): 
            self._screenWriter.LoadMenu(self._mainMenu.LoadOptions())
        elif(self._currentMenu == 1): 
            self._screenWriter.LoadMenu(self._settingsMenu.LoadOptions())
        elif(self._currentMenu == 2): 
            self._screenWriter.LoadMenu(self._outputSettingsMenu.LoadOptions())
        else: 
            pass
    
    def GetCurrentMenu(self): 
        return self._currentMenu
    def GetCurrentOutputSetting(self): 
        return self._outputSettingsMenu.GetCurrentOutput()
    def GetCurrentOutputsBlinkFrequency(self):
        return self._outputSettingsMenu.GetCurretnBlinkFrequency()

    def _changeMenu(self): 
        if(self._currentMenu == 0):
            self._currentMenu = 1
        elif(self._currentMenu == 1):
            self._currentMenu = 0
        elif(self._currentMenu == 2): 
            self._currentMenu = 1
        else: 
            pass

    def _isValid(self, keyPress) -> bool: 
        if(keyPress.isdigit()):
            self._numberOfInputs = self._getNumberOfInputs()
            return not int(keyPress) > self._numberOfInputs
        else: 
            return keyPress == 'q'

    def _getNumberOfInputs(self) -> int:
        if(self._currentMenu == 0): 
            return self._mainMenu.GetNumberOfOptions()
        elif(self._currentMenu == 1): 
            return self._settingsMenu.GetNumberOfOptions()
        else: 
            return self._outputSettingsMenu.GetNumberOfOptions()
