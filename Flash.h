#ifndef Flash_h
#define Flash_h

#include <FastLED.h>
#include "Canvas.h"

class Flash
{
public:
  Flash(double positionMeters);
  bool isAlive();
  void update();
  void render(Canvas *canvas);

private:
  unsigned long _timeOfBirth;
  unsigned long _durationSec;
  double _postionMeters;
};

#endif