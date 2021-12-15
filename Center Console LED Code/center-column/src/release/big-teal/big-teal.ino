#include <FastLED.h>
#include <OPI2020CenterColumn.h>

FASTLED_USING_NAMESPACE

// Slowly fill the LED strips with teal after a delay

#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[N_LEDS];

#define BRIGHTNESS          96
#define FRAMES_PER_SECOND  120

void setup() {
  delay(3000); // 3 second delay for recovery

  FastLED.addLeds<NEOPIXEL,OUT1_PIN>(leds, N_LEDS); 
  FastLED.addLeds<NEOPIXEL,OUT2_PIN>(leds, N_LEDS); 
  FastLED.addLeds<NEOPIXEL,OUT3_PIN>(leds, N_LEDS); 
  FastLED.addLeds<NEOPIXEL,OUT4_PIN>(leds, N_LEDS); 
  FastLED.addLeds<NEOPIXEL,OUT5_PIN>(leds, N_LEDS); 
  FastLED.addLeds<NEOPIXEL,OUT6_PIN>(leds, N_LEDS); 

  // set master brightness control
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();

  // Wait a bit
  delay(10000);

  for (uint8_t i = 0; i < N_LEDS; i++) {
    leds[i] = CRGB::Aqua;
    FastLED.show();
    delay(300);
  }
}

void loop() {

}
