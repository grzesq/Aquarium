#include "main.h"
#include "WiFi.h"

int dutyCycle;
const int LEDPin = 32;
const int PWMFreq = 500;
const int PWMChannel = 0;
const int PWMResolution = 8;
int knobValue1 = 0;

void setup() {
  ledcSetup(PWMChannel, PWMFreq, PWMResolution);
  ledcAttachPin(LEDPin, PWMChannel);
  ledcWrite(PWMChannel, 240);
  delay(1000);
  pinMode(PIN_R_BLUE , OUTPUT);
  digitalWrite(PIN_R_BLUE, HIGH);
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

void startWiFi()
{
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while ( WiFi.status() != WL_CONNECTED ) {
        delay ( 1000 );
    }
    //timeClient.begin();
    Serial.println( "" );
    Serial.println( "WIFI ON" );
}

void getNtpTime()
{
    timeClient.update();
    //timeHour = timeClient.getHours();
    //timeMin = timeClient.getMinutes();

//    if (isSummerTime(timeClient.getEpochTime())) timeHour++;

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
