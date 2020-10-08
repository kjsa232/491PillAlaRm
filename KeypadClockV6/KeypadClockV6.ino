#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <Keypad.h>
#include "clock.h" //contains clock::
#include "menu.h" //contains Menu::
//RTC CLOCK
#include "RTClib.h"
#include <Wire.h>
#include "ds3231.h"
//#include "constants.h"


//KEYPAD
char customKey;
const byte ROWS = 4;
const byte COLS = 3;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

// digital connection Pins to the arduino for the keypad
byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {3, 2, 1};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

#define SerialDebugging true

// The SSD1331 is connected like this (plus VCC plus GND)
const uint8_t OLED_pin_scl_sck = 12;  //12 old
const uint8_t OLED_pin_sda_mosi = 11; //11 old
const uint8_t OLED_pin_cs_ss = 10;
const uint8_t OLED_pin_res_rst = 9;
const uint8_t OLED_pin_dc_rs = 8;

// SSD1331 color definitions
const uint16_t OLED_Color_Black = 0x0000;
const uint16_t OLED_Color_Blue = 0x001F;
const uint16_t OLED_Color_Red = 0xF800;
const uint16_t OLED_Color_Green = 0x07E0;
const uint16_t OLED_Color_Cyan = 0x07FF;
const uint16_t OLED_Color_Magenta = 0xF81F;
const uint16_t OLED_Color_Yellow = 0xFFE0;
const uint16_t OLED_Color_White = 0xFFFF;

// The colors we actually want to use
// uint16_t OLED_Text_Color = OLED_Color_Magenta; //declared below under the creation of clkMenu
uint16_t OLED_Backround_Color = OLED_Color_Black;

// Menu Line positions
const uint8_t menu1X = 0;   //menu line 1
const uint8_t menu1Xtab = 4;//menu line 1 indent
const uint8_t menu1Y = 1;  //menu line 1

const uint8_t menu2X = 0;   //menu line 2
const uint8_t menu2Y = 9;  //menu line 2

const uint8_t menu4X = 0;   //menu line 4
const uint8_t menu4Y = 25;  //menu line 4

const uint8_t menu3Y = 17;  //menu line 3
const uint8_t menu5Y = 33;  //menu line 5
const uint8_t menu6Y = 41;  //menu line 6
const uint8_t menu7Y = 49;  //menu line 7
const uint8_t menu8Y = 57;  //menu line 8

//location of HH:MM for time Menus
const uint8_t hour1X = 0;  //menu clock input
const uint8_t hour1Y = 17; //menu clock input
const uint8_t hour2X = 6;  //menu clock input
const uint8_t hour2Y = 17; //menu clock input
const uint8_t min1X = 18;  //menu clock input
const uint8_t min1Y = 17;  //menu clock input
const uint8_t min2X = 24;  //menu clock input
const uint8_t min2Y = 17;  //menu clock input

//rtc clock times
uint8_t hourOld = 0;
uint8_t minOld = 0;
uint8_t secOld = 0;

// rtc clock location
const uint8_t RTChour1X = 4;  //menu clock input
const uint8_t RTChour1Y = 12; //menu clock input
const uint8_t RTChour2X = 22;  //menu clock input
const uint8_t RTChour2Y = 12; //menu clock input
const uint8_t RTCmin1X = 58;  //menu clock input
const uint8_t RTCmin1Y = 12;  //menu clock input
const uint8_t RTCmin2X = 76;  //menu clock input
const uint8_t RTCmin2Y = 12;  //menu clock input

String inputString1 = ""; //temp storage
String inputString2 =""; //temp storage
uint16_t abLine = 0;
char alphabet[] = {'a','b','c' ,'d','e','f' ,'g','h','i',
                   'j','k','l' ,'m','n','o' ,'p','q','r',
                   's','t','u' ,'v','w','x' ,'y','z',' ',
                   'A','B','C' ,'D','E','F' ,'G','H','I',
                   'J','K','L' ,'M','N','N' ,'O','P','Q',
                   'R','S','T' ,'U','V','W' ,'X','Y','Z',
                   '0','1','2' ,'3','4','5' ,'6','7','8',
                   '9','!','@' ,'#','$','%' ,'^','&','*',
                   '(',')','-' ,'_','=','+' ,',','?','.',
                   '<','>','\'','"','\\','/','|',':',';',
                   '"','[',']' ,'{','}' ,'`','~',' ',' ',};

