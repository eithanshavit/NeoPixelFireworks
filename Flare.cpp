#include "Flare.h"

#define BRIGHTNESS_THRESHOLD 0
#define MIN_IGNITION_TIME_SEC 0.1
#define MAX_IGNITION_TIME_SEC 0.3
#define MIN_FADE_BY_FACTOR 0.10
#define MAX_FADE_BY_FACTOR 0.25
#define MAX_FADE_BY_VALUE 255

Flare::Flare(
    CRGB color,
    double positionMeters,
    double velocityMeterPerSec)
{
    _timeOfBirth = millis();
    _postionMeters = positionMeters;
    _color = color;
    _timeOfLastUpdate = _timeOfBirth;
    _velocityMeterPerSec = velocityMeterPerSec;
    _direction = velocityMeterPerSec > 0 ? 1 : -1;
    _ignitionTimeSec = MIN_IGNITION_TIME_SEC + (MAX_IGNITION_TIME_SEC - MIN_IGNITION_TIME_SEC) * _randomFraction();
    _fadeFactor = MIN_FADE_BY_FACTOR + (MAX_FADE_BY_FACTOR - MIN_FADE_BY_FACTOR) * _randomFraction();
}

bool Flare::isAlive()
{
    return _color.getLuma() > BRIGHTNESS_THRESHOLD;
}

CRGB Flare::getColor()
{
    if (_timeToSec(_age()) < _ignitionTimeSec)
    {
        return CRGB::White;
    }
    return _color;
}

double Flare::getPositionMeters()
{
    return _postionMeters;
}

void Flare::update()
{
    unsigned long currentTime = millis();
    unsigned long deltaSinceLastUpdate = currentTime - _timeOfLastUpdate;
    _timeOfLastUpdate = currentTime;
    _postionMeters += _velocityMeterPerSec * _timeToSec(deltaSinceLastUpdate);
    _velocityMeterPerSec -= 2 * _velocityMeterPerSec * _timeToSec(deltaSinceLastUpdate);
    // Only fade if the age is past the ignition time
    if (_timeToSec(_age()) > _ignitionTimeSec)
    {
        _color = _color.fadeToBlackBy(_fadeFactor * MAX_FADE_BY_VALUE);
    }
}

unsigned long Flare::_age()
{
    return _timeOfLastUpdate - _timeOfBirth;
}

double Flare::_timeToSec(unsigned long time)
{
    return time / 1000.0;
}

double Flare::_randomFraction()
{
    return double(random8()) / 255;
}