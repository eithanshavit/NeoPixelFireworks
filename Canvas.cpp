#include "Canvas.h"

Canvas::Canvas(
    CRGB *leds,
    uint numberOfLEDs,
    uint LEDsPerMeter,
    bool usesCyclicStrip)
{
  _numberOfLEDs = numberOfLEDs;
  _LEDsPerMeter = LEDsPerMeter;
  _usesCyclicStrip = usesCyclicStrip;
  _leds = leds;
}

void Canvas::setColorInMeterPosition(CRGB color, double meterPosition)
{
  int ledIndexPos = _ledIndexFromMeterPosition(meterPosition);
  if (ledIndexPos >= 0 && ledIndexPos < _numberOfLEDs)
  {
    _leds[ledIndexPos] = color;
  }
}

int Canvas::_ledIndexFromMeterPosition(double meterPosition)
{
  int index = floor(meterPosition * _LEDsPerMeter);
  if (_usesCyclicStrip)
  {
    index = (index % _numberOfLEDs + _numberOfLEDs) % _numberOfLEDs;
  }
  return index;
}