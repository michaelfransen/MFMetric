#include "ClockApp.h"
#include <FontRobotron.h>

using namespace std;

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -25200;
const int   daylightOffset_sec = 0;

void ClockApp::displayTime() {
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

void ClockApp::displayDaysOfWeek() {
  struct tm timeinfo;

  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }

  CRGB activeColor = CRGB::White;
  CRGB inactiveColor = 0x040404;

  // Sunday Line
  CRGB sundayColor = timeinfo.tm_wday == 0 ? activeColor : inactiveColor;
  m_leds->DrawLine(11, 0, 12, 0, sundayColor);
  // Monday Line
  CRGB mondayColor = timeinfo.tm_wday == 1 ? activeColor : inactiveColor;
  m_leds->DrawLine(14, 0, 15, 0, mondayColor);
  // Tuesday Line
  CRGB tuesdayColor = timeinfo.tm_wday == 2 ? activeColor : inactiveColor;
  m_leds->DrawLine(17, 0, 18, 0, tuesdayColor);
  // Wednesday Line
  CRGB wednesdayColor = timeinfo.tm_wday == 3 ? activeColor : inactiveColor;
  m_leds->DrawLine(20, 0, 21, 0, wednesdayColor);
  // Thursday Line
  CRGB thursdayColor = timeinfo.tm_wday == 4 ? activeColor : inactiveColor;
  m_leds->DrawLine(23, 0, 24, 0, thursdayColor);
  // Friday Line
  CRGB fridayColor = timeinfo.tm_wday == 5 ? activeColor : inactiveColor;
  m_leds->DrawLine(26, 0, 27, 0, fridayColor);
  // Saturday Line
  CRGB saturdayColor = timeinfo.tm_wday == 6 ? activeColor : inactiveColor;
  m_leds->DrawLine(29, 0, 30, 0, saturdayColor);
}

ClockApp::ClockApp(cLEDMatrixBase *leds) {
    m_leds = leds;
}

void ClockApp::setup() {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    message.Init(m_leds, 24, 5, 12, 3);
    message.SetFont(MFFontData);
    message.SetTextColrOptions(COLR_RGB, 0xff, 0xff, 0xff);
    displayDaysOfWeek();
}

void ClockApp::loop() {
    EVERY_N_SECONDS(0.5) {
        displayTime();
        FastLED.show();
  }
}