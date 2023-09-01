#include <Arduino.h>
#include "network.h"
#include "leds.h"

unsigned long lastMillis = 0;
unsigned long currMillis = 0;

short ntpUpdayeCounter = 0;

bool isWorking = false;
bool isWorkinglast = false;

void setupPins();
void switchOffAllRelays();
void updateTime();
void isWorkingHours();
void updateClock();
void switchWorkingStatus();
void checkCo2Status();
void checkSystemStatus();