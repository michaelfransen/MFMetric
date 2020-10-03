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
  strftime(text, sizeof(text), "%I:%M", &timeinfo);
  message.SetText((unsigned char *)text, sizeof(text) - 1);
  message.UpdateText();
}

void displayDaysOfWeek() {
  struct tm timeinfo;

  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  CRGB activeColor = CRGB::White;
  CRGB inactiveColor = 0x040404;

  // Sunday Line
  CRGB sundayColor = timeinfo.tm_wday == 0 ? activeColor : inactiveColor;
  leds.DrawLine(11, 0, 12, 0, sundayColor);
  // Monday Line
  CRGB mondayColor = timeinfo.tm_wday == 1 ? activeColor : inactiveColor;
  leds.DrawLine(14, 0, 15, 0, mondayColor);
  // Tuesday Line
  CRGB tuesdayColor = timeinfo.tm_wday == 2 ? activeColor : inactiveColor;
  leds.DrawLine(17, 0, 18, 0, tuesdayColor);
  // Wednesday Line
  CRGB wednesdayColor = timeinfo.tm_wday == 3 ? activeColor : inactiveColor;
  leds.DrawLine(20, 0, 21, 0, wednesdayColor);
  // Thursday Line
  CRGB thursdayColor = timeinfo.tm_wday == 4 ? activeColor : inactiveColor;
  leds.DrawLine(23, 0, 24, 0, thursdayColor);
  // Friday Line
  CRGB fridayColor = timeinfo.tm_wday == 5 ? activeColor : inactiveColor;
  leds.DrawLine(26, 0, 27, 0, fridayColor);
  // Saturday Line
  CRGB saturdayColor = timeinfo.tm_wday == 6 ? activeColor : inactiveColor;
  leds.DrawLine(29, 0, 30, 0, saturdayColor);
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
  FastLED.setBrightness(100);
  FastLED.clear(true);
  message.Init(&leds, 24, 5, 12, 3);
  message.SetFont(MFFontData);
  message.SetTextColrOptions(COLR_RGB | COLR_GRAD, 0xd2, 0x01, 0x01, 0xff, 0x5c, 0x00);
}

void loop() {
  EVERY_N_SECONDS(0.5) {
    displayTime();
    displayDaysOfWeek();
    FastLED.show();
  }

  delay(20);
}
