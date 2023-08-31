#include "main.h"

int dutyCycle;

int knobValue1 = 0;

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
        updateNtp();

        lastMillis = currMillis;
    }
}

void updateNtp()
{
    ntpUpdayeCounter++;
    if (ntpUpdayeCounter >= 30)
    {
        getNtpTime();
        ntpUpdayeCounter = 0;
    }
}

void switchOffAllRelays()
{
    digitalWrite(PIN_R_BLUE, LOW);
    digitalWrite(PIN_R_RED, LOW);
    digitalWrite(PIN_R_EXTRA, LOW);
    digitalWrite(PIN_R_CO2, LOW);
}

