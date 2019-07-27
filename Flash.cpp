#include "Flash.h"

#include "Common.h"

#define EXPLODE_IMPLODE_TIME_RATIO 0.6

Flash::Flash(double positionMeters, double durationSec)
{
  _timeOfBirth = millis();
  _postionMeters = positionMeters;
  _durationSec = durationSec;
  _explodeDurationSec = durationSec * EXPLODE_IMPLODE_TIME_RATIO;
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
  uint8_t colorValue;
  if (timeSinceBirthSec < _explodeDurationSec)
  {
    double fractionOfExplode = timeSinceBirthSec / _explodeDurationSec;
    colorValue = _explodeValue(fractionOfExplode);
  }
  else
  {
    double fractionOfImplode = min(1, (timeSinceBirthSec - _explodeDurationSec) / _implodeDurationSec);
    colorValue = _implodeValue(fractionOfImplode);
  }
  _color = CHSV(255, 0, colorValue);
}

void Flash::render(Canvas *canvas)
{
  CRGB color = isAlive() ? _color : CHSV(0, 0, 0);
  canvas->setColorInMeterPosition(color, _postionMeters);
  canvas->setColorInMeterPosition(color, _postionMeters + 0.02);
  canvas->setColorInMeterPosition(color, _postionMeters - 0.02);
}

uint8_t Flash::_explodeValue(double timeFraction)
{
  uint8_t value = ((ease8InOutQuad(127 + timeFraction * 128) - ease8InOutQuad(127)) * 255) / (ease8InOutQuad(255) - ease8InOutQuad(127));
  return value;
}

uint8_t Flash::_implodeValue(double timeFraction)
{
  uint8_t value = 255 - ease8InOutQuad(timeFraction * 128);
  return value;
}