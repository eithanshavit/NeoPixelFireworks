#include "Blast.h"

#include "Common.h"

#define MIN_FLARE_COUNT 25
#define MAX_FLARE_COUNT 45
#define MIN_VELOCITY_SEC 0.4
#define MAX_VELOCITY_SEC 3
#define MIN_PARTICAL_DELAY_SEC 1
#define MAX_PARTICAL_DELAY_SEC 2

Blast::Blast(double positionMeters)
{
  _timeOfBirth = millis();
  _particalDelaySec = randomFraction(MIN_PARTICAL_DELAY_SEC, MAX_PARTICAL_DELAY_SEC);
  _flash = new Flash(positionMeters);
  _flares = new LinkedList<Flare *>();
  _postionMeters = positionMeters;
  _color = CHSV(random8(), 255, 255);
}

void Blast::update()
{
  unsigned long timeSinceBirthSec = timeToSec(millis() - _timeOfBirth);
  if (timeSinceBirthSec > _particalDelaySec && _flares->size() == 0)
  {
    int numberOfFlares = random8(MIN_FLARE_COUNT, MAX_FLARE_COUNT);
    while (--numberOfFlares > 0)
    {
      double velocity = randomFraction(MIN_VELOCITY_SEC, MAX_VELOCITY_SEC) * (random8(2) ? 1 : -1);
      _addFlare(velocity);
    }
  }
  _flash->update();
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
  _flash->render(canvas);
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
  isAlive |= _flash->isAlive();
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
  delete _flash;
  Flare *flare;
  while (_flares->size() > 0)
  {
    flare = _flares->remove(0);
    delete flare;
  }
  delete _flares;
}