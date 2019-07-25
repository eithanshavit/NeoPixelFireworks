#include "Blast.h"

#include "Common.h"

#define MIN_FLARE_COUNT 25
#define MAX_FLARE_COUNT 45
#define MIN_VELOCITY_SEC 0.4
#define MAX_VELOCITY_SEC 3

Blast::Blast(double positionMeters)
{
  _flares = new LinkedList<Flare *>();
  _postionMeters = positionMeters;
  _color = CHSV(random8(), 255, 255);
  int numberOfFlares = random8(MIN_FLARE_COUNT, MAX_FLARE_COUNT);
  while (--numberOfFlares > 0)
  {
    double velocity = randomFraction(MIN_VELOCITY_SEC, MAX_VELOCITY_SEC) * (random8(2) ? 1 : -1);
    _addFlare(velocity);
  }
}

void Blast::update()
{
  for (int i = 0; i < _flares->size(); i++)
  {
    Flare *f = _flares->get(i);
    f->update();
  }
}

void Blast::render(Canvas *canvas)
{
  for (int i = 0; i < _flares->size(); i++)
  {
    Flare *f = _flares->get(i);
    f->render(canvas);
  }
}

bool Blast::isAlive()
{
  bool isAlive = false;
  for (int i = 0; i < _flares->size(); i++)
  {
    Flare *f = _flares->get(i);
    if (f->isAlive())
    {
      isAlive = true;
      break;
    }
  }
  return isAlive;
}

void Blast::_addFlare(double velocityMeterPerSec)
{
  _flares->add(new Flare(
      _color,
      _postionMeters,
      velocityMeterPerSec));
}

Blast::~Blast()
{
  Flare *flare;
  while (_flares->size() > 0)
  {
    flare = _flares->remove(0);
    delete flare;
  }
  delete _flares;
}