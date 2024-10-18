#pragma once

#ifndef lcd_h
#define lcd_h

#include "structs.h"

class Lcd
{
    public:
        Lcd();
        void init();
        void display(Time t, short w1, short w2, short f, bool co);
        void displayMsg(const char* msg);
        void turOn();
        void turOff();

    private:        
        int getPrc(int x);
};

#endif