#include "ClockApp.h"
#include <MFFont.h>

using namespace std;

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -25200;
const int daylightOffset_sec = 0;

void ClockApp::displayTime(tm timeinfo)
{
  char text[8];
  strftime(text, sizeof(text), "%I:%M", &timeinfo);
  message.SetText((unsigned char *)text, sizeof(text) - 1);
  message.UpdateText();
}

void ClockApp::displayDate(tm timeinfo)
{
  CRGB first[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White};

  CRGB second[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB third[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB fourth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB fifth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB sixth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB seventh[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB eigth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB ninth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB tenth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB eleventh[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB twelfth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB thirteenth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB fourteenth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB fifteenth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB sixteenth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB seventeenth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB eighteenth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB nineteenth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB twentith[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB twentyfirst[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB twentysecond[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB twentythrid[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB twentyfourth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB twentyfifth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB twentysixth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB twentyseventh[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB twentyeigth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB twentyninth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB thirtieth[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::Black, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB thirtyfirst[] = {
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::Black, CRGB::Black, CRGB::White, CRGB::White, CRGB::Black, CRGB::White, CRGB::White,
      CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White, CRGB::White};

  CRGB date[64];

  switch (timeinfo.tm_mday)
  {
    case 1:
      memcpy(date, first, sizeof(date));
      break;
    case 2:
      memcpy(date, second, sizeof(date));
      break;
    case 3:
      memcpy(date, third, sizeof(date));
      break;
    case 4:
      memcpy(date, fourth, sizeof(date));
      break;
    case 5:
      memcpy(date, fifth, sizeof(date));
      break;
    case 6:
      memcpy(date, sixth, sizeof(date));
      break;
    case 7:
      memcpy(date, seventh, sizeof(date));
      break;
    case 8:
      memcpy(date, eigth, sizeof(date));
      break;
    case 9:
      memcpy(date, eigth, sizeof(date));
      break;
    case 10:
      memcpy(date, tenth, sizeof(date));
      break;
    case 11:
      memcpy(date, eleventh, sizeof(date));
      break;
    case 12:
      memcpy(date, twelfth, sizeof(date));
      break;
    case 13:
      memcpy(date, thirteenth, sizeof(date));
      break;
    case 14:
      memcpy(date, fourteenth, sizeof(date));
      break;
    case 15:
      memcpy(date, fifteenth, sizeof(date));
      break;
    case 16:
      memcpy(date, sixteenth, sizeof(date));
      break;
    case 17:
      memcpy(date, seventeenth, sizeof(date));
      break;
    case 18:
      memcpy(date, eighteenth, sizeof(date));
      break;
    case 19:
      memcpy(date, nineteenth, sizeof(date));
      break;
    case 20:
      memcpy(date, twentith, sizeof(date));
      break;
    case 21:
      memcpy(date, twentyfirst, sizeof(date));
      break;
    case 22:
      memcpy(date, twentysecond, sizeof(date));
      break;
    case 23:
      memcpy(date, twentythrid, sizeof(date));
      break;
    case 24:
      memcpy(date, twentyfourth, sizeof(date));
      break;
    case 25:
      memcpy(date, twentyfifth, sizeof(date));
      break;
    case 26:
      memcpy(date, twentysixth, sizeof(date));
      break;
    case 27:
      memcpy(date, twentyseventh, sizeof(date));
      break;
    case 28:
      memcpy(date, twentyeigth, sizeof(date));
      break;
    case 29:
      memcpy(date, twentyninth, sizeof(date));
      break;
    case 30:
      memcpy(date, thirtieth, sizeof(date));
      break;
    case 31:
      memcpy(date, thirtyfirst, sizeof(date));
      break;
  }

  int height = 8;
  int width = 8;

  for (int y = 0; y < height; y++)
  {
    for (int x = width; x > 0; x--)
    {
      int index = ((height * width) - (y * width) - (width - x) - 1);
      CRGB color = date[index];
      m_leds->DrawPixel(x, y, color);
    }
  }
}

void ClockApp::displayDaysOfWeek(tm timeinfo)
{
  CRGB activeColor = CRGB::White;
  CRGB inactiveColor = 0x0a0a0a;

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

void ClockApp::updateDisplay() {
  struct tm timeinfo;

  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }

  displayDaysOfWeek(timeinfo);
  displayDate(timeinfo);
  displayTime(timeinfo);
}

ClockApp::ClockApp(cLEDMatrixBase *leds)
{
  m_leds = leds;
}

void ClockApp::setup()
{
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  message.Init(m_leds, 24, 5, 12, 3);
  message.SetFont(MFFontData);
  message.SetTextColrOptions(COLR_RGB, 0xff, 0xff, 0xff);
  updateDisplay();
}

void ClockApp::loop()
{
  EVERY_N_SECONDS(0.5)
  {
    struct tm timeinfo;

    if (!getLocalTime(&timeinfo))
    {
      Serial.println("Failed to obtain time");
      return;
    }

    updateDisplay();
    FastLED.show();
  }
}