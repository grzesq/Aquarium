#include "main.h"


String header;

void setup() 
{
    Serial.begin(115200);
    Serial.println("Start");
    
    config.init();
    
    lcd.init();
    lcd.turOn();
    
    lcd.displayMsg(" Connecting to WiFi");
    network.connectToWiFi();
    aquaTime = network.updateNtpTime();

    checkWorkingHours();
}

void loop() 
{
    currMillis = millis();
    bool isClient = false;
    if (network.isWiFiConnected())
    {
        WiFiClient client = network.getClient(); 

        if (client.connected())
        {
            web.request(client);
        }
        else if (currMillis - lastMillis > (1000*60) ||
                currMillis < lastMillis || lastMillis == 0)
        {
            updateTime();
            Serial.print("Check status ");
            Serial.print(aquaTime.H);
            Serial.print(":");
            Serial.println(aquaTime.M);
            
            lastMillis = currMillis;
        }
    }
    delay(100);
}

void updateTime()
{
    ntpUpdayeCounter++;
    if (ntpUpdayeCounter >= 30)
    {
        aquaTime = network.updateNtpTime();
        ntpUpdayeCounter = 0;
    }
    else
    {
        aquaTime.M++;

        if (aquaTime.M >= 60)
        {
            aquaTime.M = 0;
            aquaTime.H++;
        }

        if (aquaTime.H >= 23)
        {
            aquaTime.H = 0;
        }
    }
}

void checkWorkingHours()
{
    Serial.println("checkWorkingHours.");
    if (aquaTime.H >= config.StartH && aquaTime.H < config.EndH)
    {
        isWorking = true;
        Serial.println("Is working.");
    }
    else
    {
        isWorking = false;
    }
}