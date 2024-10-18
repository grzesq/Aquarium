#pragma once

#ifndef constants_h
#define constants_h

const int PWM_FREQ = 5000;
const int PWM_RESOLUTION = 	10;
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 

const int PWM_BLUE_CHANNEL = 0;
const int PWM_RED_CHANNEL  = 1;
const int PWM_EXTRA_CHANNEL = 2;

const int PIN_LED_BLUE = 33;                                                                                                                                                                                                                                                                                                     ;
const int PIN_LED_RED  = 25;
const int PIN_LED_EXTRA = 32;

const int PIN_R_BLUE = 18;
const int PIN_R_RED  = 5 ;
const int PIN_R_EXTRA = 19;
const int PIN_R_CO2 = 17;



#endif 