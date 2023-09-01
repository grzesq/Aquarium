#include "main.h"


void setup() {
    Serial.begin(115200);
    Serial.println("Start");

    setupPins();
    switchOffAllRelays();
    
    setupLeds();

    connectToWiFi();
    getNtpTime();
    
    Serial.println("Rady.");
    lastMillis=millis();
}

void setupPins()
{
    pinMode(PIN_R_BLUE , OUTPUT);
    pinMode(PIN_R_RED , OUTPUT);
    pinMode(PIN_R_EXTRA , OUTPUT);
    pinMode(PIN_R_CO2 , OUTPUT);
}

void loop() {
    currMillis = millis();

    if (currMillis - lastMillis > (1000*60) || 
        currMillis < lastMillis)
    {
        isWorkinglast = isWorking;
        checkWorkingHours();
        updateTime();
        
        if (isWorkinglast != isWorking)
            switchWorkingStatus();
        else if (isWorking)
            checkSystemStatus();

        lastMillis = currMillis;
    }
}

void checkSystemStatus()
{
    checkLedStatus();
    checkCo2Status();
}

void switchWorkingStatus()
{
    if (!isWorking)
    {
        switchOffAllRelays();
        powerOffAll();
    }
    else
    {
        checkSystemStatus();
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
        digitalWrite(PIN_R_CO2, HIGH);
    else
        digitalWrite(PIN_R_CO2, LOW);
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
    if (currTime.H >= conf.StartH && currTime.H < conf.EndH)
        isWorking = true;
    else
        isWorking = false;
}