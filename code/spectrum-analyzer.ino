#include <Wire.h>
#include <U8g2lib.h>
#include "arduinoFFT.h"

// OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


// this calls from the u8g2 library to use the ssd1306 driver on a 128x64 pixel screen
// with default name (NONAME), full (F) memory buffer, and speak on hardware I2C (HW_I2C)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled(U8G2_R0, U8X8_PIN_NONE);

const int MIC_PIN = 32;

//=========== fft Parameters ================
const uint16_t samples = 128; // must be a power of 2
const double samplingFrequency = 10000;

unsigned int sampling_period_us;
unsigned long microseconds;

/*
 * fft requires two arrays:
 * vReal contains the actual audio values
 * vImag is used for the math
 */
double vReal[samples];
double vImag[samples];

// NOTE: requires arduinoFFT version >= 2.0
// makes an instance of arduinoFFT called fft. this is what does all the math.
ArduinoFFT<double> fft = ArduinoFFT<double>(vReal, vImag, samples, samplingFrequency);


void setup() {
  sampling_period_us = round(1000000.0 / samplingFrequency);

  // initialize OLED
  oled.begin();

  oled.clearBuffer();
  oled.sendBuffer();
}


void loop() {

  // sample the microphone
  for (int i = 0; i < samples; i++) {

    microseconds = micros();

    vReal[i] = analogRead(MIC_PIN);
    vImag[i] = 0;

    // wait until exact sampling period has passed
    while (micros() - microseconds < sampling_period_us) {
      //empty loop
    }
  }

  // perform fft
  fft.dcRemoval();                                  // removes the DC offset from the microphone
  fft.windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);  // smooths the data edges
  fft.compute(FFT_FORWARD);                         // runs the actual math
  fft.complexToMagnitude();                         // converts complex numbers to raw magnitude (basically, the volume)

  // draw to the oled
  oled.clearBuffer();

  // fft mirrors data, so we only need the first half (samples/2)
  // we start at i = 2 because indices 0 and 1 represent the DC offset and low noise.
  for (int i = 2; i < (samples / 2); i++) {

    // map fft magnitude to screen height
    // NOTE: the "100" is a number that should be tuned based on the signal from the microphone
    int barHeight = map(vReal[i], 0, 100, 0, SCREEN_HEIGHT);

    // makes sure it does not write to a non existent location   
    barHeight = constrain(barHeight, 0, SCREEN_HEIGHT);

    //2 pixels per frequency band. there are 60 bands so it fits pretty nicely on 128 px
    int xPos = (i - 2) * 2;

    // draw the bar
    oled.drawBox(xPos, SCREEN_HEIGHT - barHeight, 2, barHeight);
  }
  //write full buffer to screen
  oled.sendBuffer();
}
