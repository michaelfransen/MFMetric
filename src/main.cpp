#include <Arduino.h>
#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>
#include <WiFi.h>
#include "microapps/ClockApp.h"

// Change the next defines to match your matrix type and size
#define DATA_PIN            27

#define COLOR_ORDER         GRB
#define CHIPSET             WS2812B

// initial matrix layout (to get led strip index by x/y)
#define MATRIX_WIDTH        32
#define MATRIX_HEIGHT       8
#define MATRIX_TYPE         VERTICAL_ZIGZAG_MATRIX
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUMPIXELS           MATRIX_SIZE

const char* ssid = "Simon";
const char* password = "04190711";

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, -MATRIX_HEIGHT, MATRIX_TYPE> leds;
ClockApp clockApp(&leds);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.println("Connected to wifi.");

  // initial FastLED by using CRGB led source from our matrix class
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(100);
  FastLED.clear(true);
  clockApp.setup();
}

void loop() {
  clockApp.loop();
  delay(20);
}
