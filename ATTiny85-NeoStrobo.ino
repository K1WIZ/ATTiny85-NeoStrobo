/*
 * NeoPixel Ring Color Strobe
 * 
 * written by: John Rogers     john at wizworks dot net
 * revision 1   Oct 25 2023
 * 
 * License: GPL
 * Free for all use both commercial and private so long as this notice persists in all derivatives.
 */

#include <Adafruit_NeoPixel.h>

#define PIN            2  // Data Pin connected to the NeoPixels
#define NUMPIXELS      16  // Number of NeoPixels in the ring
#define ADJPIXELS      1  // Number of adjacent pixes to fire (more increases perceived brightness)

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Define an array of specified colors, including white
uint32_t rainbowColors[] = {
  strip.Color(255, 255, 255),  // White
  strip.Color(255, 0, 0),     // Red
  strip.Color(255, 127, 0),   // Orange
  strip.Color(255, 255, 0),   // Yellow
  strip.Color(0, 255, 0),     // Green
  strip.Color(0, 0, 255),     // Blue
  strip.Color(127, 0, 255)    // Violet
};

void setup() {
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  randomSeed(analogRead(0));  // Seed the random number generator
}

void loop() {
  int pixel = random(NUMPIXELS - 3);  // Randomly choose a pixel (avoid last three pixels)

  // Randomly choose a color from the specified set
  uint32_t color = rainbowColors[random(7)];

  // Set the pixels to the random color
  for (int i = 0; i < ADJPIXELS; i++) {
    strip.setPixelColor(pixel + i, color);
  }
  strip.show();

  delay(50);  // Keep the pixels on for 50 milliseconds

  // Turn off the pixels
  for (int i = 0; i < ADJPIXELS; i++) {
    strip.setPixelColor(pixel + i, 0);
  }
  strip.show();

  delay(random(50, 100));  // Random off time between bursts in milliseconds
}
