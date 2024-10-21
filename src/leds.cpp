#include <Arduino.h>
#include "leds.h"


const int PWM_FREQ = 5000;
const int PWM_RESOLUTION = 	10;
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 

const int PWM_W1_CHANNEL = 0;
const int PWM_W2_CHANNEL  = 1;
const int PWM_FS_CHANNEL = 2;

const int PIN_LED_W1 = 33;                                                                                                                                                                                                                                                                                                     ;
const int PIN_LED_W2  = 25;
const int PIN_LED_FS = 32;

const short STEP = 5;

Leds::Leds(Config& c)
{
    conf = &c;
}

void Leds::init()
{
    ledcSetup(PWM_W1_CHANNEL, PWM_FREQ, PWM_RESOLUTION);\
    ledcSetup(PWM_W2_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(PWM_FS_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    
    ledcAttachPin(PIN_LED_W1, PWM_W1_CHANNEL);
    ledcAttachPin(PIN_LED_W2, PWM_W2_CHANNEL);
    ledcAttachPin(PIN_LED_FS, PWM_FS_CHANNEL);
}

LightPower Leds::getLedsStatus(Time& t)
{
    checkW1Status(t);
    checkW2Status(t);
    checkFsStatus(t);
    setLedPower();
    return lightPower;
}

void Leds::checkW1Status(Time& t)
{
    WorkTime wt = conf->getWhite1();
    lightPower.W1 = setPower(t, wt, lightPower.W1);
}

void Leds::checkW2Status(Time& t)
{
    WorkTime wt = conf->getWhite2();
    lightPower.W2 = setPower(t, wt, lightPower.W2);
}

void Leds::checkFsStatus(Time& t)
{
    WorkTime wt = conf->getWhite2();
    lightPower.FS = setPower(t, wt, lightPower.FS);
}

short Leds::setPower(Time& t, WorkTime& wt, short pow)
{
    if ((t.H == wt.BH &&  t.M >= wt.BM) ||
        (t.H == wt.EH &&  t.M < wt.EM) ||
        (t.H > wt.BH && t.H < wt.EH))
    {
        if (pow == 0 && t.H > wt.BH)
        {
            return (int)(wt.P/2);
        }
        else
        {
            pow += STEP;
            if (pow > wt.P) return wt.P;
        }
    }
    else
    {
        if (pow > 0)
        {
            pow -= STEP;
            if (pow < 0) pow = 0;
            return pow;
        }
    }
    return 0;
}

void Leds::powerOffAll()
{
    lightPower.FS = 0;
    lightPower.W1 = 0;
    lightPower.W2 = 0;
    setLedPower();
}

void Leds::setLedPower()
{
    Serial.print("W1 Power: ");
    Serial.println(lightPower.W1);
    Serial.print("W2 Power: ");
    Serial.println(lightPower.W2);
    Serial.print("FS Power: ");
    Serial.println(lightPower.FS);
    ledcWrite(PWM_W1_CHANNEL, lightPower.W1);
    ledcWrite(PWM_W2_CHANNEL, lightPower.W2);
    ledcWrite(PWM_FS_CHANNEL, lightPower.FS);
    delay(50);
}

LightPower Leds::getPower()
{
    return lightPower;
}

int Leds::getPower(short p)
{
    return (int)(MAX_DUTY_CYCLE * p / 100);
}