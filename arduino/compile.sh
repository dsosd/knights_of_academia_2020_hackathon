#!/bin/sh
arduino-cli config init
rm -rf ~/.arduino15/package_index.json
rm -rf build
wget https://downloads.arduino.cc/packages/package_index.json -P ~/.arduino15/
arduino-cli core install arduino:avr
arduino-cli lib install "Adafruit NeoPixel"
arduino-cli compile --fqbn arduino:avr:uno main.ino
mkdir build
mv main.ino.arduino.avr.uno.elf build/build.arduino.avr.uno.elf
mv main.ino.arduino.avr.uno.hex build/build.arduino.avr.uno.hex
mv main.ino.arduino.avr.uno.with_bootloader.hex build/build.arduino.avr.uno.with_bootloader.hex
