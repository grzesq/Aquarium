#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "structs.h"
#include "constans.h"

LiquidCrystal_I2C lcd(0x27, 20, 4); 

void inidLcd();
void display();
void displayMsg(const char* msg);
int getPrc(int x);
void turOnLcd();
void turOffLcd();

void inidLcd()
{
    Wire.begin();
    lcd.init();
    lcd.noBacklight();
    lcd.noDisplay();
}

void turOnLcd()
{
    lcd.backlight();
    lcd.display();
}

void turOffLcd()
{
    lcd.noBacklight();
    lcd.noDisplay();
}

void display()
{
    char line1[21];
    char line2[21];
    char line3[21];
    char line4[21];

    char blue[4];
    char red[4];
    char extra[4];
    char co2[4];

    conf.BluePower == MAX_DUTY_CYCLE ? sprintf(blue, "OFF") : sprintf(blue, "%3d%", getPrc(conf.BluePower));
    conf.RedPower == MAX_DUTY_CYCLE ? sprintf(red, "OFF") : sprintf(red, "%3d%", getPrc(conf.RedPower));
    conf.ExtraPower == MAX_DUTY_CYCLE ? sprintf(extra, "OFF") : sprintf(extra, "ON ");
    conf.Co2Satus == 0 ? sprintf(co2, "OFF") : sprintf(co2, "ON ");

    sprintf(line1, "               %02d:%02d", currTime.H, currTime.M);
    sprintf(line2, "                    ");
    sprintf(line3, "Blue Red  Extra Co2");
    sprintf(line4, " %s %s  %s   %s", blue, red, extra, co2);

    lcd.setCursor(0, 0);
    lcd.print(line1);

    lcd.setCursor(0, 1);
    lcd.print(line2);

    lcd.setCursor(0, 2);
    lcd.print(line3);

    lcd.setCursor(0, 3);
    lcd.print(line4);
}

void displayMsg(const char* msg)
{
    lcd.clear(); 
    lcd.setCursor(0, 1);
    lcd.print(msg);
}

int getPrc(int x)
{
  return 100 - (int)(x * 100 / MAX_DUTY_CYCLE);
}