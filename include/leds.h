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
        LightPower getLedsStatus(Time& t);
        LightPower getPower();
        void powerOffAll();

    private:
        Config* conf;
        LightPower lightPower;

        void checkW1Status(Time& t);
        void checkW2Status(Time& t);
        void checkFsStatus(Time& t);
        void setLedPower();
        short setPower(Time& t, WorkTime& wt, short pow);
        int getPower(short p);
};

#endif