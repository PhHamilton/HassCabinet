import sys
sys.path.insert(0,'..')

from TerminalHandler.ScreenWriter import ScreenWriter
from MenuHandler.Menus import MainMenu, SettingsMenu, OutputSettingsMenu

    
class MenuHandler(): 
    def __init__(self, DISABLE_SCREENWRITER = False): 
        self.DISABLE_SCREENWRITER = DISABLE_SCREENWRITER

        self._screenWriter = ScreenWriter()
        self._currentMenu = 0
         
        self._mainMenu = MainMenu()
        self._settingsMenu = SettingsMenu() 
        self._outputSettingsMenu = OutputSettingsMenu()

        self._numberOfInputs = self._mainMenu.GetNumberOfOptions()

        if(self.DISABLE_SCREENWRITER == False):
            self._screenWriter.LoadMenu(self._mainMenu.LoadOptions())

        self._previousMenu = 0

    def SetMenuOption(self, option, outputNumber = None): 
        if(self._currentMenu == 0): 
            self._mainMenu.SetOptions(option)
        elif(self._currentMenu == 1): 
            self._settingsMenu.SetOptions(option)
        elif(self._currentMenu == 2):
            self._outputSettingsMenu.SetOptions(option, outputNumber)
        else: 
            pass 
        self.UpdateMenu()

    def Update(self, keyInput): 
        if(self.DISABLE_SCREENWRITER == False):
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
                else:
                    pass

        self.UpdateMenu() # No action, ignore all


    def UpdateMenu(self):
        if(self.DISABLE_SCREENWRITER == False):
            if(self._currentMenu == 0): 
                self._screenWriter.LoadMenu(self._mainMenu.LoadOptions())
            elif(self._currentMenu == 1): 
                self._screenWriter.LoadMenu(self._settingsMenu.LoadOptions())
            elif(self._currentMenu == 2): 
                self._screenWriter.LoadMenu(self._outputSettingsMenu.LoadOptions(self.GetCurrentOutputSetting()))
            else: 
                pass
    
    def GetCurrentMenu(self): 
        return self._currentMenu
    
    def GetCurrentOutputSetting(self): 
        return self._outputSettingsMenu.GetCurrentOutput()
    
    def GetCurrentOutputsBlinkFrequency(self):
        return self._outputSettingsMenu.GetCurretnBlinkFrequency()

    def GetOutputOptions(self): 
        return self._mainMenu.GetOptions()
    
    def GetCurrentSettings(self):
        return self._settingsMenu.GetOptions()
    
    def GetOutputSettings(self, outputNumber):
        return self._outputSettingsMenu.GetOptions(outputNumber)

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
