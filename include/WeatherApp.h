#include <Arduino.h>
#include <FastLED.h>
#include <LEDMatrix.h>
#include <LEDText.h>
#define _TASK_SLEEP_ON_IDLE_RUN // Enable 1 ms SLEEP_IDLE powerdowns between tasks if no callback methods were invoked during the pass
#define _TASK_STATUS_REQUEST 
#include <TaskScheduler.h>

class WeatherApp {
    public:
        WeatherApp(cLEDMatrixBase *leds);
        void setup();
        void loop();
    private:
        cLEDMatrixBase *m_leds;
        cLEDText message;
};