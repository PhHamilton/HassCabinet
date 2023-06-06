#!/bin/bash

echo "Transferring python scripts" 

scp -r python shell pi@192.168.1.209:/home/pi/scripts/

echo "Transfer complete"
