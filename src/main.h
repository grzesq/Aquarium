#include <Arduino.h>
#include <NTPClient.h>
#include "constans.h"
#include "config.h"
#include "WiFi.h"


struct CurrTime
{
    short H = 0;
    short M = 0;
} currTime;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
Config config;
hw_timer_t *ntpTimer = NULL;

unsigned long lastMillis = 0;

void setNtpTimer();
void setupPins();
void setupLeds();
void switchOffAllRelays();
void connectToWiFi();
void checkWiFi();
void getNtpTime();
bool isSummerTime(unsigned long secs);