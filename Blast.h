#ifndef Blast_h
#define Blast_h

#include <LinkedList.h>
#include "Flare.h"
#include "Flash.h"
#include "Canvas.h"

class Blast
{
public:
  Blast(double positionMeters);
  bool isAlive();
  void update();
  void render(Canvas *canvas);
  ~Blast();

private:
  void _addFlare(double velocityMeterPerSec);
  double _postionMeters;
  double _timeOfBirth;
  double _flashDurationSec;
  CHSV _color;
  LinkedList<Flare *> *_flares;
  Flash *_flash;
};

#endif