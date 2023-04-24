from ScreenWriter import ScreenWriter
from Menus import MainMenu, SettingsMenu, Options

    
class MenuHandler(): 
    def __init__(self): 
        self._screenWriter = ScreenWriter()
        self._currentMenu = 0
         
        self._mainMenu = MainMenu()
        self._settingsMenu = SettingsMenu() 

        self._numberOfInputs = self._mainMenu.GetNumberOfOptions()
        self._screenWriter.LoadMenu(self._mainMenu.LoadOptions())


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
                else:
                    self._settingsMenu.UpdateOption(int(keyInput))


        self.UpdateMenu() # No action, ignore all


    def UpdateMenu(self):
        if(self._currentMenu == 0): 
            self._screenWriter.LoadMenu(self._mainMenu.LoadOptions())
        else: 
            self._screenWriter.LoadMenu(self._settingsMenu.LoadOptions())

    def _changeMenu(self): 
        if(self._currentMenu == 0):
            self._currentMenu = 1
        else:
            self._currentMenu = 0

    def _isValid(self, keyPress) -> bool: 
        if(keyPress.isdigit()):
            self._numberOfInputs = self._getNumberOfInputs()
            return not int(keyPress) > self._numberOfInputs
        else: 
            return keyPress == 'q'

    def _getNumberOfInputs(self) -> int:
        if(self._currentMenu == 0): return self._mainMenu.GetNumberOfOptions()
        else: return self._settingsMenu.GetNumberOfOptions()
