//LED 5 핀
#include <Adafruit_NeoPixel.h>

#define LED_PIN 5

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 3

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void initLED() {

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void ledShow() {
  // Fill along the length of the strip in various colors...
  colorWipe(strip.Color(255,   0,   0), 500); // Red
  colorWipe(strip.Color(  0, 255,   0), 500); // Green
  colorWipe(strip.Color(  0,   0, 255), 500); // Blue
}
