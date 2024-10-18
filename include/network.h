#pragma once

#ifndef Network_h
#define Network_h

#include <NTPClient.h>
#include <WebServer.h>
#include "WiFi.h"
#include "structs.h"

class Network
{
    public:
        Network();
        ~Network();

        void connectToWiFi();
        void checkWiFi();
        Time updateNtpTime();
        bool isWiFiConnected();
        WiFiClient getClient();
    
    private:
        WiFiServer webServer;
        WiFiUDP ntpUDP;
        NTPClient* timeClient;

    private:
        void setNtpTimer();
        bool isSummerTime(unsigned long secs);
};

#endif