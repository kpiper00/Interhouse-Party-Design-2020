#!/bin/bash

# Script for flashing Bifrost boards with Arduino Uno hex files in `/bin`
#
# Arguments:
#       1:  Hex file name
#       2:  Port number (default: COM7)
#
# ASSUMES CONF FILE IN SAME DIRECTORY AS AVRDUDE


# avrdude -CC:\Users\Ray\AppData\Local\Arduino15\packages\arduino\tools\avrdude\6.3.0-arduino17/etc/avrdude.conf -v -patmega328p -carduino -PCOM7 -b115200 -D -Uflash:w:C:\Users\Ray\AppData\Local\Temp\arduino_build_10356/big-teal.ino.hex:i 

FLAGS="-p atmega328p -c arduino"
BINARY=$1
PORT=${2:-COM7}

echo "avrdude $FLAGS -P $PORT -b 115200 -D -V -U flash:w:$BINARY:i"
avrdude $FLAGS -P $PORT -b 115200 -D -V -U flash:w:$BINARY:i
