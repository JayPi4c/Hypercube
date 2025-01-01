# Hypercube on Arduino

This project ports the coding train [Hypercube](https://github.com/CodingTrain/Coding-Challenges/tree/main/113_Hypercube) project to Arduino.


A demo video can be found [here](https://www.youtube.com/watch?v=ZFF1CO1Ako0)

## Hardware
- [Display](https://www.waveshare.com/1.51inch-transparent-oled.htm)
- [Wemos D1 Mini](https://amzn.eu/d/3VorcY7)

NOTE: these are no affiliate links. It's just for you to know what products I used. You can use any other display and microcontroller from other sellers as well.

## Libraries
- [BasicLinearAlgebra](https://www.arduino.cc/reference/en/libraries/basiclinearalgebra/) for matrix operations
- ([Waveshare OLED Library](https://www.waveshare.com/wiki/1.51inch_Transparent_OLED#Resource) for the display)
- A custom adaptation of the Waveshare OLED library can be downloaded cloned here: https://github.com/JayPi4c/1.51inch-Transparent-OLED-Arduino-library

The Waveshare OLED library is not available in the Arduino IDE library manager. You have to download it from the link above and install it manually. Additionally the library did not work out of the box for the wemos microcontroller. So I adjusted it accordingly. That also explains, why the included OLED-library has the WEMOS postfix.

## Other information
As mentioned previously, any display can be used. All you need is a library to draw lines on the display. The used display has a resolution of 128x64 pixels. I will add a tutorial of the places to be changed for another display.