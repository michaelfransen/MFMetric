#include <Arduino.h>
#include "WeatherApp.h"
#include <MFFont.h>

using namespace std;


WeatherApp::WeatherApp(cLEDMatrixBase *leds)
{
  m_leds = leds;
}

void WeatherApp::setup()
{
  message.Init(m_leds, 24, 5, 12, 3);
  message.SetFont(MFFontData);
  message.SetTextColrOptions(COLR_RGB, 0xff, 0xff, 0xff);
}

void WeatherApp::loop()
{
  EVERY_N_SECONDS(0.5)
  {
    
  }
}