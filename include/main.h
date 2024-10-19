#include <Arduino.h>
#include "constans.h"
#include "structs.h"
#include "network.h"
#include "web.h"
#include "config.h"
#include "lcd.h"
#include "leds.h"

Network network;
Config config;
Web web(config);
Lcd lcd;
Leds leds(config);

const int PIN_R_W1 = 18;
const int PIN_R_W2  = 5 ;
const int PIN_R_FS = 19;
const int PIN_R_CO2 = 17;

Time aquaTime;
unsigned long lastMillis = 0;
unsigned long currMillis = 0;
short ntpUpdayeCounter = 0;
bool isWorking = false;
bool isWorkinglast = false;

void updateTime();
void checkWorkingHours();
void switchWorkingStatus();
bool checkCo2Status();
void checkSystemStatus();
void switchOffAllRelays();
void setRelays(LightPower p);
/*
short ntpUpdayeCounter = 0;
*/
