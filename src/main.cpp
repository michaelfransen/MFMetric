#include <Arduino.h>
#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>
#include <FontRobotron.h>
#include <WiFi.h>
#include <HTTPClient.h>

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

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -25200;
const int   daylightOffset_sec = 0;

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, -MATRIX_HEIGHT, MATRIX_TYPE> leds;
cLEDText message;

// void printLocalTime()
// {
//   struct tm timeinfo;
//   if(!getLocalTime(&timeinfo)){
//     Serial.println("Failed to obtain time");
//     return;
//   }
//   Serial.println(&timeinfo, "%H:%M");
// }

void displayTime() {
  struct tm timeinfo;

  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  char text[8];
  sprintf(text, "%d:%d", timeinfo.tm_hour, timeinfo.tm_min);
  message.SetText((unsigned char *)text, sizeof(text) - 1);
  message.UpdateText();
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  Serial.println("Connected to wifi.");

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // initial FastLED by using CRGB led source from our matrix class
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(40);
  FastLED.clear(true);
  message.Init(&leds, 24, 8, 12, 0);
  message.SetFont(MFFontData);
  unsigned char text[] = {"00:00"};
  message.SetText((unsigned char *)text, sizeof(text) - 1);
  message.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0x00, 0xff);
  message.UpdateText();
}

void loop() {
  EVERY_N_SECONDS(0.5) {
    displayTime();
    FastLED.show();
  }
}
