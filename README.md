# Audio-Spectrum-Analyzer

An embedded project containing an ESP32 microcontroller that uses an electret microphone to read audio and an SSD1306 OLED panel to output audio frequency readings. It uses an non-inverting op amp and high pass filter with a DC Bias to amplify microphone readings and clean noise before being read by the microphone.

## Components:
* ESP32
* Electret Microphone
* SSD1306 OLED panel
* TL081CP Operational Amplifier IC
* R1 6k ohms
* R2 200k ohms
* R3 200k ohms
* R4 1k ohms
* R5 10k ohm
* R6 10k ohm
* C1 330 Micro Farad
* C2 47 Micro Farad
* C3 120 Pico Farad
* Breadboard
* Jumper Wires

The design took inspiration from the following schematic, but we made a few minor modifications: https://www.ti.com/lit/an/sboa290a/sboa290a.pdf?ts=1785880552560

Particularly, we decided to omit the resistor R6 and the capacitor C4 from the design, because they removed the 1.65V DC offset required by the ESP32 to properly read the sound waves.

## Pins
25 - AnalogRead

## Libraries used:
U8G2 library for monochrome displays
