#ifndef constants_h
#define constants_h

#define LEAP_YEAR(Y)     ( (Y>0) && !(Y%4) && ( (Y%100) || !(Y%400) ) )

const int PWM_FREQ = 500;
const int PWM_RESOLUTION = 8;

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

const int MAX_DUTY_CYCLE = 255;
const int LED_LEVELS = 12;

const int LED_LEVEL_CHANGE_BY_MIN = 3;
const int MAX_LED_POW_LEVELS = 10;
const int LED_POWER[LED_LEVELS] = 
{
    MAX_DUTY_CYCLE,
    MAX_DUTY_CYCLE -  7,
    MAX_DUTY_CYCLE -  13,
    MAX_DUTY_CYCLE -  19,
    MAX_DUTY_CYCLE -  25,
    MAX_DUTY_CYCLE -  37,
    MAX_DUTY_CYCLE -  50,
    MAX_DUTY_CYCLE -  75,
    MAX_DUTY_CYCLE -  100,
    MAX_DUTY_CYCLE -  150,
    MAX_DUTY_CYCLE -  230,
    0,
};


//WIFI
const char* WIFI_SSID     = "meg-home";
const char* WIFI_PASSWORD = "MateuszeK2003";

#endif 