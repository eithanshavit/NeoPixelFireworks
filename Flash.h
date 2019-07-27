#ifndef Flash_h
#define Flash_h

#include <FastLED.h>
#include "Canvas.h"

class Flash
{
public:
  Flash(double positionMeters, double durationSec);
  bool isAlive();
  void update();
  void render(Canvas *canvas);

private:
  double _timeOfBirth;
  double _durationSec;
  double _explodeDurationSec;
  double _implodeDurationSec;
  double _postionMeters;
  CHSV _color;
  uint8_t _explodeValue(double timeFraction);
  uint8_t _implodeValue(double timeFraction);
};

#endif