#include "Flash.h"

#include "Common.h"

#define MIN_FLASH_DURATION_SEC 3
#define MAX_FLASH_DURATION_SEC 4

Flash::Flash(double positionMeters)
{
  _timeOfBirth = millis();
  _postionMeters = positionMeters;
  _durationSec = randomFraction(MIN_FLASH_DURATION_SEC, MAX_FLASH_DURATION_SEC);
}

bool Flash::isAlive()
{
  unsigned long timeSinceBirthSec = timeToSec(millis() - _timeOfBirth);
  return timeSinceBirthSec < _durationSec;
}

void Flash::update()
{
  unsigned long timeSinceBirth = timeToSec(millis() - _timeOfBirth);
}

void Flash::render(Canvas *canvas)
{
  canvas->setColorInMeterPosition(CRGB::White, _postionMeters);
}