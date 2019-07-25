#include <FastLED.h>
#include <LinkedList.h>

#include "Flare.h"
#include "Blast.h"

// Physics
#define LEDS_PER_METER 30
#define FRAMES_PER_SECOND 60

// LEDS
#define LED_PIN 6
#define COLOR_ORDER GRB
#define CHIPSET WS2812B
#define NUM_LEDS 150
#define BRIGHTNESS 200
#define USE_CYCLIC_STRIP false
CRGB leds[NUM_LEDS];

// Blasts
#define BLAST_PROBABILITY_PERCENT 10
#define MAX_BLAST_COUNT 5
#define BLAST_CREATION_LIMIT_AREA 2
#define BLAST_CREATION_LIMIT_TIME_SEC 2
LinkedList<Blast *> blasts = LinkedList<Blast *>();
double lastBlastLocation = 0;
unsigned long timeOfLastBlast = 0;

void setup()
{
  Serial.begin(115200);
  LEDS.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  LEDS.setBrightness(BRIGHTNESS);
  randomSeed(analogRead(0));
}

void loop()
{
  Serial.print(millis());
  Serial.println(": looping");
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
    unsigned long currentTime = millis();
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
    for (int j = 0; j < blast->flaresCount(); j++)
    {
      Flare *f = blast->getFlares()->get(j);
      double positionMeters = f->getPositionMeters();
      int ledIndexPos = ledIndexFromPositionMeters(positionMeters);
      if (ledIndexPos >= 0 && ledIndexPos < NUM_LEDS)
      {
        leds[ledIndexPos] = f->getColor();
      }
    }
  }
}

int ledIndexFromPositionMeters(double posInMeters)
{
  int index = floor(posInMeters * LEDS_PER_METER);
  if (USE_CYCLIC_STRIP)
  {
    return (index % NUM_LEDS + NUM_LEDS) % NUM_LEDS;
  }
  else
  {
    return index;
  }
}
