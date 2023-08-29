#define LEAP_YEAR(Y)     ( (Y>0) && !(Y%4) && ( (Y%100) || !(Y%400) ) )

const int PWM_FREQ = 500;
const int PWM_RESOLUTION = 8;

const int PWM_BLUE_CHANNEL = 0;
const int PWM_RED_CHANNEL  = 1;
const int PWM_EXTRA_CHANNEL = 2;

const int PIN_LED_BLUE = 32;
const int PIN_LED_RED  = 33;
const int PIN_LED_EXTRA = 32;

const int PIN_R_BLUE = 19;
const int PIN_R_RED  = 18;
const int PIN_R_EXTRA = 5;
const int PIN_R_CO2 = 17;

const int MAX_DUTY_CYCLE = 255;
const int LED_LEVELS = 15;
const int MAX_LED_LEVELS = 14;

const int LED_POWER[LED_LEVELS] = 
{
    MAX_DUTY_CYCLE,
    MAX_DUTY_CYCLE -  5,
    MAX_DUTY_CYCLE -  10,
    MAX_DUTY_CYCLE -  15,
    MAX_DUTY_CYCLE -  20,
    MAX_DUTY_CYCLE -  30,
    MAX_DUTY_CYCLE -  50,
    MAX_DUTY_CYCLE -  75,
    MAX_DUTY_CYCLE -  100,
    MAX_DUTY_CYCLE -  125,
    MAX_DUTY_CYCLE -  150,
    MAX_DUTY_CYCLE -  175,
    MAX_DUTY_CYCLE -  200,
    MAX_DUTY_CYCLE -  225,
    0,
};

//WIFI
const char* WIFI_SSID     = "meg-home";
const char* WIFI_PASSWORD = "MateuszeK2003";
