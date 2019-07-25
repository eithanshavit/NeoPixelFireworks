#ifndef Blast_h
#define Blast_h

#include <LinkedList.h>
#include "Flare.h"
#include "Canvas.h"

class Blast
{
public:
  Blast(double positionMeters);
  bool isAlive();
  LinkedList<Flare *> *getFlares();
  int flaresCount();
  void update();
  void render(Canvas *canvas);
  ~Blast();

private:
  void _addFlare(double velocityMeterPerSec);
  double _postionMeters;
  CRGB _color;
  LinkedList<Flare *> *_flares;
};

#endif