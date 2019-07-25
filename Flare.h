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
  unsigned long _timeOfBirth;
  unsigned long _timeOfLastUpdate;
  double _velocityMeterPerSec;
  int _direction;
  CRGB _initialColor;
  CRGB _color;
  double _postionMeters;
  double _fadeFactor;
  double _ignitionTimeSec;
};

#endif