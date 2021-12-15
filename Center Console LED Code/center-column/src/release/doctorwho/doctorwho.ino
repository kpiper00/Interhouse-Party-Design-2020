#include <FastLED.h>
#include <OPI2020CenterColumn.h>

#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

#define COLOR_DELAY 100000
#define FILL_DELAY  50
#define INTER_DELAY 2000

CRGB leds[N_LEDS];

void setup() {
  delay(3000); // 3 second delay for recovery

  FastLED.addLeds<NEOPIXEL,OUT1_PIN>(leds, N_LEDS); 
  FastLED.addLeds<NEOPIXEL,OUT2_PIN>(leds, N_LEDS); 
  FastLED.addLeds<NEOPIXEL,OUT3_PIN>(leds, N_LEDS); 
  FastLED.addLeds<NEOPIXEL,OUT4_PIN>(leds, N_LEDS); 
  FastLED.addLeds<NEOPIXEL,OUT5_PIN>(leds, N_LEDS); 
  FastLED.addLeds<NEOPIXEL,OUT6_PIN>(leds, N_LEDS); 

  // set master brightness control
  //FastLED.setBrightness(BRIGHTNESS);
}
  
void loop()
{
  fadeUp(0xFF4000);
  //fill_solid(leds, N_LEDS, 0xFF4800);
  FastLED.show();
  FastLED.delay(COLOR_DELAY); 
  fadeDown();

  FastLED.delay(INTER_DELAY);

  fadeUp(CRGB::White);
  //fill_solid(leds, N_LEDS, CRGB::White);
  FastLED.show();
  FastLED.delay(COLOR_DELAY); 
  fadeDown();

  FastLED.delay(INTER_DELAY);

  fadeUp(CRGB::Aqua);
  //fill_solid(leds, N_LEDS, CRGB::Aqua);
  FastLED.show();
  FastLED.delay(COLOR_DELAY); 
  fadeDown();
  
  FastLED.delay(INTER_DELAY);
}

void fadeUp(CRGB::HTMLColorCode color) {
  for (int i = 0; i < N_LEDS; i++) {
    leds[i] = color;
    FastLED.show();
    FastLED.delay(FILL_DELAY); 
  }
}

void fadeDown() {
  for (int i = N_LEDS-1; i >= 0; i--) {
    leds[i] = CRGB::Black;
    FastLED.show();
    FastLED.delay(FILL_DELAY); 
  }
}
