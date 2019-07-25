#include "Common.h"

#include <FastLED.h>

double randomFraction(double min, double max)
{
    return (double(random8()) / 255 * (max - min)) + min;
}

double timeToSec(unsigned long time)
{
    return time / 1000.0;
}