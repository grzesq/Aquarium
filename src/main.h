#include <Arduino.h>
#include "network.h"
#include "leds.h"

unsigned long lastMillis = 0;
unsigned long currMillis = 0;

short ntpUpdayeCounter = 0;

void setupPins();
void switchOffAllRelays();
void updateNtp();
