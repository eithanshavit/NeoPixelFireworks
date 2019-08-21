#include <FastLED.h>
#include <LinkedList.h>

#include "Flare.h"
#include "Blast.h"
#include "Canvas.h"

// Physics
#define LEDS_PER_METER 15
#define FRAMES_PER_SECOND 200

// LEDS
#define LED_PIN_1 0
#define LED_PIN_2 2
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define BRIGHTNESS 250
#define USE_CYCLIC_STRIP true
#define NUM_STRIPS 2
#define NUM_LEDS_PER_STRIP 240
#define NUM_LEDS NUM_LEDS_PER_STRIP *NUM_STRIPS
CRGB leds[NUM_LEDS];

// Blasts
#define BLAST_PROBABILITY_PERCENT 15
#define MAX_BLAST_COUNT 6
#define BLAST_CREATION_LIMIT_AREA 2
#define BLAST_CREATION_LIMIT_TIME_SEC 2
LinkedList<Blast *> blasts = LinkedList<Blast *>();
double lastBlastLocation = 0;
double timeOfLastBlast = 0;

// Canvas
Canvas canvas = Canvas(leds, NUM_LEDS, LEDS_PER_METER, USE_CYCLIC_STRIP);

void setup()
{
  Serial.begin(115200);
  LEDS.addLeds<CHIPSET, LED_PIN_1, COLOR_ORDER>(leds, 0, NUM_LEDS_PER_STRIP);
  LEDS.addLeds<CHIPSET, LED_PIN_2, COLOR_ORDER>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  LEDS.setBrightness(BRIGHTNESS);
  randomSeed(analogRead(0));
}

void loop()
{
  FastLED.clear();
  sanitizeBlasts();
  createBlasts();
  animateBlasts();
  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void createBlasts()
{
  if (random(101) < BLAST_PROBABILITY_PERCENT && blasts.size() < MAX_BLAST_COUNT)
  {
    double currentTime = millis();
    double newLocation = (double(random8(101)) / 100) * (NUM_LEDS / LEDS_PER_METER);
    if (abs(newLocation - lastBlastLocation) > BLAST_CREATION_LIMIT_AREA || (currentTime - timeOfLastBlast) / 1000 > BLAST_CREATION_LIMIT_TIME_SEC)
    {
      blasts.add(new Blast(newLocation));
      lastBlastLocation = newLocation;
      timeOfLastBlast = millis();
    }
  }
}

void sanitizeBlasts()
{
  Blast *blast;
  int i = 0;
  while (i < blasts.size())
  {
    blast = blasts.get(i);
    if (blast->isAlive())
    {
      i++;
    }
    else
    {
      blasts.remove(i);
      delete blast;
    }
  }
}

void animateBlasts()
{
  Blast *blast;
  for (int i = 0; i < blasts.size(); i++)
  {
    blast = blasts.get(i);
    blast->update();
    blast->render(&canvas);
  }
}