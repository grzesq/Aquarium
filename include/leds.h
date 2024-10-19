#pragma one

#ifndef leds_h
#define leds_h

#include "structs.h"
#include "config.h"

class Leds
{
    public:
        Leds(Config& c);
        void init();
        void checkLedStatus(Time t);
        LightPower getPower();

    private:
        Config* conf;
        LightPower lightPower;

        void checkW1Status();
        void checkW2Status();
        void checkFsStatus();
        void setLedPower();

};

#endif