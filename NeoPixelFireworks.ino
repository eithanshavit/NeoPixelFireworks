#include <FastLED.h>
#include <LinkedList.h>

#include "Flare.h"
#include "Blast.h"

// Physics
#define LEDS_PER_METER 10
#define FRAMES_PER_SECOND 60

// LEDS
#define LED_PIN     6
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define NUM_LEDS    150
#define BRIGHTNESS  200
CRGB leds[NUM_LEDS];

// Blasts
#define BLAST_PROBABILITY_PERCENT 4
#define MAX_BLAST_COUNT 5
LinkedList<Blast *> blasts = LinkedList<Blast *>();

// DEBUG
#define CREATE_BLAST_EVERY_SECONDS 1
unsigned long framemNumber;

void setup() 
{ 
    Serial.begin(115200);
    LEDS.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    LEDS.setBrightness(BRIGHTNESS);
    randomSeed(analogRead(0));

    // DEBUG
    framemNumber = 0;
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
    framemNumber++;
    FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void createBlasts() 
{
    if (0 && framemNumber % (CREATE_BLAST_EVERY_SECONDS * FRAMES_PER_SECOND) == 0) {
        blasts.add(new Blast(7));
    }
    if (random(101) < BLAST_PROBABILITY_PERCENT && blasts.size() < MAX_BLAST_COUNT) {
        blasts.add(new Blast(random(NUM_LEDS / LEDS_PER_METER)));
    }
}

void sanitizeBlasts() 
{
    Blast *blast;
    int i=0;
    while (i < blasts.size()) {
        blast = blasts.get(i);
        if (blast->isAlive()) {
            i++;
        } else {
            blasts.remove(i);
            delete blast;
        }
    }
}

void animateBlasts() 
{
    Blast *blast;
    for (int i = 0; i < blasts.size(); i++) {
        blast = blasts.get(i);
        for (int j = 0; j < blast->flaresCount(); j++) {
            Flare *f = blast->getFlares()->get(j);
            f->update();
            double positionMeters = f->getPositionMeters();
            int ledIndexPos = ledIndexFromPositionMeters(positionMeters);
            if (ledIndexPos >=0 && ledIndexPos < NUM_LEDS) {
                leds[ledIndexPos] = f->getColor();
            }
        }
    }
}

int ledIndexFromPositionMeters(double posInMeters)
{
    int index = floor(posInMeters * LEDS_PER_METER);
    return index;
    // Uncomment for cyclic
    // return (index % NUM_LEDS + NUM_LEDS) % NUM_LEDS;
}
