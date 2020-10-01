#include <Arduino.h>
#include <FastLED.h>
#include <FastLED_GFX.h>
#include <LEDMatrix.h>

// Change the next defines to match your matrix type and size
#define DATA_PIN            27

#define COLOR_ORDER         GRB
#define CHIPSET             WS2812B

// initial matrix layout (to get led strip index by x/y)
#define MATRIX_WIDTH        8
#define MATRIX_HEIGHT       32
#define MATRIX_TYPE         HORIZONTAL_ZIGZAG_MATRIX
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUMPIXELS           MATRIX_SIZE

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

void setup() {
  // initial FastLED by using CRGB led source from our matrix class
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(100);
  FastLED.clear(true);
}

void loop() {
  EVERY_N_SECONDS(1) {
    //leds.DrawPixel(7, 31, CRGB::Cyan);
    leds.DrawFilledRectangle(0, 0, 7, 7, CRGB::DarkCyan);
    leds.DrawFilledRectangle(0, 8, 7, 15, CRGB::Orange);
    leds.DrawFilledRectangle(0, 16, 7, 23, CRGB::DarkCyan);
    leds.DrawFilledRectangle(0, 24, 7, 31, CRGB::Orange);
  
    FastLED.show();
  }
}
