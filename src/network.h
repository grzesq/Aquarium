#ifndef Constants_h
#define Constants_h

#include "WiFi.h"
#include <NTPClient.h>
#include "constans.h"
#include "structs.h"
#include "config.h"


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

void setNtpTimer();
void connectToWiFi();
void checkWiFi();
void getNtpTime();
bool isSummerTime(unsigned long secs);

//-------------------------------------------------------------------------------
//   FUNCTIONS
//-------------------------------------------------------------------------------
void checkWiFi()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.reconnect();
        Serial.println("WIFI reconnect");
    }
    else
    {
        Serial.println("WIFI connected (reconnect checked)");
    }
}

void connectToWiFi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while ( WiFi.status() != WL_CONNECTED ) {
        delay ( 1000 );
    }
    Serial.println("WIFI connected");
}

void getNtpTime()
{
    Serial.println("Get NTP time");
    checkWiFi();    

    timeClient.update();
    currTime.H = timeClient.getHours();
    currTime.M = timeClient.getMinutes();
    if (isSummerTime(timeClient.getEpochTime())) currTime.H++;
    Serial.print("H: ");
    Serial.println(currTime.H);
    Serial.print("M: ");
    Serial.println(currTime.M);
}

bool isSummerTime(unsigned long secs) 
{
    unsigned long rawTime = secs / 86400L;  // in days
    unsigned long days = 0, year = 1970;
    uint8_t month;
    static const uint8_t monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31};

    while((days += (LEAP_YEAR(year) ? 366 : 365)) <= rawTime)
    year++;
    rawTime -= days - (LEAP_YEAR(year) ? 366 : 365); // now it is days in this year, starting at 0
    days=0;
    for (month=0; month<12; month++) {
    uint8_t monthLength;
    if (month==1) { // february
        monthLength = LEAP_YEAR(year) ? 29 : 28;
    } else {
        monthLength = monthDays[month];
    }
    if (rawTime < monthLength) break;
        rawTime -= monthLength;
    }
    ++month;
    ++rawTime;
    
    String monthStr = month < 10 ? "0" + String(month) : String(month); // jan is month 1  
    String dayStr = rawTime < 10 ? "0" + String(rawTime) : String(rawTime); // day of month  

    bool st = false;

    if (month > 3 && month < 10) st = true;
    else if (month == 3 && rawTime >= 27) st = true;
    else if (month == 10 && rawTime < 27) st = true;
    
    return st;
}


#endif