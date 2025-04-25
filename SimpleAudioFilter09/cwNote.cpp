
#include "cwNote.h"
#include <I2S.h>

const int frequency = 1000;  // frequency of square wave in Hz
const int amplitude = 2000;  // amplitude of square wave

const int sampleRate = 8000;
const int halfWavelength = (sampleRate / frequency);  // half wavelength of square wave

//definimos los leds para indicar el estado
#define LED_FILTER_1 5  // SSB WIDE
#define LED_FILTER_2 6  // SSB NARROW
#define LED_FILTER_3 7  // CW WIDE
#define LED_FILTER_4 8  // CW NARROW

#define LED_NOISE_1 9   // DNR DENOISE LEVEL 1
#define LED_NOISE_2 10  // DNR DENOISE LEVEL 2


I2S i2s_;

void setI2s(const I2S &i2sIn) {
  i2s_ = i2sIn;
}

void playDith() {
  playTone(1);
}

void playDash() {
  playTone(4);
}

void playDelay() {
  delay(100);
}


void playTone(int mult) {

  int16_t sample = amplitude;  // current sample value
  int count = 0;

  for (int i = 1; i <= (360 * mult); i++) {

    if (count % halfWavelength == 0) {
      // invert the sample every half wavelength count multiple to generate square wave
      sample = -1 * sample;
    }

    // write the same sample twice, once for left and once for the right channel
    i2s_.write(sample);
    i2s_.write(sample);

    // increment the counter for the next sample
    count++;
  }

  delay(85);
}

void playTest() {
}

void playCW() {
  // INSERTAMOS ENCENDIDO DE LEDS
  gpio_put(LED_FILTER_1, 0);
  gpio_put(LED_FILTER_2, 0);
  gpio_put(LED_FILTER_3, 1);
  gpio_put(LED_FILTER_4, 0);
  // C
  playDash();
  playDith();
  playDash();
  playDith();

  playDelay();

  // W
  playDith();
  playDash();
  playDash();
  playDelay();
}

void playCN() {
  // INSERTAMOS ENCENDIDO DE LEDS
  gpio_put(LED_FILTER_1, 0);
  gpio_put(LED_FILTER_2, 0);
  gpio_put(LED_FILTER_3, 0);
  gpio_put(LED_FILTER_4, 1);
  // C
  playDash();
  playDith();
  playDash();
  playDith();

  playDelay();

  // N

  playDash();
  playDith();
  playDelay();
}

void playSW() {
  // INSERTAMOS ENCENDIDO DE LEDS
  gpio_put(LED_FILTER_1, 1);
  gpio_put(LED_FILTER_2, 0);
  gpio_put(LED_FILTER_3, 0);
  gpio_put(LED_FILTER_4, 0);
  // S
  playDith();
  playDith();
  playDith();

  playDelay();

  // S
  playDith();
  playDith();
  playDith();

  playDelay();


  // W
  playDith();
  playDash();
  playDash();
  playDelay();
}

void playSN() {
  // INSERTAMOS ENCENDIDO DE LEDS
  gpio_put(LED_FILTER_1, 0);
  gpio_put(LED_FILTER_2, 1);
  gpio_put(LED_FILTER_3, 0);
  gpio_put(LED_FILTER_4, 0);
  // S
  playDith();
  playDith();
  playDith();

  playDelay();

  // S
  playDith();
  playDith();
  playDith();

  playDelay();

  // N

  playDash();
  playDith();
  playDelay();
}

void playNN() {
  // INSERTAMOS ENCENDIDO DE LEDS
  gpio_put(LED_NOISE_1, 0);
  gpio_put(LED_NOISE_2, 0);
  // N

  playDash();
  playDith();
  playDelay();

  playDelay();

  // N

  playDash();
  playDith();
  playDelay();
}


void playN1() {
  gpio_put(LED_NOISE_1, 1);
  gpio_put(LED_NOISE_2, 0);
  // N

  playDash();
  playDith();

  playDelay();

  // 1
  playDith();
  playDash();
  playDash();
  playDash();
  playDash();

  playDelay();
}


void playN2() {
  gpio_put(LED_NOISE_1, 0);
  gpio_put(LED_NOISE_2, 1);
  // N

  playDash();
  playDith();
  playDelay();

  // 2
  playDith();
  playDith();
  playDash();
  playDash();
  playDash();

  playDelay();
}
