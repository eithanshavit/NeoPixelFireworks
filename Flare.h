#ifndef Flare_h
#define Flare_h

#include <FastLED.h>
#include "Canvas.h"

class Flare
{
public:
  Flare(
      CRGB color,
      double positionMeters,
      double velocityMeterPerSec);
  bool isAlive();
  void update();
  void render(Canvas *canvas);

private:
  double _timeOfBirth;
  double _timeOfLastUpdate;
  double _velocityMeterPerSec;
  int _direction;
  CRGB _currentColor;
  CRGB _color;
  double _postionMeters;
  double _fadeFactor;
  double _ignitionTimeSec;
};

#endif