#include "Flash.h"

#include "Common.h"

#define EXPLODE_IMPLODE_TIME_RATIO 0.8
#define MAX_EXPLODE_RADIUS_METER 0.06
#define MIN_EXPLODE_RADIUS_METER 0.2

Flash::Flash(CHSV color, double positionMeters, double durationSec)
{
  _timeOfBirth = millis();
  _positionMeters = positionMeters;
  _durationSec = durationSec;
  _explodeDurationSec = durationSec * EXPLODE_IMPLODE_TIME_RATIO;
  _implodeDurationSec = durationSec - _explodeDurationSec;
  _maxRadiusMeter = randomFraction(MIN_EXPLODE_RADIUS_METER, MAX_EXPLODE_RADIUS_METER);
  _color = color;
}

bool Flash::isAlive()
{
  double timeSinceBirthSec = timeToSec(millis() - _timeOfBirth);
  return timeSinceBirthSec < _durationSec;
}

void Flash::update()
{
  double timeSinceBirthSec = timeToSec(millis() - _timeOfBirth);
  double fractionOfProcessStage;
  if (timeSinceBirthSec < _explodeDurationSec)
  {
    double fractionOfExplode = timeSinceBirthSec / _explodeDurationSec;
    fractionOfProcessStage = _explodeFractionByTime(fractionOfExplode);
  }
  else
  {
    double fractionOfImplode = min(1, (timeSinceBirthSec - _explodeDurationSec) / _implodeDurationSec);
    fractionOfProcessStage = _implodeFractionByTime(fractionOfImplode);
  }
  //_color = CHSV(255, 0, fractionOfProcessStage * 255);
  _color.sat = fractionOfProcessStage * 255;
  _color.val = fractionOfProcessStage * 255;
  _radiusMeter = _maxRadiusMeter * fractionOfProcessStage;
}

void Flash::render(Canvas *canvas)
{
  if (!isAlive())
  {
    return;
  }
  canvas->setColorInMeterPositionWithRadius(_color, _positionMeters, _radiusMeter);
}

double Flash::_explodeFractionByTime(double timeFraction)
{
  return (double(ease8InOutQuad(127 + timeFraction * 128)) - 126.0) / 129.0;
}

double Flash::_implodeFractionByTime(double timeFraction)
{
  return (255.0 - double(ease8InOutQuad(timeFraction * 128))) / 255.0;
}