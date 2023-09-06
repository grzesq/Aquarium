#ifndef leds_h
#define leds_h

#include <Arduino.h>
#include "constans.h"
#include "structs.h"
#include "config.h"

short bluePower = LED_POWER[0];
short redPower = LED_POWER[0];
short extraPower = LED_POWER[0];

short bluePowerLvl = 0;
short redPowerLvl = 0;

void setupLeds();
void setLedPower();
void checkLedStatus();
void powerOffAll();
void checkBlueStatus();
void checkRedStatus();
void checkExtraStatus();
void setRelays();

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
    checkBlueStatus();
    checkRedStatus();
    checkExtraStatus();
    setLedPower();
}

void checkBlueStatus()
{
    if ((currTime.H == conf.BlueStartH &&  currTime.M >= conf.BlueStartM) ||
        (currTime.H == conf.BlueStopH &&  currTime.M < conf.BlueStopM) ||
        (currTime.H > conf.BlueStartH))
    {
        if (currTime.M % LED_LEVEL_CHANGE_BY_MIN == 0 
            && bluePowerLvl < MAX_LED_POW_LEVELS)
            bluePowerLvl++; 
    }
    else
    {
        if (currTime.M % LED_LEVEL_CHANGE_BY_MIN == 0 
            && bluePowerLvl > 0)
            bluePowerLvl--; 
    }
    bluePower = LED_POWER[bluePowerLvl];
}

void checkRedStatus()
{
    if ((currTime.H == conf.RedStartH &&  currTime.M >= conf.RedStartM) ||
        (currTime.H == conf.RedStopH &&  currTime.M < conf.RedStopM) ||
        (currTime.H > conf.RedStartH))
    {
        if (currTime.M % LED_LEVEL_CHANGE_BY_MIN == 0 
            && redPowerLvl < MAX_LED_POW_LEVELS)
            redPowerLvl++; 
    }
    else
    {
        if (currTime.M % LED_LEVEL_CHANGE_BY_MIN == 0 
            && redPowerLvl > 0)
            redPowerLvl--; 
    }
    redPower = LED_POWER[redPowerLvl];
}

void checkExtraStatus()
{
    if ((currTime.H == conf.ExtraStartH &&  currTime.M >= conf.ExtraStartM) ||
        (currTime.H == conf.ExtraStopH &&  currTime.M < conf.ExtraStopM) ||
        (currTime.H > conf.ExtraStartH))
    {
        extraPower = LED_POWER[2];
    }
    else
    {
        extraPower = LED_POWER[0];
    }
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

void setRelays()
{
    if (bluePower > 0)
        digitalWrite(PIN_R_BLUE, HIGH);
    else
        digitalWrite(PIN_R_BLUE, LOW);

    if (redPower > 0)
        digitalWrite(PIN_R_RED, HIGH);
    else
        digitalWrite(PIN_R_RED, LOW);

    if (extraPower > 0)
        digitalWrite(PIN_R_EXTRA, HIGH);
    else
        digitalWrite(PIN_R_EXTRA, LOW);
}

#endif