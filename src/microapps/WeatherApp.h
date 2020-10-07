#include <Arduino.h>
#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>

class WeatherApp {
    public:
        WeatherApp(cLEDMatrixBase *leds);
        void setup();
        void loop();
    private:
        cLEDMatrixBase *m_leds;
        cLEDText message;
};