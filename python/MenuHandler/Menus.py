OFF = 0
ON = 1 
NUMBER_OF_OUTPUTS = 4
NUMBER_OF_SETTINGS = 2 
NUMBER_OF_OUTPUT_SETTINGS = 3
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
    
    def GetOptions(self): 
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
        self._defaultAction = 0
        self._Options = list()
        self._Options.append(Options("Start logging", self._defaultAction))
        self._Options.append(Options("Enable automatic cooling", self._defaultAction))
        self._Options.append(Options("Change output settings", self._defaultAction))
        self._Options.append(Options("Reset to default settings" , self._defaultAction))
        self._Options.append(Options("Return to main menu", self._defaultAction))
    
    def LoadOptions(self):
        return self._Options
    
    def SetOptions(self, options): 
        for i in range(NUMBER_OF_SETTINGS): 
            if((int(options) >> int(i)) & 1):
                self._Options[i].action = ON
                if(i == 0):
                    self._Options[i].name = self.GetLoggingText(ON, i)
                elif(i == 1): 
                    self._Options[i].name = self.GetCoolingText(ON, i)
                else: 
                    pass
            else: 
                self._Options[i].action = OFF
                if(i == 0):
                    self._Options[i].name = self.GetLoggingText(OFF, i)
                elif(i == 1): 
                    self._Options[i].name = self.GetCoolingText(OFF, i)
                else: 
                    pass

    def GetOptions(self): 
        return self._Options
        
    def GetNumberOfOptions(self): 
        return len(self._Options) - 1
    
    def UpdateOption(self, OptionNumber): 
        if(OptionNumber == 0):
            if(self._Options[OptionNumber].action == 0): 
                self._Options[OptionNumber].action = ON
                self._Options[OptionNumber].name = self.GetLoggingText(1, OptionNumber)
            else: 
                self._Options[OptionNumber].action = OFF
                self._Options[OptionNumber].name = self.GetLoggingText(0, OptionNumber)
        elif(OptionNumber == 1): 
            if(self._Options[OptionNumber].action == 0): 
                self._Options[OptionNumber].action = ON
                self._Options[OptionNumber].name = self.GetCoolingText(1, OptionNumber)
            else: 
                self._Options[OptionNumber].action = OFF
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
        self._currentOutputNumber = 0
        self._currentBlinkFrequency = [0, 0, 0, 0]
        self._OutputOptions = []
        self._Options0 = list()
        self._Options0.append(Options("Change Output Number (Current output: {})".format(self._currentOutputNumber), self._defaultAction))
        self._Options0.append(Options("Disable output", self._defaultAction))
        self._Options0.append(Options("Disable led", self._defaultAction))
        self._Options0.append(Options("Update blink frequency (Current: {} Hz)".format(self._currentBlinkFrequency[0]), self._defaultAction))
        self._Options0.append(Options("Reset to default output settings", self._defaultAction))
        self._Options0.append(Options("Return to settings", self._defaultAction))


        self._Options1 = list()
        self._Options1.append(Options("Change Output Number (Current output: {})".format(self._currentOutputNumber), self._defaultAction))
        self._Options1.append(Options("Disable output", self._defaultAction))
        self._Options1.append(Options("Disable led", self._defaultAction))
        self._Options1.append(Options("Update blink frequency (Current: {} Hz)".format(self._currentBlinkFrequency[1]), self._defaultAction))
        self._Options1.append(Options("Reset to default output settings", self._defaultAction))
        self._Options1.append(Options("Return to settings", self._defaultAction))

        self._Options2 = list()
        self._Options2.append(Options("Change Output Number (Current output: {})".format(self._currentOutputNumber), self._defaultAction))
        self._Options2.append(Options("Disable output", self._defaultAction))
        self._Options2.append(Options("Disable led", self._defaultAction))
        self._Options2.append(Options("Update blink frequency (Current: {} Hz)".format(self._currentBlinkFrequency[2]), self._defaultAction))
        self._Options2.append(Options("Reset to default output settings", self._defaultAction))
        self._Options2.append(Options("Return to settings", self._defaultAction))


        self._Options3 = list()
        self._Options3.append(Options("Change Output Number (Current output: {})".format(self._currentOutputNumber), self._defaultAction))
        self._Options3.append(Options("Disable output", self._defaultAction))
        self._Options3.append(Options("Disable led", self._defaultAction))
        self._Options3.append(Options("Update blink frequency (Current: {} Hz)".format(self._currentBlinkFrequency[3]), self._defaultAction))
        self._Options3.append(Options("Reset to default output settings", self._defaultAction))
        self._Options3.append(Options("Return to settings", self._defaultAction))


        self._OutputOptions.append(self._Options0)
        self._OutputOptions.append(self._Options1)
        self._OutputOptions.append(self._Options2)
        self._OutputOptions.append(self._Options3)

    
    def LoadOptions(self, outputNumber):
        return self.GetOptions(outputNumber)
    
    def SetOptions(self, options, outputNumber): 
        for i in range(NUMBER_OF_OUTPUT_SETTINGS):
            self._OutputOptions[outputNumber][i+1].action = (int(options) >> int(i)) & 1
            
            if(i == 0):
                txt = self.GetEnableText(int(options) >> int(i), " output")
            elif(i == 1):
                txt = self.GetEnableText(int(options) >> int(i), " led")
            else:
                self._currentBlinkFrequency[outputNumber] = (int(options) >> int(i)) + 2*(int(options) >> int(i) & 1)
                txt = "Update blink frequency (Current: {} Hz)".format(self._currentBlinkFrequency[outputNumber])
            
            self._OutputOptions[outputNumber][i+1].name = txt


    def GetOptions(self, outputNumber): 
        return self._OutputOptions[outputNumber]
        
    def GetNumberOfOptions(self): 
        return len(self._Options0) - 1
    
    def UpdateOption(self, OptionNumber): 
        if(OptionNumber == 0): 
            self._currentOutputNumber += 1
            if(self._currentOutputNumber >= NUMBER_OF_OUTPUTS):
               self._currentOutputNumber = 0
            self._OutputOptions[self._currentOutputNumber][OptionNumber].name = "Change Output Number (Current output: {})".format(self._currentOutputNumber)

        elif(OptionNumber == 1):
            if(self._OutputOptions[self._currentOutputNumber][OptionNumber].action == 0): 
                self._OutputOptions[self._currentOutputNumber][OptionNumber].action = 1
                self._OutputOptions[self._currentOutputNumber][OptionNumber].name = self.GetEnableText(1, " output")
            else: 
                self._OutputOptions[self._currentOutputNumber][OptionNumber].action = 0
                self._OutputOptions[self._currentOutputNumber][OptionNumber].name = self.GetEnableText(0, " output")
        elif(OptionNumber == 2): 
            if(self._OutputOptions[self._currentOutputNumber][OptionNumber].action == 0): 
                self._OutputOptions[self._currentOutputNumber][OptionNumber].action = 1
                self._OutputOptions[self._currentOutputNumber][OptionNumber].name = self.GetEnableText(1, " led")
            else: 
                self._OutputOptions[self._currentOutputNumber][OptionNumber].action = 0
                self._OutputOptions[self._currentOutputNumber][OptionNumber].name = self.GetEnableText(0, " led")
        elif(OptionNumber == 3): 
            self._currentBlinkFrequency[self._currentOutputNumber] += 1
            if(self._currentBlinkFrequency[self._currentOutputNumber] > MAXIMUM_BLINK_FREQUENCY):
               self._currentBlinkFrequency[self._currentOutputNumber] = 0
            self._OutputOptions[self._currentOutputNumber][OptionNumber].name = "Update blink frequency (Current: {} Hz)".format(self._currentBlinkFrequency[self._currentOutputNumber])
        else: 
            pass

    def GetEnableText(self, action, type): 
        if(action == 1): nextState = "Disable"
        else: nextState = "Enable"
        return nextState + type
    
    def GetCurrentOutput(self):
        return self._currentOutputNumber
    def GetCurretnBlinkFrequency(self): 
        return self._currentBlinkFrequency[self._currentOutputNumber]

    