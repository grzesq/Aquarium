#ifndef Structs_h
#define Structs_h

struct Config
{
    short StartH = 8;
    short EndH = 23;

    short BlueStartH = 12;
    short BlueStartM = 00;
    short BlueStopH = 21;
    short BlueStopM = 00;

    short RedStartH = 12;
    short RedStartM = 15;
    short RedStopH = 20;
    short RedStopM = 45;

    short ExtraStartH = 8;
    short ExtraStartM = 0;
    short ExtraStopH = 23;
    short ExtraStopM = 00;

    short Co2Start = 11;
    short Co2Stop = 19;
    short Co2Satus = 0;

    short BluePower = LED_POWER[0];
    short RedPower = LED_POWER[0];
    short ExtraPower = LED_POWER[0];
} conf;

struct CurrTime
{
    short H = 0;
    short M = 0;
    short S = 0;
} currTime;


#endif