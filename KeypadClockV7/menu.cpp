//menu.cpp

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <Keypad.h>
#include "Arduino.h"
#include <EEPROM.h> // This will allow saving valies for loss of power

#include "menu.h"

#define EEADDR 166 // Start location to write EEPROM data.

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
  timeFormat = 24;

  isDisplayVisible = false;
}
void Menu::load()
{
  //Read EEPROM
  int EEAddr = EEADDR;
  EEPROM.get(EEAddr, menuColor); EEAddr += sizeof(menuColor);       //EEAddr = 166
  EEPROM.get(EEAddr, timeFormat); EEAddr += sizeof(timeFormat);     //EEAddr = 168
  EEPROM.get(EEAddr, childSafety); EEAddr += sizeof(childSafety);   //EEAddr = 169
  EEPROM.get(EEAddr, alarmHH); EEAddr += sizeof(alarmHH);           //EEAddr = 170
  EEPROM.get(EEAddr, alarmMM); EEAddr += sizeof(alarmMM);           //EEAddr = 171
  EEPROM.get(EEAddr, pillHH); EEAddr += sizeof(pillHH);             //EEAddr = 172
  EEPROM.get(EEAddr, pillMM); EEAddr += sizeof(pillMM);             //EEAddr = 173
  EEPROM.get(EEAddr, pillCounter); EEAddr += sizeof(pillCounter);   //EEAddr = 174
  EEPROM.get(EEAddr, PIN); EEAddr += sizeof(PIN);                   //EEAddr = 175 // max size is 20, larger than needed to be safe.
  EEPROM.get(EEAddr, wifiSSID); EEAddr += sizeof(wifiSSID);         //EEAddr = 195 
  EEPROM.get(EEAddr, wifiPASS); EEAddr += sizeof(wifiPASS);         //EEAddr = 195  + sizeof(wifiSSID)

  snoozeAlarmHH = alarmHH;
  snoozeAlarmMM = alarmMM; 
  menuLevel = 0;
  count = 0;
  clkON = true;
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
void Menu::setPIN(String newPIN){PIN = newPIN; EEPROM.update(175, newPIN.c_str());}
String Menu::getPIN(){return PIN;}

// COLOR
void Menu::setColor(uint16_t newColor){menuColor = newColor; EEPROM.update(166, newColor);}
uint16_t Menu::getColor(){return menuColor;}

//SSID and PASS
void Menu::setWiFi(String SSIDin, String WIFIin){wifiSSID = SSIDin; wifiPASS = WIFIin; EEPROM.update(195, wifiSSID.c_str());EEPROM.update( (195+sizeof(wifiSSID)), wifiPASS.c_str());}
String Menu::getSSID(){return wifiSSID;}
String Menu::getPASS(){return wifiPASS;}

//Time  Format
void Menu::setTimeFormat(uint8_t newFormat){timeFormat = newFormat; EEPROM.update(168, newFormat);} //only pass 12 or 24 in
uint8_t Menu::getTimeFormat(){return timeFormat;}

//Child Safety
void Menu::setChildSafety(bool newState){childSafety = newState; EEPROM.update(169, newState);}
bool Menu::getChildSafety(){return childSafety;}

//Alarm Time
void Menu::setAlarmTime(uint8_t hour, uint8_t min){alarmHH = hour; alarmMM = min; snoozeAlarmHH = hour; snoozeAlarmMM = min; EEPROM.update(170, hour); EEPROM.update(171, min);}
uint8_t Menu::getAlarmHH(){return alarmHH;}
uint8_t Menu::getAlarmMM(){return alarmMM;}

//Pill Alarm Time
void Menu::setPillTime(uint8_t hour, uint8_t min){pillHH = hour; pillMM = min; EEPROM.update(172, hour); EEPROM.update(173, min);}
uint8_t Menu::getPillHH(){return pillHH;}
uint8_t Menu::getPillMM(){return pillMM;}

//Pill Alarm Counter
uint8_t Menu::getPillCounter(){return pillCounter;}
void Menu::incPillAlarm(){pillCounter += 1; EEPROM.update(174, pillCounter);}
void Menu::resetPillCounter(){pillCounter = 0; EEPROM.update(174, pillCounter);}
