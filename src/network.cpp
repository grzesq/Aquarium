#include "network.h"

const char* WIFI_SSID     = "meg-home";
const char* WIFI_PASSWORD = "MateuszeK2003";
const char* NTP_SERVER    = "pool.ntp.org";
const IPAddress LOCAL_IP(192,168,5,99);
const IPAddress GATEWAY(192,168,4,1);
const IPAddress SUBNET(255,255,254,0);
const IPAddress DNS1(8,8,8,8);
const IPAddress DNS2(1,1,1,1);

#define LEAP_YEAR(Y)     ( (Y>0) && !(Y%4) && ( (Y%100) || !(Y%400) ) )

Network::Network()
{
    timeClient = new NTPClient(ntpUDP, NTP_SERVER);
}

Network::~Network()
{
    delete timeClient;
}

bool Network::isWiFiConnected()
{
    return  WiFi.status() == WL_CONNECTED;
}

void Network::checkWiFi()
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

WiFiClient Network::getClient()
{
    return  webServer.available();
}

void Network::connectToWiFi()
{
    if (!WiFi.config(LOCAL_IP, GATEWAY, SUBNET, DNS1, DNS2)) {
     Serial.println("STA Failed to configure");
    }
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while ( WiFi.status() != WL_CONNECTED ) {
        Serial.println("WIFI try connecting ....");
        delay ( 2000 );
    }
    webServer.begin();
    Serial.println("WIFI connected");
}

Time Network::updateNtpTime()
{
    Time lastTime;
    
    checkWiFi();
    Serial.println("Get NTP time");
    timeClient->update();
    lastTime.H = timeClient->getHours();
    lastTime.M = timeClient->getMinutes();
    lastTime.S = timeClient->getSeconds();
    
    if (isSummerTime(timeClient->getEpochTime()))
    {
        lastTime.H++;
    }

    return lastTime;
}

bool Network::isSummerTime(unsigned long secs) 
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