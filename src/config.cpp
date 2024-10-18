#include <EEPROM.h>
#include "config.h"

Config::Config()
{
    init();
}

void Config::init()
{
    Serial.println("INIT CONFIG");
    // initialize EEPROM with predefined size
    if (!EEPROM.begin(EEPROM_SIZE))
    {
        Serial.println("failed to initialize EEPROM");
    }
    else
    {
        Serial.println("EEPROM OK");
    }

    getWorkTime(white1, WH1_B_H);
    getWorkTime(white2, WH2_B_H);
    getWorkTime(full, FS_B_H);
    getWorkTime(co2, CO2_B_H);
}

void Config::getWorkTime(WorkTime& t, short i)
{
    Serial.print("Read EEPROM");
    t.BH = EEPROM.read(i++);
    t.BM = EEPROM.read(i++);
    t.EH = EEPROM.read(i++);
    t.EM = EEPROM.read(i++);
     t.P = EEPROM.read(i);

    if (t.BH > 23) t.BH = 12;
    if (t.EH > 23) t.EH = 18;
    if (t.BM > 59) t.BH = 00;
    if (t.EM > 23) t.EH = 00;
    if (t.P > 100) t.EH = 75;
}

void Config::setWhite1(WorkTime& t)
{
    setWorkTime(t, white1, WH1_B_H);
}

void Config::setWhite2(WorkTime& t)
{
    setWorkTime(t, white2, WH2_B_H);
}

void Config::setFull(WorkTime& t)
{
    setWorkTime(t, full, FS_B_H);
}

void Config::setCo2(WorkTime& t)
{
    setWorkTime(t, co2, CO2_B_H);
}

void Config::setWorkTime(WorkTime& t, WorkTime& tc, short i)
{
    tc.BH = t.BH;
    tc.BM = t.BM;
    tc.EH = t.EH;
    tc.EM = t.EM;
    tc.P = t.P;

    EEPROM.write(i++, tc.BH);
    EEPROM.write(i++, tc.BM);
    EEPROM.write(i++, tc.EH);
    EEPROM.write(i++, tc.EM);
    EEPROM.write(i++, tc.P); 

    EEPROM.commit();
    Serial.println("Save EEPROM");
}