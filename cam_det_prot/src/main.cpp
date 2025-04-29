#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN    48  // Adjust if your LED is connected to a different GPIO
#define NUM_LEDS   1

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  // Set color to red
  strip.setPixelColor(0, strip.Color(255, 0, 0));
  strip.show();
  delay(1000);

  // Set color to green
  strip.setPixelColor(0, strip.Color(0, 255, 0));
  strip.show();
  delay(1000);

  // Set color to blue
  strip.setPixelColor(0, strip.Color(0, 0, 255));
  strip.show();
  delay(1000);

  // Turn off
  strip.setPixelColor(0, strip.Color(0, 0, 0));
  strip.show();
  delay(1000);
}
