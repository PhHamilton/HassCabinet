class InputHandler(): 
    def __init__(self): 
        self.prevCharacter = 0

    def WaitForKeyInput(self):
        currentInput = input()
        if not self._isValid(currentInput):
            return self.prevCharacter
        
        self.prevCharacter = currentInput
        return currentInput

    def _isValid(self, currentInput): 
        return True
