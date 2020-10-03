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
const long  gmtOffset_sec = -21600;
const int   daylightOffset_sec = 3600;

// create our matrix based on matrix definition
cLEDMatrix<MATRIX_WIDTH, -MATRIX_HEIGHT, MATRIX_TYPE> leds;
cLEDText message;

const unsigned char TxtDemo[] = {"12:00"};

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%H:%M");
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
  printLocalTime();

  // initial FastLED by using CRGB led source from our matrix class
  FastLED.addLeds<CHIPSET, DATA_PIN, COLOR_ORDER>(leds[0], leds.Size()).setCorrection(TypicalSMD5050);
  FastLED.setBrightness(40);
  FastLED.clear(true);
  message.Init(&leds, 24, 8, 12, 0);
  message.SetFont(MFFontData);
  message.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
  message.SetTextColrOptions(COLR_RGB | COLR_SINGLE, 0xff, 0x00, 0xff);
  message.UpdateText();
}

void loop() {
  EVERY_N_SECONDS(1) {
    //canvas.fillScreen(CRGB::Red);
    // leds.DrawFilledRectangle(0, 0, 7, 7, CRGB::DarkCyan);
    // leds.DrawFilledRectangle(8, 0, 15, 7, CRGB::Orange);
    // leds.DrawFilledRectangle(16, 0, 23, 7, CRGB::DarkCyan);
    // leds.DrawFilledRectangle(24, 0, 31, 7, CRGB::Orange);
    FastLED.show();
  }
  // if (message.UpdateText() == -1)
  //   message.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
  // else
    FastLED.show();
  delay(50);
}