// declare the display
Adafruit_SSD1331 oled = Adafruit_SSD1331(OLED_pin_cs_ss,OLED_pin_dc_rs,OLED_pin_sda_mosi,OLED_pin_scl_sck,OLED_pin_res_rst);
//declare the menu
Menu clkMenu;
//declare the clock
RTC_DS3231 rtc;
DateTime now;

uint16_t OLED_Text_Color = clkMenu.getColor();

// assume the display is off until configured in setup()
bool isDisplayVisible = false;
// declare size of working string buffers. Basic strlen("d hh:mm:ss") = 10
const size_t MaxString = 16;
// the string being displayed on the SSD1331 (initially empty)
char oldTimeString[MaxString] = { 0 };
// the interrupt service routine affects this
volatile bool isButtonPressed = false;

String PINin = "";
volatile uint16_t hourIn = 0;
volatile uint16_t minIn = 0;
volatile uint16_t ampmIn = 0; //0:not set 1:AM 2:PM
//volatile uint16_t clkMenu.setColor(OLED_Color_Green);

// interrupt service routine
void senseButtonPressed() {
    if (!isButtonPressed) {isButtonPressed = true;}
}





void rtcTime(uint8_t in)
{
   oled.setTextSize(3);
   oled.setTextColor(clkMenu.getColor());
   now = rtc.now();
   if(in == 1)
   {
    oled.setCursor(RTChour1X,RTChour1Y);
    if(now.hour() < 10){oled.print('0');}
    oled.print(now.hour());
    oled.setCursor(40,12); 
    oled.print(':');
    oled.setCursor(RTCmin1X,RTCmin1Y);
    if(now.minute() < 10){oled.print('0');}
    oled.print(now.minute());
   }
   else //in != 1
   {
   if(clkMenu.getClkON()) // This will skip this code when in a menu
   {
    //oled.setCursor(40,12); oled.print(':'); // This is the :, HH:MM, it doesn't need to be printed elsewhere     

// CHECK AND UPDATE THE HOUR  
     if(hourOld != now.hour())
     {
       oled.setTextColor(OLED_Backround_Color); //Set Clear hourOld
       if(clkMenu.getTimeFormat() == 24)
       {
        //CLEAR hourOld 24
        if(hourOld < 9)         {oled.setCursor(RTChour2X,RTChour2Y);oled.print(hourOld);}
        else if(hourOld == 10)  {oled.setCursor(RTChour1X,RTChour1Y);oled.print(hourOld);}
        else if(hourOld < 19)   {oled.setCursor(RTChour2X,RTChour2Y);oled.print((hourOld - 10));}
        else if(hourOld == 19)  {oled.setCursor(RTChour1X,RTChour1Y);oled.print(hourOld);}
        else if (hourOld < 22)  {oled.setCursor(RTChour2X,RTChour2Y);oled.print((hourOld - 20));}
        else /* hourOld == 23*/ {oled.setCursor(RTChour1X,RTChour1Y);oled.print(hourOld);}

        oled.setTextColor(clkMenu.getColor());
        //PRINT now.hour(), DEC 24
        if(hourOld < 9)         {oled.setCursor(RTChour2X,RTChour2Y);oled.print(now.hour());}
        else if(hourOld == 10)  {oled.setCursor(RTChour1X,RTChour1Y);oled.print(now.hour());}
        else if(hourOld < 19)   {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 10));}
        else if(hourOld == 19)  {oled.setCursor(RTChour1X,RTChour1Y);oled.print(now.hour());}
        else if (hourOld < 22)  {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 20));}
        else /* hourOld == 23*/ {oled.setCursor(RTChour1X,RTChour1Y);oled.print('0');oled.print(now.hour());}
        
       }//end 24 hour
       
       else //12 hour format
       {
        //CLEAR hourOld 12
        //1-8 am and pm
        if((hourOld > 0) && (hourOld < 9))        {oled.setCursor(RTChour2X,RTChour2Y);oled.print(hourOld);}
        else if((hourOld > 12) && (hourOld < 21)) {oled.setCursor(RTChour2X,RTChour2Y);oled.print(hourOld - 22);}
        //midnight and noon
        else if((hourOld == 0)||(hourOld == 12) ) {oled.setCursor(RTChour1X,RTChour1Y);oled.print("12");}
        //10 and 11 am and pm
        else if((hourOld >= 9)&&(hourOld <= 11))  {oled.setCursor(RTChour2X,RTChour2Y);oled.print((hourOld - 10));}
        else /* hourOld == 21 or 22 or 23 */      {oled.setCursor(RTChour2X,RTChour2Y);oled.print((hourOld - 22));}

        //Remove the AM/PM indicator
        //remove AM if hourOld == 11

        //remove PM if hourOld == 23

        oled.setTextColor(clkMenu.getColor());
        //PRINT now.hour(), DEC 12
        //1-8 am and pm OLD
        if((hourOld > 0) && (hourOld < 9)) {oled.setCursor(RTChour2X,RTChour2Y); oled.print(now.hour());}
        else if((hourOld > 12) && (hourOld < 21)) {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 22));}
        //midnight and noon OLD
        else if((hourOld == 0)||(hourOld == 12))  {oled.setCursor(RTChour1X,RTChour1Y);oled.print("01");}
        //9,10,11 am and pm OLD
        else if((hourOld >= 9)&&(hourOld <= 11))  {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 10));}
        else /* hourOld == 21 or 22 or 23 */      {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 22));}
        
       }//end 12 hour
       
       //update hourOld
       if(hourOld < 23){hourOld += 1;} else{hourOld -= 23;}
     }//END UPDATE HOUR
   
   
      
