//menu.cpp
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <Keypad.h>
#include "Arduino.h"
#include "constants.h"

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
  
  hourIn = 0;
  minIn = 0;
  ampmIn = 0; //0:not set 1:AM 2:PM
  isDisplayVisible = false;
}

// LEVEL
void Menu::setLevel(uint16_t newLevel)
{
  menuLevel = newLevel;
  count = 0;
  //if(newLevel == 0){clkON = true;}
}
uint16_t Menu::getLevel(){return menuLevel;}

// COUNT
void Menu::setCount(uint16_t newCount){count = newCount;}
uint16_t Menu::getCount(){return count;}
void Menu::incCount(){count++;}

// CLK ON
bool Menu::getClkON(){return clkON;}
void Menu::setClkON(bool state){clkON = state;}

void Menu::setVisability(bool state){isDisplayVisible = state;}

// PIN
void Menu::setPIN(uint16_t newPIN){PIN = newPIN;}
uint16_t Menu::getPIN(){return PIN;}

// COLOR
void Menu::setColor(uint16_t newColor){menuColor = newColor;}
uint16_t Menu::getColor(){return menuColor;}

//SSID and PASS
void Menu::setSSID(String input){wifiSSID = input;}
String Menu::getSSID(){return wifiSSID;}
void Menu::setPASS(String input){wifiPASS = input;}
String Menu::getPASS(){return wifiPASS;}

//Time  Format
void Menu::setTimeFormat(uint16_t newFormat){timeFormat = newFormat;} //only pass 12 or 24 in
uint16_t Menu::getTimeFormat(){return timeFormat;}
