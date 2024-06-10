#ifndef leds_h
#define leds_h

#include <Arduino.h>
#include "constans.h"
#include "structs.h"
#include "config.h"

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
    ledcAttachPin(PIN_LED_RED, PWM_RED_CHANNEL);
    ledcAttachPin(PIN_LED_EXTRA, PWM_EXTRA_CHANNEL);

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
        (currTime.H > conf.BlueStartH && currTime.H < conf.BlueStopH))
    {
        if (currTime.H > conf.BlueStartH + 1 && bluePowerLvl < 6)
        {
            bluePowerLvl = 6;
        }
        
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
    conf.BluePower = LED_POWER[bluePowerLvl];
}

void checkRedStatus()
{
    if ((currTime.H == conf.RedStartH &&  currTime.M >= conf.RedStartM) ||
        (currTime.H == conf.RedStopH &&  currTime.M < conf.RedStopM) ||
        (currTime.H > conf.RedStartH && currTime.H < conf.RedStopH))
    {
        if (currTime.H > conf.RedStartH + 1 && redPowerLvl < 6)
        {
            redPowerLvl = 6;
        }

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
    conf.RedPower = LED_POWER[redPowerLvl];
}

void checkExtraStatus()
{
    if ((currTime.H >= conf.ExtraFullStartH && currTime.H < conf.ExtraFullStopH))
    {
        conf.ExtraPower = LED_POWER[5];
    }
    else if ((currTime.H == conf.ExtraStartH && currTime.M >= conf.ExtraStartM) ||
        (currTime.H == conf.ExtraStopH && currTime.M < conf.ExtraStopM) ||
        (currTime.H > conf.ExtraStartH))
    {
        conf.ExtraPower = LED_POWER[2];
    }
    else

    {
        conf.ExtraPower = LED_POWER[0];
    }
}

void powerOffAll()
{
    conf.BluePower = LED_POWER[0];
    conf.RedPower = LED_POWER[0];
    conf.ExtraPower = LED_POWER[0];
    setLedPower();
}

void setLedPower()
{
    Serial.print("Blue Power: ");
    Serial.println(conf.BluePower);
    Serial.print("Red Power: ");
    Serial.println(conf.RedPower);
    Serial.print("Extra Power: ");
    Serial.println(conf.ExtraPower);
    ledcWrite(PWM_BLUE_CHANNEL, conf.BluePower);
    ledcWrite(PWM_RED_CHANNEL, conf.RedPower);
    ledcWrite(PWM_EXTRA_CHANNEL, conf.ExtraPower);
    delay(500);
    setRelays();
}

void setRelays()
{
    if (conf.BluePower == LED_POWER[0])
        digitalWrite(PIN_R_BLUE, HIGH);
    else
        digitalWrite(PIN_R_BLUE, LOW);

    if (conf.RedPower == LED_POWER[0])
        digitalWrite(PIN_R_RED, HIGH);
    else
        digitalWrite(PIN_R_RED, LOW);

    if (conf.ExtraPower == LED_POWER[0])
        digitalWrite(PIN_R_EXTRA, HIGH);
    else
        digitalWrite(PIN_R_EXTRA, LOW);
}

#endif