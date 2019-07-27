#include "Flare.h"

#include "Common.h"

#define BRIGHTNESS_THRESHOLD 0
#define MIN_FADE_BY_FACTOR 0.1
#define MAX_FADE_BY_FACTOR 0.3
#define MAX_FADE_BY_VALUE 255
#define MIN_IGNITION_TIME_SEC 0.05
#define MAX_IGNITION_TIME_SEC 0.15
#define VELOCITY_SLOW_DOWN_FACTOR 1.5
#define MIN_VELOCITY_METER_SEC 0.015

Flare::Flare(
    CRGB color,
    double positionMeters,
    double velocityMeterPerSec)
{
  _timeOfBirth = millis();
  _postionMeters = positionMeters;
  _color = color;
  _currentColor = CRGB::White;
  _timeOfLastUpdate = _timeOfBirth;
  _velocityMeterPerSec = velocityMeterPerSec;
  _direction = velocityMeterPerSec > 0 ? 1 : -1;
  _fadeFactor = randomFraction(MIN_FADE_BY_FACTOR, MAX_FADE_BY_FACTOR);
  _ignitionTimeSec = randomFraction(MIN_IGNITION_TIME_SEC, MAX_IGNITION_TIME_SEC);
}

bool Flare::isAlive()
{
  double timeSinceBirthSec = timeToSec(millis() - _timeOfBirth);
  bool isStillIgniting = timeSinceBirthSec < _ignitionTimeSec;
  bool isBright = _currentColor.getLuma() > BRIGHTNESS_THRESHOLD;
  return isBright || isStillIgniting;
}

void Flare::update()
{
  double currentTime = millis();
  double timeSinceLastUpdateSec = timeToSec(currentTime - _timeOfLastUpdate);
  double timeSinceBirthSec = timeToSec(currentTime - _timeOfBirth);

  double positionDeltaMeter = _velocityMeterPerSec * timeSinceLastUpdateSec;
  _postionMeters += positionDeltaMeter;
  if (abs(_velocityMeterPerSec) > MIN_VELOCITY_METER_SEC)
  {
    _velocityMeterPerSec -= VELOCITY_SLOW_DOWN_FACTOR * positionDeltaMeter;
  }

  bool isStillIgniting = timeSinceBirthSec < _ignitionTimeSec;
  _color.fadeToBlackBy(_fadeFactor * MAX_FADE_BY_VALUE);
  if (isStillIgniting)
  {
    _currentColor = CRGB::White;
  }
  else
  {
    _currentColor = _color;
  }
}

void Flare::render(Canvas *canvas)
{
  canvas->setColorInMeterPosition(_currentColor, _postionMeters);
}