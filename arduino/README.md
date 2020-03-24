# Arduino Hardware

This is the documentation for the hardware and the Arduino-Software of the keyboard.

## Setting up the hardware

You'll need:

* 1x Arduino Uno
* Any amount of keys/switches (15x default)
* Any amount of [Adafruit Through-hole NeoPixels](https://please.dont-hack.me/05kqmij1rg86f.png) (15x default)
* As many [0,1µf capacitors]( https://www.adafruit.com/product/753) as you have LEDS
* As many [diodes](https://www.adafruit.com/product/755) as you have keys
* 1x [knob/potentiometer](https://www.adafruit.com/product/2047)

After you've got all of this you wire it up like this:

![](https://please.dont-hack.me/05kqmij1rg86f.png)

(Breadboard optional).

The pins of the LED have this layout:

![](https://cdn-shop.adafruit.com/1200x900/1938-05.jpg)

The longest pin of the LED is connected to ground.

If you want to connect more LEDs just connect them to +5v and Ground and plug the previous Data out into the next Data in.

If you want more keys you can add more columns and rows like shown in the first picture.

## Software

Connect your Arduino to your computer.

At first we're gonna have to clear out the EEPROM of your Arduino.

On the [official Arduino Website](https://www.arduino.cc/en/Tutorial/EEPROMClear) is a Tutorial for this.

After that's done we need to install the "Adafruit NeoPixel by Adafruit" library.

To do that, Go From the Sketch menu, > Include Library > Manage Libraries...

In the text input box type in "NeoPixel". 

Look for "Adafruit NeoPixel by Adafruit" and select the latest version by clicking on the popup menu next to the Install button. 

Then click on the Install button. After it's installed, you can click the "close" button.

After you've done that you have to edit the sketch if you added/reduced the amount of LEDs / Keys

If you added more LED's, change 

```c
#define NUMPIXELS 15
```

the 15 to the number of LEDs you have.

If you changed the data pin for the LEDs change this line:

```c
#define PIN       11
```

If you changed the pins of the rows/columns or the amount of rows/columns change these:

```c
byte rows[] = {2, 3, 4};
byte columns[] = {5, 6, 7, 8, 9};
```

to your needs.

(2, 3 and 4 being the pins for the rows.)

After you've done these changes, upload the sketch and you should be ready to go!

(On linux you could install arduino-cli and use the compile.sh and upload.sh scripts too!)

## Interaction

To see how to interact with the board through serial, read the documentation on the [mainpage](https://github.com/SagnikPradhan/the-knights/tree/feature/info#2-deep-dive).



~ sw1tchbl4d3, 24/03/2020 (dd/mm/yy)
