#ifndef Blast_h
#define Blast_h

#include <LinkedList.h>
#include "Flare.h"

class Blast
{
public:
  Blast(double positionMeters);
  bool isAlive();
  LinkedList<Flare *> *getFlares();
  int flaresCount();
  void update();
  ~Blast();

private:
  void _addFlare(double velocityMeterPerSec);
  double _postionMeters;
  CRGB _color;
  LinkedList<Flare *> *_flares;
};

#endif