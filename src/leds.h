#ifndef leds_h
#define leds_h

#include <Arduino.h>
#include "constans.h"
#include "structs.h"
#include "config.h"

void setupLeds();

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
}


#endif