#ifndef leds_h
#define leds_h

#include <Arduino.h>
#include "constans.h"
#include "structs.h"
#include "config.h"

short bluePower = LED_POWER[0];
short redPower = LED_POWER[0];
short extraPower = LED_POWER[0];

void setupLeds();
void checkLedStatus();
void powerOffAll();
void checkBlueStatus();
void checkRedStatus();
void checkExtraStatus();

//-------------------------------------------------------------------------------
//   FUNCTIONS
//-------------------------------------------------------------------------------

void setupLeds()
{
    ledcSetup(PWM_BLUE_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(PWM_RED_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    ledcSetup(PWM_EXTRA_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
    
    ledcAttachPin(PIN_LED_BLUE, PWM_BLUE_CHANNEL);
    ledcAttachPin(PIN_LED_RED, PWM_BLUE_CHANNEL);
    ledcAttachPin(PIN_LED_EXTRA, PWM_BLUE_CHANNEL);

    powerOffAll();
}


void checkLedStatus()
{
    setLedPower();
}

void checkBlueStatus()
{

}

void checkRedStatus()
{

}

void checkExtraStatus()
{

}

void powerOffAll()
{
    bluePower = LED_POWER[0];
    redPower = LED_POWER[0];
    extraPower = LED_POWER[0];
    setLedPower();
}

void setLedPower()
{
    ledcWrite(PWM_BLUE_CHANNEL, bluePower);
    ledcWrite(PWM_RED_CHANNEL, redPower);
    ledcWrite(PWM_RED_CHANNEL, extraPower);
}

#endif