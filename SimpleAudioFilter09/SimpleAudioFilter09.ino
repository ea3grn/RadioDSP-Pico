/************************************************************* 
 * SimpleAudioFilter09.ino
 * Audio Filter DSP for Shorthwave Receiver
 * Based on Raspberry Pico Pi2 Processor module
 * 
 * Filter Functions :
 * 0. Audio passthrough 
 * 1..4 Filters ( SSB W / SSB N / CW w / CW N)
 * 
 * DNR NLMS Functions:
 * 0. Audio passthrough 
 * 1. DNR NLMS denoise Level 1 (low action)
 * 2. DNR NLMS denoise Level 2 (high action) 
 * 
 * With CW audio announce for mode and dnr change
 * 
 * Created: Start works on Feb 2023
 * Author: Giuseppe Callipo - IK8YFW
 * https://github.com/ik8yfw
 * 
 * License: Creative Common with attribution 
 * 
 * This program use filters built with the tFilter program
 * http://t-filter.engineerjs.com/
 * 
 * Last update: 03/01/2025
 * NOTE: This version does not works with Raspberry Pico Pi but
 *       need the new module Raspberry Pico Pi2 based on CortexM33 Architecture.
 */

#include "audioIO.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void setup() {

//definimos los leds para indicar el estado
#define LED_FILTER_1 5  // SSB WIDE
#define LED_FILTER_2 6  // SSB NARROW
#define LED_FILTER_3 7  // CW WIDE
#define LED_FILTER_4 8  // CW NARROW

#define LED_NOISE_1 9   // DNR DENOISE LEVEL 1
#define LED_NOISE_2 10   // DNR DENOISE LEVEL 2

#ifdef DEBUG_SERIAL 
  Serial.begin(115200);
#endif  

  // Keep SMPS PWM mode to reduce audio noise. (RPi Pico Dataseet p.18)
  pinMode(23, OUTPUT);
  digitalWrite(23, HIGH);

  gpio_init(LED_FILTER_1);
  gpio_init(LED_FILTER_2);
  gpio_init(LED_FILTER_3);
  gpio_init(LED_FILTER_4);
  gpio_init(LED_NOISE_1);
  gpio_init(LED_NOISE_2);

  gpio_set_dir(LED_FILTER_1, GPIO_OUT);
  gpio_set_dir(LED_FILTER_2, GPIO_OUT);
  gpio_set_dir(LED_FILTER_3, GPIO_OUT);
  gpio_set_dir(LED_FILTER_4, GPIO_OUT);
  gpio_set_dir(LED_NOISE_1, GPIO_OUT);
  gpio_set_dir(LED_NOISE_2, GPIO_OUT);
 
  // nos aseguramos de que todo los leds esten apagados
  gpio_put(LED_FILTER_1,0);
  gpio_put(LED_FILTER_2,0);
  gpio_put(LED_FILTER_3,0);
  gpio_put(LED_FILTER_4,0);
  gpio_put(LED_NOISE_1,0);
  gpio_put(LED_NOISE_2,0);


  audioIO_setup();

}


  //configuramos GPIO

  
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void loop(void)
{
  audioIO_loop();
}
