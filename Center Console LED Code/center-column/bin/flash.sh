#!/bin/bash

# Script for flashing Bifrost boards with Arduino Uno hex files in `/bin`
#
# Arguments:
#       1:  Hex file name
#       2:  Port number (default: /dev/ttyUSB0)


# avrdude -C /usr/share/arduino/hardware/tools/avrdude.conf -p atmega328p -c arduino -P /dev/ttyUSB0 -b115200 -D -U flash:w:/tmp/build11897768143811812786.tmp.Blink.cpp.hex:i

FLAGS="-C /usr/share/arduino/hardware/tools/avrdude.conf -p atmega328p -c arduino"
BINARY=$1
PORT=${2:-/dev/ttyUSB0}

echo "avrdude $FLAGS -P $PORT -b 115200 -D -V -U flash:w:$BINARY:i"
avrdude $FLAGS -P $PORT -b 115200 -D -V -U flash:w:$BINARY:i
