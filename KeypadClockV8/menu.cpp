//menu.cpp

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <Keypad.h>
#include "Arduino.h"
#include <EEPROM.h> // This will allow saving valies for loss of power

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
  timeFormat = 24;

  isDisplayVisible = false;
}

//PRIVATE, HELPER FUNCTIONS
//eeprom update and read String are based heavily on code found here: https://circuits4you.com/2018/10/16/arduino-reading-and-writing-string-to-eeprom/
//originaly update was just write, but changed due to limited number of writes to EEPROM.
void Menu::eepromUpdateString(uint8_t address, String DATA)
{
  uint8_t sizeDATA = DATA.length();
  char currChar;
  for(uint8_t i = 0; i < sizeDATA; i++)
    {
    currChar = EEPROM.read(address + 1);
    if(currChar != DATA[i]){EEPROM.write(address + i, DATA[i]);}
    }
  EEPROM.write(address + sizeDATA, '\0');   //Add termination null character for String  
}
String Menu::eepromReadString(uint8_t address)
{ 
  uint8_t i;
  uint8_t len = 0;
  char data[80]; //Max 80 Bytes
  char currChar = EEPROM.read(address);
  while(currChar != '\0' && len < 80)   //Read until null character or max length
    {    
    currChar = EEPROM.read(address + len);
    data[len] = currChar;
    len++;
    }
  data[len] = '\0';
  return String(data);
  
}

//FUNCTIONS
void Menu::load()
{
  //Read EEPROM
  
  EEPROM.get(0, menuColor);                  //EEAddr = 0
  EEPROM.get(2, timeFormat);                 //EEAddr = 2
  EEPROM.get(3, childSafety);                //EEAddr = 3
  EEPROM.get(4, alarmHH);                    //EEAddr = 4
  EEPROM.get(5, alarmMM);                    //EEAddr = 5
  EEPROM.get(6, pillHH);                     //EEAddr = 6
  EEPROM.get(7, pillMM);                     //EEAddr = 7
  EEPROM.get(8, pillCounter);                //EEAddr = 8
  PIN = eepromReadString(9);
  wifiSSID = eepromReadString(29);
  wifiPASS = eepromReadString(29+sizeof(wifiPASS));
  
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
void Menu::setPIN(String newPIN)
{
  PIN = newPIN; 
  //EEPROM.update(9, newPIN.c_str());
  eepromUpdateString(9, PIN);
}
String Menu::getPIN(){return PIN;}

// COLOR
void Menu::setColor(uint16_t newColor){menuColor = newColor; EEPROM.put(0, newColor);}
uint16_t Menu::getColor(){return menuColor;}

//SSID and PASS
void Menu::setWiFi(String SSIDin, String WIFIin)
{wifiSSID = SSIDin; wifiPASS = WIFIin; 
//EEPROM.update(29, wifiSSID.c_str());EEPROM.update( (29+sizeof(wifiSSID)), wifiPASS.c_str());
eepromUpdateString(29, wifiSSID); eepromUpdateString((29+sizeof(wifiSSID)), wifiPASS);
}
String Menu::getSSID(){return wifiSSID;}
String Menu::getPASS(){return wifiPASS;}

//Time  Format
void Menu::setTimeFormat(uint8_t newFormat){timeFormat = newFormat; EEPROM.update(2, newFormat);} //only pass 12 or 24 in
uint8_t Menu::getTimeFormat(){return timeFormat;}

//Child Safety
void Menu::setChildSafety(bool newState){childSafety = newState; EEPROM.update(3, newState);}
bool Menu::getChildSafety(){return childSafety;}

//Alarm Time
void Menu::setAlarmTime(uint8_t hour, uint8_t min){alarmHH = hour; alarmMM = min; snoozeAlarmHH = hour; snoozeAlarmMM = min; EEPROM.update(4, hour); EEPROM.update(5, min);}
uint8_t Menu::getAlarmHH(){return alarmHH;}
uint8_t Menu::getAlarmMM(){return alarmMM;}

//Pill Alarm Time
void Menu::setPillTime(uint8_t hour, uint8_t min){pillHH = hour; pillMM = min; EEPROM.update(6, hour); EEPROM.update(7, min);}
uint8_t Menu::getPillHH(){return pillHH;}
uint8_t Menu::getPillMM(){return pillMM;}

//Pill Alarm Counter
uint8_t Menu::getPillCounter(){return pillCounter;}
void Menu::incPillAlarm(){pillCounter += 1; EEPROM.update(8, pillCounter);}
void Menu::resetPillCounter(){pillCounter = 0; EEPROM.update(8, pillCounter);}
