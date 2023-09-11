#include "main.h"


void setup() {
    Serial.begin(115200);
    Serial.println("Start");
    setupPins();

    switchOffAllRelays();
    inidLcd();
    display();

    setupLeds();
    turOnLcd();

    displayMsg(" Connecting to WiFi");
    connectToWiFi();
    getNtpTime();
    
    Serial.println("Rady.");
    lastMillis=0;
}

void setupPins()
{
    pinMode(PIN_R_BLUE , OUTPUT);
    pinMode(PIN_R_RED , OUTPUT);
    pinMode(PIN_R_EXTRA , OUTPUT);
    pinMode(PIN_R_CO2 , OUTPUT);
}

void loop() 
{
    currMillis = millis();

    if (currMillis - lastMillis > (1000*60) || 
        currMillis < lastMillis ||
        lastMillis == 0)
    {
        Serial.println("loop.");
        isWorkinglast = isWorking;
        checkWorkingHours();
        updateTime();
        
        if (isWorkinglast != isWorking)
            switchWorkingStatus();
        
        if (isWorking)
            checkSystemStatus();

        isWorkinglast = isWorking;
        lastMillis = currMillis;
    }
}

void checkSystemStatus()
{
    Serial.println("check system status.");
    checkLedStatus();
    checkCo2Status();
    display();
}

void switchWorkingStatus()
{
    if (!isWorking)
    {
        switchOffAllRelays();
        powerOffAll();
        turOffLcd();
    }
    else
    {
        checkSystemStatus();
        turOnLcd();
    }
}

void updateClock()
{
    currTime.M++;

    if (currTime.M >= 60)
    {
        currTime.M = 0;
        currTime.H++;
    }

    if (currTime.H >= 23)
    {
        currTime.H = 0;
    }
}

void updateTime()
{
    ntpUpdayeCounter++;
    if (ntpUpdayeCounter >= 30)
    {
        getNtpTime();
        ntpUpdayeCounter = 0;
    }
    else
    {
        updateClock();
    }
}

void checkCo2Status()
{
    if (currTime.H >= conf.Co2Start && currTime.H < conf.Co2Stop)
    {
        digitalWrite(PIN_R_CO2, HIGH);
        Serial.println("Co2 On");
        conf.Co2Satus = 1;
    }
    else
    {
        digitalWrite(PIN_R_CO2, LOW);
        Serial.println("Co2 Off");
        conf.Co2Satus = 0;
    }
}

void switchOffAllRelays()
{
    digitalWrite(PIN_R_BLUE, LOW);
    digitalWrite(PIN_R_RED, LOW);
    digitalWrite(PIN_R_EXTRA, LOW);
    digitalWrite(PIN_R_CO2, LOW);
}

void checkWorkingHours()
{
    Serial.println("checkWorkingHours.");
    if (currTime.H >= conf.StartH && currTime.H < conf.EndH)
    {
        isWorking = true;
        Serial.println("Is working.");
    }
    else
    {
        isWorking = false;
    }
}