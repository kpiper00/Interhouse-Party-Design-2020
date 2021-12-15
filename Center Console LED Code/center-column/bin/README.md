# Binaries

This directory contains binary (`.hex`) files compiled for the Bifrost RGB LED controller.

All files should be compiled using the Arduino Uno bootloader. Although Bifrost uses the Arduino Nano, the bootloader on the Nano should be replaced with the Uno bootloader, which is smaller in size.

To implement remote programming, a Raspberry Pi or similar remote server should be set up to flash the Bifrost Arduino Nano with these binaries with AVRDUDE.
