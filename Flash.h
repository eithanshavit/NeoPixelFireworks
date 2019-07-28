#ifndef Flash_h
#define Flash_h

#include <FastLED.h>
#include "Canvas.h"

class Flash
{
public:
  Flash(CHSV color, double positionMeters, double durationSec);
  bool isAlive();
  void update();
  void render(Canvas *canvas);

private:
  double _timeOfBirth;
  double _durationSec;
  double _explodeDurationSec;
  double _implodeDurationSec;
  double _positionMeters;
  double _maxRadiusMeter;
  double _radiusMeter;
  CHSV _color;
  double _explodeFractionByTime(double timeFraction);
  double _implodeFractionByTime(double timeFraction);
};

#endif