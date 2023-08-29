#include <Arduino.h>
#include "constans.h"
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");


void startWiFi();
void getNtpTime();
bool isSummerTime(unsigned long secs);