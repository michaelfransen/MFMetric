#include <Arduino.h>
#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>
#include <FontRobotron.h>
#include <WiFi.h>
#include <HTTPClient.h>

class ClockApp {
    public:
        ClockApp(cLEDMatrixBase *leds);
        void setup();
        void loop();
    private:
        cLEDMatrixBase *m_leds;
        cLEDText message;
        void displayDaysOfWeek();
        void displayTime();
};