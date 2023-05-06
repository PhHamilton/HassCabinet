OFF = 0
ON = 1 
NUMBER_OF_OUTPUTS = 4

class Options(): 
    def __init__(self, name, action):
        self.name = name
        self.action = action  

class MainMenu(): 
    def __init__(self):
        self._defaultAction = OFF
        self._Options = list()
        for i in range(NUMBER_OF_OUTPUTS): 
            self._Options.append(Options(self.GetText(self._defaultAction, i), self._defaultAction))
        self._Options.append(Options("Settings", 1))
        
    
    def LoadOptions(self):
        return self._Options
    
    def UpdateOption(self, OptionNumber):
        if(self._Options[OptionNumber].action == OFF): 
            self._Options[OptionNumber].action = ON
            self._Options[OptionNumber].name = self.GetText(ON, OptionNumber)
        else: 
            self._Options[OptionNumber].action = OFF
            self._Options[OptionNumber].name = self.GetText(OFF, OptionNumber)
    
    def GetNumberOfOptions(self): 
        return len(self._Options) - 1

    def GetText(self, action, relayNumber): 
        if(action == ON): nextState = "off"
        else: nextState = "on "
        return "Turn " + nextState + " relay " + str(relayNumber + 1)

class SettingsMenu(): 
    def __init__(self):
        self._nListItems = 1; 
        self._defaultAction = 0
        self._Options = list()
        self._Options.append(Options("Start logging", self._defaultAction))
        self._Options.append(Options("Enable automatic cooling", self._defaultAction))
        self._Options.append(Options("Return to main menu", self._defaultAction))
    
    def LoadOptions(self):
        return self._Options
        
    def GetNumberOfOptions(self): 
        return len(self._Options) - 1
    
    def UpdateOption(self, OptionNumber): 
        if(OptionNumber == 0):
            if(self._Options[OptionNumber].action == 0): 
                self._Options[OptionNumber].action = 1
                self._Options[OptionNumber].name = self.GetLoggingText(1, OptionNumber)
            else: 
                self._Options[OptionNumber].action = 0
                self._Options[OptionNumber].name = self.GetLoggingText(0, OptionNumber)
        else: 
            if(self._Options[OptionNumber].action == 0): 
                self._Options[OptionNumber].action = 1
                self._Options[OptionNumber].name = self.GetCoolingText(1, OptionNumber)
            else: 
                self._Options[OptionNumber].action = 0
                self._Options[OptionNumber].name = self.GetCoolingText(0, OptionNumber)
    
    def GetLoggingText(self, action, relayNumber): 
        if(action == 1): nextState = "Stop"
        else: nextState = "Start"
        return nextState + " logging"
    
    def GetCoolingText(self, action, relayNumber): 
        if(action == 1): nextState = "Disable"
        else: nextState = "Enable"
        return nextState + " automatic cooling"