#ifndef Canvas_h
#define Canvas_h

#include <FastLED.h>

class Canvas
{
  public:
    Canvas(
      CRGB *leds,
      uint numberOfLEDs,
      uint LEDsPerMeter,
      bool usesCyclicStrip);
    void setColorInMeterPosition(CRGB color, double positionMeter);

  private:
    unsigned int _numberOfLEDs;
    unsigned int _LEDsPerMeter;
    CRGB *_leds;
    bool _usesCyclicStrip;
    int _ledIndexFromMeterPosition(double meterPosition);
};

#endif
