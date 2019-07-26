#include "Flash.h"

#include "Common.h"

Flash::Flash(double positionMeters, double durationSec)
{
  _timeOfBirth = millis();
  _postionMeters = positionMeters;
  _durationSec = durationSec;
  _explodeDurationSec = durationSec / 2;
  _implodeDurationSec = durationSec - _explodeDurationSec;
  _color = CHSV(255, 0, 0);
}

bool Flash::isAlive()
{
  double timeSinceBirthSec = timeToSec(millis() - _timeOfBirth);
  return timeSinceBirthSec < _durationSec;
}

void Flash::update()
{
  double timeSinceBirthSec = timeToSec(millis() - _timeOfBirth);
  double fractionOfLife = min(1, timeSinceBirthSec / _durationSec);
  uint8_t colorValue = fractionOfLife * 255;
  _color = CHSV(255, 0, colorValue);
}

void Flash::render(Canvas *canvas)
{
  CRGB color = isAlive() ? _color : CHSV(0, 0, 0);
  canvas->setColorInMeterPosition(color, _postionMeters);
  canvas->setColorInMeterPosition(color, _postionMeters + 0.02);
  canvas->setColorInMeterPosition(color, _postionMeters - 0.02);
}