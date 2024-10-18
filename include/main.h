#include <Arduino.h>
#include "structs.h"
#include "network.h"
#include "web.h"
#include "config.h"
#include "lcd.h"

Network network;
Config config;
Web web(config);
Lcd lcd;

Time aquaTime;
unsigned long lastMillis = 0;
unsigned long currMillis = 0;
short ntpUpdayeCounter = 0;
bool isWorking = false;

void updateTime();
void checkWorkingHours();

/*
short ntpUpdayeCounter = 0;


bool isWorkinglast = false;
*/