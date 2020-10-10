//menu.cpp
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <Keypad.h>
#include "Arduino.h"

#include "menu.h"

//constructor
Menu::Menu()
{
  menuLevel = 0;
  count = 0;
  clkON = true;
  menuColor = 0x07E0; //green
  wifiSSID = "";
  wifiPASS = "";
  PIN = "147";
  timeFormat = 12;

  isDisplayVisible = false;
}

// LEVEL
void Menu::setLevel(uint8_t newLevel)
{
  menuLevel = newLevel;
  count = 0;
  //if(newLevel == 0){clkON = true;}
}
uint8_t Menu::getLevel(){return menuLevel;}

// COUNT
void Menu::setCount(uint8_t newCount){count = newCount;}
uint8_t Menu::getCount(){return count;}
void Menu::incCount(){count++;}

// CLK ON
bool Menu::getClkON(){return clkON;}
void Menu::setClkON(bool state){clkON = state;}

void Menu::setVisability(bool state){isDisplayVisible = state;}

// PIN
void Menu::setPIN(String newPIN){PIN = newPIN;}
String Menu::getPIN(){return PIN;}

// COLOR
void Menu::setColor(uint16_t newColor){menuColor = newColor;}
uint16_t Menu::getColor(){return menuColor;}

//SSID and PASS
void Menu::setSSID(String input){wifiSSID = input;}
String Menu::getSSID(){return wifiSSID;}
void Menu::setPASS(String input){wifiPASS = input;}
String Menu::getPASS(){return wifiPASS;}

//Time  Format
void Menu::setTimeFormat(uint8_t newFormat){timeFormat = newFormat;} //only pass 12 or 24 in
uint8_t Menu::getTimeFormat(){return timeFormat;}

//Child Safety
void Menu::setChildSafety(bool newState){childSafety = newState;}
bool Menu::getChildSafety(){return childSafety;}

//Alarm Time
void Menu::setAlarmTime(uint8_t hour, uint8_t min){alarmHH = hour; alarmMM = min;}
uint8_t Menu::getAlarmHH(){return alarmHH;}
uint8_t Menu::getAlarmMM(){return alarmMM;}

//Pill Alarm Time
void Menu::setPillTime(uint8_t hour, uint8_t min){pillHH = hour; pillMM = min;}
uint8_t Menu::getPillHH(){return pillHH;}
uint8_t Menu::getPillMM(){return pillMM;}