// CHECK AND UPDATE MINUTES
       oled.setCursor(RTCmin1X,RTCmin1Y);
       if(minOld != now.minute())
       {
        //CLEAR minOld
        oled.setTextColor(OLED_Backround_Color);

        if(minOld < 9)         {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print(minOld);}
        else if(minOld == 9)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print('0');oled.print(minOld);}
        else if(minOld < 19)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((minOld - 10));}
        else if(minOld == 19)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(minOld);}
        else if(minOld < 29)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((minOld - 20));}
        else if(minOld == 29)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(minOld);}
        else if(minOld < 39)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((minOld - 30));}
        else if(minOld == 39)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(minOld);}
        else if(minOld < 49)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((minOld - 40));}
        else if(minOld == 49)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(minOld);}
        else if(minOld < 59)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((minOld - 50));}
        else/* minOld == 59 */ {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(minOld);}

        //print (now.minute(), DEC);
        oled.setTextColor(clkMenu.getColor());
        
        if(minOld < 9)         {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print(now.minute());}
        else if(minOld == 9)   {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute());}
        else if(minOld < 19)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 10));}
        else if(minOld == 19)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute());}
        else if(minOld < 29)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 20));}
        else if(minOld == 29)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute());}
        else if(minOld < 39)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 30));}
        else if(minOld == 39)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute());}
        else if(minOld < 49)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 40));}
        else if(minOld == 49)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute());}
        else if(minOld < 59)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 50));}
        else/* minOld == 59 */ {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute());}

         //update minOld
         if(minOld < 59){minOld += 1;} else{minOld -= 59;}
       }//END UPDATE MIN
   }//END Checks if Display Clock is ON
}// END in != 1
}//RTC TIME


void setup()
{
//rtcTime
rtc.begin();
rtc.adjust(DateTime(__DATE__, __TIME__));
delay(750);
oled.fillScreen(OLED_Backround_Color);

// ignore any power-on-reboot garbage
isButtonPressed = false;

// initialise the SSD1331
oled.begin();
oled.setFont();
oled.fillScreen(OLED_Backround_Color);
oled.setTextColor(clkMenu.getColor());
oled.setTextSize(3);

// the display is now on
isDisplayVisible = true;
}

void loop()
{
//RTC CLOCK TIME

rtcTime(0);


//CALL THE PILL ALARM FUNCTION
//  if(Pill_Alarm_Trigger_Time || pillAlarmTripped == 1){pillAlarmTripped = pillAlarm(); }

//call the alarm function here
//  if(Alarm_Trigger_Time || alarmTripped == 1 || Snooze_Alarm_Trigger_Time){alarmTripped = alarm(); }

// no need to be in too much of a hurry, shorten if too much latency
//delay(100);
}
