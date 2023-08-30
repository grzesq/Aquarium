#include "main.h"

int dutyCycle;

int knobValue1 = 0;

void setup() {
    Serial.println("Start");

    setupPins();
    switchOffAllRelays();
    
    setupLeds();
    connectToWiFi();
    getNtpTime();


    lastMillis=millis();
}

void setupPins()
{
    pinMode(PIN_R_BLUE , OUTPUT);
    pinMode(PIN_R_RED , OUTPUT);
    pinMode(PIN_R_EXTRA , OUTPUT);
    pinMode(PIN_R_CO2 , OUTPUT);
}

void setupLeds()
{
    ledcSetup(PWM_BLUE_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(PWM_RED_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(PWM_EXTRA_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    
    ledcAttachPin(PIN_LED_BLUE, PWM_BLUE_CHANNEL);
    ledcAttachPin(PIN_LED_RED, PWM_BLUE_CHANNEL);
    ledcAttachPin(PIN_LED_EXTRA, PWM_BLUE_CHANNEL);
}

void setNtpTimer()
{
    ntpTimer = timerBegin(0, 80, true);
    timerAttachInterrupt(ntpTimer, &getNtpTime, true);
    timerAlarmWrite(ntpTimer, (1000000 * 60) * 5, true);
    timerAlarmEnable(ntpTimer);    
}


void loop() {
/*  for(dutyCycle = 0; dutyCycle <= MAX_DUTY_CYCLE; dutyCycle++)
  {
    ledcWrite(PWMChannel, dutyCycle);
    delay(25);
    //delayMicroseconds(100);
  }
  for(dutyCycle = MAX_DUTY_CYCLE; dutyCycle >= 0; dutyCycle--)
  {
    ledcWrite(PWMChannel, dutyCycle);
    delay(25);
    //delayMicroseconds(100);
  }*/
}



void switchOffAllRelays()
{
    digitalWrite(PIN_R_BLUE, LOW);
    digitalWrite(PIN_R_RED, LOW);
    digitalWrite(PIN_R_EXTRA, LOW);
    digitalWrite(PIN_R_CO2, LOW);
}

void checkWiFi()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.reconnect();
        Serial.println("WIFI reconect");
    }
    else
    {
        Serial.println("WIFI connected nor reconect");
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
    
    timeClient.update();
    currTime.H = timeClient.getHours();
    currTime.M = timeClient.getMinutes();
    if (isSummerTime(timeClient.getEpochTime())) currTime.H++;
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
