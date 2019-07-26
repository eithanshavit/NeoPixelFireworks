#include "Common.h"

#include <FastLED.h>

double randomFraction(double min, double max)
{
  return (double(random8()) / 255 * (max - min)) + min;
}

double timeToSec(double time)
{
  return time / 1000.0;
}