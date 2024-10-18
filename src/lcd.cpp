#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "lcd.h"
#include "constans.h"

LiquidCrystal_I2C i2c(0x27, 20, 4); 

Lcd::Lcd()
{}

void Lcd::init()
{
    Wire.begin();
    i2c.init();
    i2c.noBacklight();
    i2c.noDisplay();
}

void Lcd::turOn()
{
    i2c.backlight();
    i2c.display();
}

void Lcd::turOff()
{
    i2c.noBacklight();
    i2c.noDisplay();
}

void Lcd::display(Time t, short w1, short w2, short f, bool co)
{
    char line1[21];
    char line2[21];
    char line3[21];
    char line4[21];

    char wh1[4];
    char wh2[4];
    char fs[4];
    char co2[4];

    w1 == MAX_DUTY_CYCLE ? sprintf(wh1, "OFF") : sprintf(wh1, "%3d%", getPrc(w1));
    w2 == MAX_DUTY_CYCLE ? sprintf(wh2, "OFF") : sprintf(wh2, "%3d%", getPrc(w2));
    f == MAX_DUTY_CYCLE ? sprintf(fs, "OFF") : sprintf(fs, "%3d%", getPrc(f));
    co == false ? sprintf(co2, "OFF") : sprintf(co2, "ON ");

    sprintf(line1, "               %02d:%02d", t.H, t.M);
    sprintf(line2, "                    ");
    sprintf(line3, "Wh 1 Wh 2  FullS Co2");
    sprintf(line4, " %s %s  %s   %s", wh1, wh2, fs, co2);

    i2c.setCursor(0, 0);
    i2c.print(line1);

    i2c.setCursor(0, 1);
    i2c.print(line2);

    i2c.setCursor(0, 2);
    i2c.print(line3);

    i2c.setCursor(0, 3);
    i2c.print(line4);
}

void Lcd::displayMsg(const char* msg)
{
    i2c.clear(); 
    i2c.setCursor(0, 1);
    i2c.print(msg);
}

int Lcd::getPrc(int x)
{
  return 100 - (int)(x * 100 / MAX_DUTY_CYCLE);
}