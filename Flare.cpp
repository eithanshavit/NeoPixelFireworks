#include "Flare.h"

#include "Common.h"

#define BRIGHTNESS_THRESHOLD 0
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
    _fadeFactor = randomFraction(MIN_FADE_BY_FACTOR, MAX_FADE_BY_FACTOR);
}

bool Flare::isAlive()
{
    return _color.getLuma() > BRIGHTNESS_THRESHOLD;
}

CRGB Flare::getColor()
{
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
    double positionDelta = _velocityMeterPerSec * timeToSec(deltaSinceLastUpdate);
    _postionMeters += positionDelta;
    _velocityMeterPerSec -= 2 * positionDelta;
    _color = _color.fadeToBlackBy(_fadeFactor * MAX_FADE_BY_VALUE);
}