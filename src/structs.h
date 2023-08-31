#ifndef Structs_h
#define Structs_h

struct Config
{
    short BlueStartH = 12;
    short BlueStartM = 12;
    short BlueStopH = 12;
    short BlueStopM = 12;

    short RedStartH = 12;
    short RedStartM = 12;
    short RedStopH = 12;
    short RedStopM = 12;

    short ExtraStartH = 12;
    short ExtraStartM = 12;
    short ExtraStopH = 12;
    short ExtraStopM = 12;

    short Co2Start = 12;
    short Co2Stop = 12;
} conf;

struct CurrTime
{
    short H = 0;
    short M = 0;
} currTime;


#endif