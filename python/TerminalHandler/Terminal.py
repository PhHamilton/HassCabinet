from os import system, name 

class Terminal(): 
    def __init__(self): 
        pass
    def Write(self, text):
        print(text)
    def ClearScreen(self): 
        if(name == "nt"): # WindowsUser
            _ = system("cls")
        else: # Linux or Mac user
            _ = system("clear")

if __name__ == "__main__": 
    terminalObject = Terminal(); 
    