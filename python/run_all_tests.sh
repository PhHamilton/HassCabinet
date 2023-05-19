#!/bin/bash/


pytest -q HassBoxCommunicator/test_HassBoxCommands.py

pytest -q InputHandler/test_InputHandler.py
pytest -q MenuHandler/test_MenuHandler.py
pytest -q SerialHandler/test_SerialHandler.py