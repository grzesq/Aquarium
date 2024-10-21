#include "main.h"


String header;

void setup() 
{
    Serial.begin(115200);
    Serial.println("Start");
    switchOffAllRelays();

    config.init();
    lcd.init();
    lcd.turOn();
    leds.init();
    
    lcd.displayMsg(" Connecting to WiFi");
    network.connectToWiFi();
    aquaTime = network.updateNtpTime();

    setSystem();
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
            setSystem();
            lastMillis = currMillis;
        }
    }
    delay(100);
}

void setSystem()
{
    isWorkinglast = isWorking;
    updateTime();
    checkWorkingHours();

    if (isWorkinglast != isWorking)
        switchWorkingStatus();

    if (isWorking)
        checkSystemStatus();
}

void switchWorkingStatus()
{
    if (!isWorking)
    {
        Serial.println("Out of hours.");
        switchOffAllRelays();
        leds.powerOffAll();
        lcd.turOff();
    }
    else
    {
        checkSystemStatus();
        lcd.turOn();
    }
}

bool checkCo2Status()
{
    WorkTime t = config.getCo2();

    if ((aquaTime.H == t.BH &&  aquaTime.M >= t.BM) ||
        (aquaTime.H == t.EH &&  aquaTime.M < t.EM) ||
        (aquaTime.H > t.BH &&  aquaTime.H < t.EH))
    {
        digitalWrite(PIN_R_CO2, LOW);
        Serial.println("Co2 On");
        return true;
    }
    else
    {
        digitalWrite(PIN_R_CO2, HIGH);
        Serial.println("Co2 Off");
        return false;
    }
}

void checkSystemStatus()
{
    Serial.print("Check status ");
    Serial.print(aquaTime.H);
    Serial.print(":");
    Serial.println(aquaTime.M);

    LightPower p = leds.getLedsStatus(aquaTime);
    setRelays(p);
    
    bool c2 = checkCo2Status();
    lcd.display(aquaTime, p, c2);

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

void switchOffAllRelays()
{
    digitalWrite(PIN_R_W1, HIGH);
    digitalWrite(PIN_R_W2, HIGH);
    digitalWrite(PIN_R_FS, HIGH);
    digitalWrite(PIN_R_CO2, HIGH);
}

void setRelays(LightPower p)
{
    p.W1 == 0 ? digitalWrite(PIN_R_W1, HIGH) :
                digitalWrite(PIN_R_W1, LOW);

    p.W2 == 0 ? digitalWrite(PIN_R_W2, HIGH) :
                digitalWrite(PIN_R_W2, LOW);

    p.FS == 0 ? digitalWrite(PIN_R_FS, HIGH) :
                digitalWrite(PIN_R_FS, LOW);
}