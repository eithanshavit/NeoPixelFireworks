#include "Blast.h"

#include "Common.h"

#define MIN_FLARE_COUNT 25
#define MAX_FLARE_COUNT 45
#define MIN_VELOCITY_SEC 0.4
#define MAX_VELOCITY_SEC 3
#define MIN_FLASH_DURATION_SEC 0.3
#define MAX_FLASH_DURATION_SEC 0.7

Blast::Blast(double positionMeters)
{
  _timeOfBirth = millis();
  _flashDurationSec = randomFraction(MIN_FLASH_DURATION_SEC, MAX_FLASH_DURATION_SEC);
  _flash = new Flash(positionMeters, _flashDurationSec);
  _flares = new LinkedList<Flare *>();
  _postionMeters = positionMeters;
  _color = CHSV(random8(), 255, 255);
}

void Blast::update()
{
  double timeSinceBirthSec = timeToSec(millis() - _timeOfBirth);
  if (timeSinceBirthSec > _flashDurationSec && _flares->size() == 0)
  {
    int numberOfFlares = random8(MIN_FLARE_COUNT, MAX_FLARE_COUNT);
    while (--numberOfFlares > 0)
    {
      double velocity = randomFraction(MIN_VELOCITY_SEC, MAX_VELOCITY_SEC) * (random8(2) ? 1 : -1);
      _addFlare(velocity);
    }
  }
  if (_flash)
  {
    _flash->update();
  }
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
  if (_flash)
  {
    _flash->render(canvas);
  }
}

bool Blast::isAlive()
{
  for (int i = 0; i < _flares->size(); i++)
  {
    Flare *f = _flares->get(i);
    if (f->isAlive())
    {
      return true;
    }
  }
  if (_flares->size() == 0)
  {
    return true;
  }
  if (_flash && _flash->isAlive())
  {
    return true;
  }
  return false;
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