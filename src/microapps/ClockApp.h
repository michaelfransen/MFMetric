#include <Arduino.h>
#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>

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
        void displayDate();
};