#include <Arduino.h>
#include "WeatherApp.h"
#include <MFFont.h>
#include "taskmanager/header.hpp"
#include <HTTPClient.h>

void retrieveWeather();
HTTPClient http;

Task weatherRetrieverTask(15 * TASK_MINUTE, TASK_FOREVER, &retrieveWeather);

WeatherApp::WeatherApp(cLEDMatrixBase *leds)
{
  m_leds = leds;
}

void retrieveWeather() {
    http.begin("http://api.openweathermap.org/data/2.5/weather?zip=94115,US&appid=d134621845de557af90dd48dd7dfa1b1");
    int statusCode = http.GET();

    if (statusCode > 0) { //Check for the returning code
        String payload = http.getString();
        Serial.println(statusCode);
        Serial.println(payload);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
}

void WeatherApp::setup()
{
  message.Init(m_leds, 24, 5, 12, 3);
  message.SetFont(MFFontData);
  message.SetTextColrOptions(COLR_RGB, 0xff, 0xff, 0xff);
  taskManager.addTask(weatherRetrieverTask);
  weatherRetrieverTask.enable();
}