#include "RTClib.h" 

#include <Wire.h> 

#include "ds3231.h" 

#include <Arduino.h> 

#include <Adafruit_GFX.h> 

#include <Adafruit_SSD1331.h> 

#include <SPI.h> 

  

  

// The SSD1331 is connected like this (plus VCC plus GND) 

const uint8_t   OLED_pin_scl_sck        = 12; 

const uint8_t   OLED_pin_sda_mosi       = 11; 

const uint8_t   OLED_pin_cs_ss          = 10; 

const uint8_t   OLED_pin_res_rst        = 9; 

const uint8_t   OLED_pin_dc_rs          = 8; 

  

// connect a push button to ... 

const uint8_t   Button_pin              = 2; 

  

// SSD1331 color definitions 

const uint16_t  OLED_Color_Black        = 0x0000; 

const uint16_t  OLED_Color_Blue         = 0x001F; 

const uint16_t  OLED_Color_Red          = 0xF800; 

const uint16_t  OLED_Color_Green        = 0x07E0; 

const uint16_t  OLED_Color_Cyan         = 0x07FF; 

const uint16_t  OLED_Color_Magenta      = 0xF81F; 

const uint16_t  OLED_Color_Yellow       = 0xFFE0; 

const uint16_t  OLED_Color_White        = 0xFFFF; 

  

// The colors we actually want to use 

uint16_t        OLED_Text_Color         = OLED_Color_Black; 

uint16_t        OLED_Backround_Color    = OLED_Color_Blue; 


//location of HH:MM
const uint16_t hour1X = 0;  //menu clock input
const uint16_t hour1Y = 18; //menu clock input
const uint16_t hour2X = 12;  //menu clock input
const uint16_t hour2Y = 18; //menu clock input
const uint16_t min1X = 36;  //menu clock input
const uint16_t min1Y = 18;  //menu clock input
const uint16_t min2X = 48;  //menu clock input
const uint16_t min2Y = 18;  //menu clock input 
const uint16_t sec1X = 72;
const uint16_t sec1Y = 18;
const uint16_t sec2X = 84;
const uint16_t sec2Y = 18;


// declare the display 

Adafruit_SSD1331 oled = 

    Adafruit_SSD1331( 

        OLED_pin_cs_ss, 

        OLED_pin_dc_rs, 

        OLED_pin_sda_mosi, 

        OLED_pin_scl_sck, 

        OLED_pin_res_rst 

     ); 

  

RTC_DS3231 rtc; 

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}; 
uint8_t hourOld = 0;
uint8_t minOld = 0;
uint8_t secOld = 0;

  

void setup () { 

#ifndef ESP8266 

  while (!Serial); // for Leonardo/Micro/Zero 

#endif 

Serial.begin(9600); 

delay(3000); // wait for console opening 
     oled.begin(); 

    oled.setFont(); 

    oled.fillScreen(OLED_Backround_Color); 

    oled.setTextColor(OLED_Text_Color); 

    oled.setTextSize(2); 
  

  if (! rtc.begin()) { 

    Serial.println("Couldn't find RTC"); 

    while (1); 

  } 

  

  if (rtc.lostPower()) { 

    Serial.println("RTC lost power, lets set the time!"); 

    // following line sets the RTC to the date & time this sketch was compiled 

    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 

    // This line sets the RTC with an explicit date & time, for example to set 

    // January 21, 2014 at 3am you would call: 

    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0)); 

  } 

} 

  

void loop () { 

    DateTime now = rtc.now(); 
    oled.fillScreen(OLED_Backround_Color);
    oled.setCursor(24,18);

    
      if(hourOld != now.hour())
      {
      if(now.hour() < 9) {oled.setCursor(hour2X,hour2Y);} 
      else {oled.setCursor(hour1X, hour1Y);}
      
      oled.print(now.hour(), DEC);
      oled.print(':');
      Serial.print(now.hour(), DEC);
      Serial.print(':');
      
      
      }
      if(minOld != now.minute()) 
      {
        if(now.minute() < 9){oled.setCursor(min2X, min2Y);} 
        else {oled.setCursor(min1X, min1Y);}
        
        oled.print(now.minute(), DEC);
        oled.print(':');
        Serial.print(now.minute(), DEC);
        Serial.print(':');
        
      
      }
      if(secOld != now.second()) 
      {
        if(now.second() < 9) {oled.setCursor(sec2X, sec2Y);} 
        else {oled.setCursor(sec1X, sec1Y);}
        
        oled.print(now.second(), DEC);
        Serial.print(now.second(), DEC); 
      }
  

    Serial.println(); 
    oled.println();

    delay(1000); 

}    
