//clock.cpp
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <Keypad.h>
#include "Arduino.h"

#include "clock.h"

//constructor
Clock::Clock()
{
    // time data
  HH = 0;
  MM = 0;
  SS = 0;
  AMPM = 0;
    // alarm data
  HHa = 0; //alarm hour
  MMa = 0; //alarm minute
  AMPMa = 0; //not set=0 AM=1 PM=2
    // pill alarm data
  HHp = 0; //pill alarm hour
  MMp = 0; //pill alarm minute
  AMPMp = 0; //not set=0 AM=1 PM=2
}

//constructor 3 inputs
Clock::Clock(uint16_t HH_in, uint16_t MM_in, uint16_t AMPM_in)
{
    // time data
  HH = HH_in;
  MM = MM_in;
  SS = 0;
  AMPM = AMPM_in;
    // alarm data
  HHa = 0; //alarm hour
  MMa = 0; //alarm minute
  AMPMa = 0; //not set=0 AM=1 PM=2
    // pill alarm data
  HHp = 0; //pill alarm hour
  MMp = 0; //pill alarm minute
  AMPMp = 0; //not set=0 AM=1 PM=2
}

//constructor 4 inputs
Clock::Clock(uint16_t HH_in, uint16_t MM_in, uint16_t SS_in, uint16_t AMPM_in)
{
    // time data
  HH = HH_in;
  MM = MM_in;
  SS = SS_in;
  AMPM = AMPM_in;
    // alarm data
  HHa = 0; //alarm hour
  MMa = 0; //alarm minute
  AMPMa = 0; //not set=0 AM=1 PM=2
    // pill alarm data
  HHp = 0; //pill alarm hour
  MMp = 0; //pill alarm minute
  AMPMp = 0; //not set=0 AM=1 PM=2
}

// functions
  //returns the value
  uint16_t Clock::getHH(){return HH;}
  uint16_t Clock::getMM(){return MM;}
  uint16_t Clock::getSS(){return SS;}
  uint16_t Clock::getAMPM(){return AMPM;}//not set=0 AM=1 PM=2

  //pull the values from the internet and updates the values
  void Clock::pullHH()
  {
    //pull from web

    //set value pulled
    ;
  }
  void Clock::pullMM()
  {
    //pull from web

    //set value pulled
    ;
  }
  void Clock::pullSS()
  {
    //pull from web

    //set value pulled
    ;
  }
  void Clock::pullAMPM() //not set=0 AM=1 PM=2
  {
    //pull from web

    //set value pulled
    ;
  }

  //updates the values from input
  void Clock::setHH(uint16_t hour_in){HH = hour_in;}
  void Clock::setMM(uint16_t min_in){MM = min_in;}
  void Clock::setSS(uint16_t sec_in){SS = sec_in;}
  void Clock::setAMPM(uint16_t AMPM_in){AMPM = AMPM_in;}//not set=0 AM=1 PM=2

  void Clock::setAlarm(uint16_t HH_in, uint16_t MM_in, uint16_t AMPM_in, uint16_t alarmType_in)
  {
    if(alarmType = 0)
    {
      HHa = HH_in;
      MMa = MM_in;
      AMPMa = AMPM_in;
    }
    else
    {
      HHp = HH_in;
      MMp = MM_in;
      AMPMp = AMPM_in;
    }
  }
