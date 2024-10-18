#pragma once
#ifndef config_h
#define config_h

#include "structs.h"

class Config
{
    public:
        Config();
        void init();

        WorkTime getWhite1() { return white1; }
        WorkTime getWhite2() { return white2; }
        WorkTime getFull() { return full; }
        WorkTime getCo2() { return co2; }

        void setWhite1(WorkTime& t);
        void setWhite2(WorkTime& t);
        void setFull(WorkTime& t);
        void setCo2(WorkTime& t);

        const short StartH = 8;
        const short EndH = 23  ; 

    private:
        const short WH1_B_H = 0;
        const short WH1_B_M = 1;
        const short WH1_E_H = 3;
        const short WH1_E_M = 4;
        const short WH1_P   = 5;

        const short WH2_B_H = 6;
        const short WH2_B_M = 7;
        const short WH2_E_H = 8;
        const short WH2_E_M = 9;
        const short WH2_P = 10;

        const short FS_B_H = 11;
        const short FS_B_M = 12;
        const short FS_E_H = 13;
        const short FS_E_M = 14;
        const short FS_P = 15;

        const short CO2_B_H = 16;
        const short CO2_B_M = 17;
        const short CO2_E_H = 18;
        const short CO2_E_M = 19;
        const short CO2_P = 20;

        const short EEPROM_SIZE = 64;

    private:
       WorkTime white1;
       WorkTime white2;
       WorkTime full;
       WorkTime co2;

    private:
        void getWorkTime(WorkTime& t, short i);
        void setWorkTime(WorkTime& t, WorkTime& tc, short i);

};

#endif
