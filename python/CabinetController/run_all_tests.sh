#!/bin/bash/

HASSBOX_COMMUNICATOR_PATH='HassBoxCommunicator/test_HassBoxCommands.py';
INPUT_HANDLER_PATH='InputHandler/test_InputHandler.py';
MENU_HANDLER_PATH='MenuHandler/test_MenuHandler.py';
SERIAL_HANDLER_PATH='SerialHandler/test_SerialHandler.py';



LIST_OF_TESTS=($HASSBOX_COMMUNICATOR_PATH $INPUT_HANDLER_PATH $MENU_HANDLER_PATH $SERIAL_HANDLER_PATH)

echo "Starting test sequence.." 
echo "======================================================"
for VALUE in "${LIST_OF_TESTS[@]}"; do
    echo Testing $VALUE
    pytest -q $VALUE
done
echo "======================================================"
echo "Finished test sequence"
