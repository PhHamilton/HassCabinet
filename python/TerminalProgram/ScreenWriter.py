from Terminal import Terminal
from HeaderAndFooter import HeaderAndFooter

class ScreenWriter(): 
    def __init__(self): 
        self._terminal = Terminal() 
        self._headers = HeaderAndFooter()
        self._currentMenu = 0 


    def UpdateCurrentMenu(self, currentMenu): 
        self._currentMenu = currentMenu
    
    def GetCurrentMenu(self): 
        return self._currentMenu
    
    def LoadMenu(self, menus):
        self._terminal.ClearScreen()
        self._terminal.Write(self._headers.GetHeader())
        i = 0
        for menu in menus:  
            self._terminal.Write(str(i) + ") " + menu.name)
            i += 1 
            
            
        self._terminal.Write(self._headers.GetFooter())
    def ClerScreen(self):
        self._terminal.ClearScreen()

if __name__ == "__main__":
    test = ScreenWriter()
    test.LoadMenu()

        


