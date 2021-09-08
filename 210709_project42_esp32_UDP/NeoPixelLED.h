//LED 5 핀
#include <Adafruit_NeoPixel.h>

#define LED_PIN 5

// How many NeoPixels are attached to the Arduino?

#define LED_COUNT 3
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

//uint32_t red = strip.Color(255, 0, 0);
//uint32_t green = strip.Color(0, 255, 0);
//uint32_t blue = strip.Color(0, 0, 255);
//uint32_t magenta = strip.Color(255, 0, 255);
//uint32_t yellow = strip.Color(255, 255, 0);
//uint32_t white = strip.Color(255, 255, 255);
//uint32_t black = strip.Color(0, 0, 0);

uint32_t ledColorName = 0;
int brightness = 255;

unsigned long previousMillis = 0;
int ledState = 0;

void initLED() {
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(brightness); // Set BRIGHTNESS to about 1/5 (max = 255)
}

void ledShow(int color) {
  switch (color) {
    case 1:
      ledColorName = strip.Color(255, 0, 0);
      break;
    case 2:
      ledColorName = strip.Color(0, 255, 0);
      break;
    case 3:
      ledColorName = strip.Color(0, 0, 255);
      break;
    case 4:
      ledColorName = strip.Color(255, 0, 255);
      break;
    case 5:
      ledColorName = strip.Color(255, 255, 0);
      break;
    case 6:
      ledColorName = strip.Color(0, 255, 255);
      break;
    case 7:
      ledColorName = strip.Color(255, 255, 255);
      break;
    case 8:
      ledColorName = strip.Color(0, 0, 0);
      break;
    default:
      break;
  }

  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, ledColorName);
  }
  strip.show();
}

void ledOff() {
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
}

void ledBlink(int color, int interval) {
  switch (color) {
    case 1:
      ledColorName = strip.Color(255, 0, 0);
      break;
    case 2:
      ledColorName = strip.Color(0, 255, 0);
      break;
    case 3:
      ledColorName = strip.Color(0, 0, 255);
      break;
    case 4:
      ledColorName = strip.Color(255, 0, 255);
      break;
    case 5:
      ledColorName = strip.Color(255, 255, 0);
      break;
    case 6:
      ledColorName = strip.Color(0, 255, 255);
      break;
    case 7:
      ledColorName = strip.Color(255, 255, 255);
      break;
    case 8:
      ledColorName = strip.Color(0, 0, 0);
      break;
    default:
      break;
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;

    } else {
      ledState = LOW;
    }
  }

  if (ledState) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, ledColorName);
    }
  } else {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }

  }

  strip.show();
}

void ledRainbow(int interval) {
  unsigned long currentMillis = millis();

  static unsigned long firstPixelHue = 0;
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    firstPixelHue += 256;
    if (firstPixelHue >= 5 * 65536) {
      firstPixelHue = 0;
    }
  }

  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    // Offset pixel hue by an amount to make one full revolution of the
    // color wheel (range of 65536) along the length of the strip
    // (strip.numPixels() steps):
    int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());

    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
  }
  strip.show(); // Update strip with new contents

}
