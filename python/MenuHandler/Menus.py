OFF = 0
ON = 1 
NUMBER_OF_OUTPUTS = 4
MAXIMUM_BLINK_FREQUENCY = 3

def getBit(bit): 
    return bit 

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
    
    def SetOptions(self, options): 
        for i in range(NUMBER_OF_OUTPUTS): 
            if((int(options) >> int(i)) & 1):
                self._Options[i].action = ON
                self._Options[i].name = self.GetText(ON, i)
            else: 
                self._Options[i].action = OFF
                self._Options[i].name = self.GetText(OFF, i)
            

    
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
        self._defaultAction = 0
        self._Options = list()
        self._Options.append(Options("Start logging", self._defaultAction))
        self._Options.append(Options("Enable automatic cooling", self._defaultAction))
        self._Options.append(Options("Change output settings", self._defaultAction))
        self._Options.append(Options("Reset to default settings" , self._defaultAction))
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
        elif(OptionNumber == 1): 
            if(self._Options[OptionNumber].action == 0): 
                self._Options[OptionNumber].action = 1
                self._Options[OptionNumber].name = self.GetCoolingText(1, OptionNumber)
            else: 
                self._Options[OptionNumber].action = 0
                self._Options[OptionNumber].name = self.GetCoolingText(0, OptionNumber)
        elif(OptionNumber == 2): 
            pass
        else: 
            pass
    def GetLoggingText(self, action, relayNumber): 
        if(action == 1): nextState = "Stop"
        else: nextState = "Start"
        return nextState + " logging"
    
    def GetCoolingText(self, action, relayNumber): 
        if(action == 1): nextState = "Disable"
        else: nextState = "Enable"
        return nextState + " automatic cooling"
    
class OutputSettingsMenu():
    def __init__(self):
        self._defaultAction = 1
        self._currentOutputNumber = 1
        self._currentBlinkFrequency = 0
        self._Options = list()
        self._Options.append(Options("Change Output Number (Current output: {})".format(self._currentOutputNumber), self._defaultAction))
        self._Options.append(Options("Disable output", self._defaultAction))
        self._Options.append(Options("Disable led", self._defaultAction))
        self._Options.append(Options("Update blink frequency (Current: {} Hz)".format(self._currentBlinkFrequency), self._defaultAction))
        self._Options.append(Options("Reset to default output settings", self._defaultAction))
        self._Options.append(Options("Return to settings", self._defaultAction))
    
    def LoadOptions(self):
        return self._Options
        
    def GetNumberOfOptions(self): 
        return len(self._Options) - 1
    
    def UpdateOption(self, OptionNumber): 
        if(OptionNumber == 0): 
            self._currentOutputNumber += 1
            if(self._currentOutputNumber > NUMBER_OF_OUTPUTS):
               self._currentOutputNumber = 1
            self._Options[OptionNumber].name = "Change Output Number (Current output: {})".format(self._currentOutputNumber)

        elif(OptionNumber == 1):
            if(self._Options[OptionNumber].action == 0): 
                self._Options[OptionNumber].action = 1
                self._Options[OptionNumber].name = self.GetEnableText(1, " output")
            else: 
                self._Options[OptionNumber].action = 0
                self._Options[OptionNumber].name = self.GetEnableText(0, " output")
        elif(OptionNumber == 2): 
            if(self._Options[OptionNumber].action == 0): 
                self._Options[OptionNumber].action = 1
                self._Options[OptionNumber].name = self.GetEnableText(1, " led")
            else: 
                self._Options[OptionNumber].action = 0
                self._Options[OptionNumber].name = self.GetEnableText(0, " led")
        elif(OptionNumber == 3): 
            self._currentBlinkFrequency += 1
            if(self._currentBlinkFrequency > MAXIMUM_BLINK_FREQUENCY):
               self._currentBlinkFrequency = 0
            self._Options[OptionNumber].name = "Update blink frequency (Current: {} Hz)".format(self._currentBlinkFrequency)
        else: 
            pass

    def GetEnableText(self, action, type): 
        if(action == 1): nextState = "Disable"
        else: nextState = "Enable"
        return nextState + type
    
    def GetCurrentOutput(self):
        return self._currentOutputNumber
    def GetCurretnBlinkFrequency(self): 
        return self._currentBlinkFrequency

    