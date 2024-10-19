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

void Leds::checkLedStatus(Time t)
{
    checkW1Status();
    checkW2Status();
    checkFsStatus();
    setLedPower();
}

void Leds::checkW1Status()
{}

void Leds::checkW2Status()
{}

void Leds::checkFsStatus()
{}

void Leds::setLedPower()
{}

LightPower Leds::getPower()
{
    return lightPower;
}