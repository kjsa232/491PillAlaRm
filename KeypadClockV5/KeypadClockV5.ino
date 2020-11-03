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


void keypadMenu()
{
customKey = customKeypad.getKey();
if (customKey){Serial.println(customKey);}
switch(clkMenu.getLevel())
  {
  case 0:
      if (customKey == '1'){ OLED_Text_Color = OLED_Color_White; }
      else if (customKey == '2'){ OLED_Text_Color = OLED_Color_Green; }
      else if (customKey == '3'){ OLED_Text_Color = OLED_Color_Blue; oled.fillCircle(oled.width()/2, oled.height()/2, 10, OLED_Color_Green);      }
      else if (customKey == '4')
      {
        OLED_Text_Color = OLED_Color_Cyan;
        oled.fillCircle(oled.width()/4,   // X-Axis of the center
                        oled.height()/2,  // Y-Axis of the center
                        5,                // Radius of the circle
                        OLED_Color_Cyan   // Color of the circle
                        );
      oled.drawPixel(0, 63, OLED_Color_White);
      }
      else if (customKey == '5')
      {
        // Battery Full
        //OLED_Text_Color = OLED_Color_White;
                   // X←,Y↑,↔,↨, Color
        oled.drawRect(89, 1, 7, 9, OLED_Color_White);   //Outline
        oled.drawPixel(89, 1, OLED_Color_Black);
        oled.drawPixel(95, 1, OLED_Color_Black);
                    // X←,Y↑,↔,↨, Color
         oled.fillRect(90, 2, 5, 7, OLED_Color_Green); //Green Fill
                   // X, Y, Color
         oled.drawPixel(90, 2, OLED_Color_White);  //Outline
         oled.drawPixel(94, 2, OLED_Color_White);

      }
      else if (customKey == '6')
      {
        OLED_Text_Color = OLED_Color_Red;
        oled.drawCircle(oled.width()/4,   // X-Axis of the center
                        oled.height()/2,  // Y-Axis of the center
                        5,                // Radius of the circle
                        OLED_Color_Red    // Color of the Line
                        );
      }
      else if (customKey == '*')  //Menu
      {
      clkMenu.setClkON(false);
      oled.fillScreen(OLED_Color_Black);   //SLOW

      //oled.setTextColor(OLED_Backround_Color);
      //oled.setCursor(hhX,hhY);
      //oled.print("XXXXX");
      oled.setTextColor(clkMenu.getColor());
      oled.setCursor(menu1X,menu1Y);
      oled.setTextSize(1);
      oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");
      clkMenu.setLevel(1);
   customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
      }
      else if (customKey == '#')  //Toggle Display
      {
      // yes! toggle display visibility
         isDisplayVisible = !isDisplayVisible;
      // apply
         oled.enableDisplay(isDisplayVisible);
      }
  break;// menuLevel 0
// SUB MENU LOOP ---- ↓ -------------------------
  case 1:
    oled.setTextSize(1);
  switch(customKey)
  {
   //SET TIME
   case '1':
   //clear screen text
   oled.setTextColor(OLED_Backround_Color);
   oled.setCursor(menu1X,menu1Y);
   oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");

   oled.setTextColor(clkMenu.getColor());
   oled.setCursor(menu1Xtab, menu1Y);
   oled.print("Time\nEnter the time\nXX:XX");
   clkMenu.setLevel(10);
   customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
   break; // case '1'

     //SET PILL ALARM
     case '2':
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");

     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("Pill Alarm\nEnter the time\nXX:XX");
     clkMenu.setLevel(20);
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 2
     break;//case '2'

     //SET ALARM
     case '3':
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");

     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("Alarm\nEnter the time\nXX:XX");
     clkMenu.setLevel(30);
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 3
     break; //case '3'

     //CHILD SAFETY
     case '4':
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");

     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("Child Safety\nEnter your PIN\nfollowed by *");
     PINin = "";
     clkMenu.setLevel(40);
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 4
     break; //case '4'

     //CHANGE PIN
     case '5':
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");

     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("Change PIN\nEnter your PIN\nfollowed by *");
     PINin = "";
     clkMenu.setLevel(50);
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 5
     break; //case '5'

     //WIFI
     case '6':
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");

     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("WiFi\nEnter your SSID\nfollowed by *\nSSID:\n\n Char:");
   abLine = 0;
     for(int i = 0; i < 9; i++){oled.print(alphabet[abLine * 9 + i]);}
     oled.print("\nPress:123456789\nPrev:0    Next:#");
     oled.setCursor(30, menu4Y);
     clkMenu.setLevel(60);
     inputString1 = "";
     inputString2 = "";
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 6
     break; //case '6'

     //Color Menu
     case '7':
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");

     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("Colors\nPick Font Color\n");
     oled.setTextColor(OLED_Color_Blue);
     oled.print("1:Blue\n");
     oled.setTextColor(OLED_Color_Cyan);
     oled.print("2:Cyan\n");
     oled.setTextColor(OLED_Color_Green);
     oled.print("3:Green\n");
     oled.setTextColor(OLED_Color_Yellow);
     oled.print("4:Yellow\n");
     oled.setTextColor(OLED_Color_Magenta);
     oled.print("5:Magenta\n");
     oled.setTextColor(OLED_Color_White);
     oled.print("6:White");
     oled.setTextColor(clkMenu.getColor());
     clkMenu.setLevel(70);
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
     break; //case '7'

     //Pills Replaced
     case '8':
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");

     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("Pills Replaced\nHave you reset\nyour pills?\n1:Yes\n2:No");
     clkMenu.setLevel(80);
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
     break; //case '8'

     //Return to clock
   case '#':
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");

     clkMenu.setLevel(0);
     clkMenu.setClkON(true);
     rtcTime(1);

     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
     break; //case '#'
   default:
   customKey = 'z';
   //end default
  }// switch(customKey)
    break; //menuLevel 1
// SUB MENU LOOP ---- ↑ -------------------------

// TIME/Pill Alarm/Alarm MENU LOOP  ---------- ↓ ---------------
  // uses hourIn and minIn for temp storage, volatile uint16_t count is used counter var
  case 10: case 20: case 30:
     oled.setTextSize(1);
   if(clkMenu.getCount() == 4) //ADDS THE AM PM selection
      {
      clkMenu.incCount();
      oled.setTextColor(clkMenu.getColor());
      oled.setCursor(menu4X, menu4Y);
      oled.print("1:AM\n2:PM");
      }
   else if(clkMenu.getCount() == 6) // UPDATES THE (TIME or PILL ALARM or ALARM) WITH THE INPUT then leaves menu
      {
      //ADD CODE

      //IF TIME
      if(clkMenu.getLevel() == 10)
      {
        //This will set the time
      }
      //IF PILL ALARM
      else if(clkMenu.getLevel() == 20)
      {
        //this will set the Pill alarm
      }
      //IF ALARM
      else if(clkMenu.getLevel() == 30)
      {
        // this will set the alarm
      }

      //clears screen
      oled.setTextColor(OLED_Backround_Color);
      oled.setCursor(menu1Xtab,menu1Y);
      if(clkMenu.getLevel() == 10){oled.print("Time\nEnter the time\n  :");}
      else if(clkMenu.getLevel() == 20){oled.print("Pill Alarm\nEnter the time\n  :");}
      else if(clkMenu.getLevel() == 30){oled.print("Alarm\nEnter the time\n  :");}
      if(hourIn < 10){oled.setCursor(hour1X,hour1Y);oled.print("0");
              oled.setCursor(hour2X,hour2Y);oled.print(hourIn);}
      else       {oled.setCursor(hour1X,hour1Y);oled.print(hourIn);}
      if(minIn > 9) {oled.setCursor(min1X,min1Y);oled.print(minIn);}
      else       {oled.setCursor(min1X,min1Y);oled.print("0");
              oled.setCursor(min2X,min2Y);oled.print(minIn);}
      oled.setCursor(menu4X, menu4Y);
      oled.print("1:AM\n2:PM");
      clkMenu.setLevel(0);

   //Turns clock back on
   clkMenu.setClkON(true);
      } //end of menu
      switch(customKey)
      {
      case '1':
        if (clkMenu.getCount() == 0 )
          {
          hourIn = 1; clkMenu.incCount();
          //CLEARS the first X
          oled.setCursor(hour1X,hour1Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the first hour digit
          oled.setCursor(hour1X,hour1Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("1");
          }
        else if (clkMenu.getCount() == 1 )
          {
          hourIn = hourIn*10 + 1; clkMenu.incCount();
          //CLEARS the second X
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second hour digit
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("1");
          }
        else if (clkMenu.getCount() == 2 )
          {
          minIn = 1; clkMenu.incCount();
          //CLEARS the third X
          oled.setCursor(min1X,min1Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the first min digit
          oled.setCursor(min1X,min1Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("1");
          }
        else if (clkMenu.getCount() == 3 )
          {
          minIn = minIn*10 + 1; clkMenu.incCount();
          //CLEARS the fourth X
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second min digit
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("1");
          }
        else if (clkMenu.getCount() == 5){ampmIn = 1; clkMenu.incCount();}
      break;//case '1'

      case '2':
        if (clkMenu.getCount() == 1 )
          {
          hourIn = hourIn*10 + 2; clkMenu.incCount();
          //CLEARS the second X
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second hour digit
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("2");
          }
        else if (clkMenu.getCount() == 2 )
          {
          minIn = 2; clkMenu.incCount();
          //CLEARS the third X
          oled.setCursor(min1X,min1Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the first min digit
          oled.setCursor(min1X,min1Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("2");
          }
        else if (clkMenu.getCount() == 3 )
          {
          minIn = minIn*10 + 2; clkMenu.incCount();
          //CLEARS the fourth X
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second min digit
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("2");
          }
        else if (clkMenu.getCount() == 5){ampmIn = 2; clkMenu.incCount();}
      break;//case '2'

      case '3':
        if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
          hourIn = 3; clkMenu.incCount();
          //CLEARS the second X
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second hour digit
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("3");
          }
        else if (clkMenu.getCount() == 2 )
          {
          minIn = 3; clkMenu.incCount();
          //CLEARS the third X
          oled.setCursor(min1X,min1Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the first min digit
          oled.setCursor(min1X,min1Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("3");
          }
        else if (clkMenu.getCount() == 3 )
          {
          minIn = minIn*10 + 3; clkMenu.incCount();
          //CLEARS the fourth X
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second min digit
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("3");
          }
      break;//case '3'

      case '4':
        if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
          hourIn = 4; clkMenu.incCount();
          //CLEARS the second X
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second hour digit
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("4");
          }
        else if (clkMenu.getCount() == 2 )
          {
          minIn = 4; clkMenu.incCount();
          //CLEARS the third X
          oled.setCursor(min1X,min1Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the first min digit
          oled.setCursor(min1X,min1Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("4");
          }
        else if (clkMenu.getCount() == 3 )
          {
          minIn = minIn*10 + 4; clkMenu.incCount();
          //CLEARS the fourth X
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second min digit
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("4");
          }
      break;//case '4'

      case '5':
       if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
          hourIn = 5; clkMenu.incCount();
          //CLEARS the second X
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second hour digit
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("5");
          }
        else if (clkMenu.getCount() == 2 )
          {
          minIn = 5; clkMenu.incCount();
          //CLEARS the third X
          oled.setCursor(min1X,min1Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the first min digit
          oled.setCursor(min1X,min1Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("5");
          }
        else if (clkMenu.getCount() == 3 )
          {
          minIn = minIn*10 + 5; clkMenu.incCount();
          //CLEARS the fourth X
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second digit
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("5");
          }
      break;//case '5'

      case '6':
       if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
          hourIn = 6; clkMenu.incCount();
          //CLEARS the second X
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second hour digit
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("6");
          }
        else if (clkMenu.getCount() == 3 )
          {
          minIn = minIn*10 + 6; clkMenu.incCount();
          //CLEARS the fourth X
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second min digit
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("6");
          }
      break;//case '6'

      case '7':
       if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
          hourIn = 7; clkMenu.incCount();
          //CLEARS the second X
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second hour digit
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("7");
          }
        else if (clkMenu.getCount() == 3 )
          {
          minIn = minIn*10 + 7; clkMenu.incCount();
          //CLEARS the fourth X
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second min digit
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("7");
          }
      break;//case '7'

      case '8':
       if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
          hourIn = 8; clkMenu.incCount();
          //CLEARS the second X
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second hour digit
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("8");
          }
        else if (clkMenu.getCount() == 3 )
          {
          minIn = minIn*10 + 8; clkMenu.incCount();
          //CLEARS the fourth X
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second min digit
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("8");
          }
      break;//case '8'

      case '9':
       if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
          hourIn = 9; clkMenu.incCount();
          //CLEARS the second X
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second hour digit
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("9");
          }
        else if (clkMenu.getCount() == 3 )
          {
          minIn = minIn*10 + 9; clkMenu.incCount();
          //CLEARS the fourth X
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second min digit
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("9");
          }
      break;//case '9'

      case '0':
        if (clkMenu.getCount() == 0 )
          {
          hourIn = 0; clkMenu.incCount();
          //CLEARS the first X
          oled.setCursor(hour1X,hour1Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the first hour digit
          oled.setCursor(hour1X,hour1Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("0");
          }
        else if (clkMenu.getCount() == 1 )
          {
          hourIn = hourIn*10 + 0; clkMenu.incCount();
          //CLEARS the second X
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second hour digit
          oled.setCursor(hour2X,hour2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("0");
          }
        else if (clkMenu.getCount() == 2 )
          {
          minIn = 0; clkMenu.incCount();
          //CLEARS the third X
          oled.setCursor(min1X,min1Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the first min digit
          oled.setCursor(min1X,min1Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("0");
          }
        else if (clkMenu.getCount() == 3 )
          {
          minIn = minIn*10 + 0; clkMenu.incCount();
          //CLEARS the fourth X
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(OLED_Backround_Color);
          oled.print("X");
          //Prints the second min digit
          oled.setCursor(min2X,min2Y);
          oled.setTextColor(clkMenu.getColor());
          oled.print("0");
          }
      break;//case '0'

      //else if (customKey == '*'){}
      case '#':
        //clears screen
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab,menu1Y);
        if(clkMenu.getLevel() == 10){oled.print("Time\nEnter the time\nXX:XX");}
        else if(clkMenu.getLevel() == 20){oled.print("Pill Alarm\nEnter the time\nXX:XX");}
        else if(clkMenu.getLevel() == 30){oled.print("Alarm\nEnter the time\nXX:XX");}

        if(hourIn < 10){oled.setCursor(hour1X,hour1Y);oled.print("0");
                        oled.setCursor(hour2X,hour2Y);oled.print(hourIn);}
        else           {oled.setCursor(hour1X,hour1Y);oled.print(hourIn);}

        if(minIn > 9)  {oled.setCursor(min1X,min1Y);oled.print(minIn);}
        else           {oled.setCursor(min1X,min1Y);oled.print("0");
                        oled.setCursor(min2X,min2Y);oled.print(minIn);}

        oled.setCursor(menu4X,menu4Y);
        oled.print("1:AM\n2:PM");

        oled.setTextColor(clkMenu.getColor());
        oled.setCursor(menu1X,menu1Y);
        oled.setTextSize(1);
        oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");

        clkMenu.setLevel(1); customKey = 'z';
    break;// case '#'
    default:
    customKey = 'z';
   }//switch(customKey)
  break;//menuLevel 10 20 30
// TIME/Pill Alarm/Alarm MENU LOOP  ---------- ↑ ---------------

// Child SAFETY or Change PIN -------------- ↓ --------------
//PINin is a temp value
  case 40: case 50: //count == 0 geting pin , count == 2 safety, count == 1 change PIN, count == 3 error menu
     oled.setTextSize(1);


    switch(customKey)
    {
    case '1':
      if (clkMenu.getCount() < 2 ) //both required inputing a pin
        {
        PINin += '1';
        //Prints the PINin
        oled.setCursor(menu4X,menu4Y);
        oled.setTextColor(clkMenu.getColor());
        oled.print(PINin);
        }
        else if (clkMenu.getCount() == 2 )
        {
        //clear screan, exit menu
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab,menu1Y);
        oled.print("Child Safety\nChild Safety is\ncurrently:");
        if (clkMenu.getChildSafety()){oled.print("ON\n1:Keep ON\n2:Turn OFF");}
        else {oled.print("OFF\n1:Turn ON\n2:Keep OFF");}
        clkMenu.setLevel(0);clkMenu.setClkON(true);
        //safety on
        clkMenu.setChildSafety(true);
        }
      else
        {
        //clear screen
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu2X,menu2Y);
        oled.print("Wrong PIN\n1:Retry Input\n2:Exit");
        //print retry
        oled.setTextColor(clkMenu.getColor());
        oled.setCursor(menu2X,menu2Y);
        oled.print("Enter your PIN\nfollowed by *\n");
        clkMenu.setCount(0);
        PINin = "";
        }
    break; //case '1'

    case '2':
      if (clkMenu.getCount() < 2 ) //both required inputing a pin
        {
        PINin += '2';
        //Prints the PINin
        oled.setCursor(menu4X,menu4Y);
        oled.setTextColor(clkMenu.getColor());
        oled.print(PINin);
        }
      else if (clkMenu.getCount() == 2 )
        {
        //clear screen, exit menu
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab,menu1Y);
        oled.print("Child Safety\nChild Safety is\ncurrently:");
        if (clkMenu.getChildSafety()){oled.print("ON\n1:Keep ON\n2:Turn OFF");}
        else {oled.print("OFF\n1:Turn ON\n2:Keep OFF");}
        clkMenu.setLevel(0);clkMenu.setClkON(true);
        //Safety Off
        clkMenu.setChildSafety(false);
        }
      else
        {
        //clear screen
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab,menu1Y);
        (clkMenu.getLevel() == 40) ? oled.print("Child Safety\n") : oled.print("Change PIN\n");
        oled.print("Wrong PIN\n1:Retry Input\n2:Exit");
        //exit
        clkMenu.setLevel(0);clkMenu.setClkON(true);
        }
    break; //case '2'

    case '3':
      if (clkMenu.getCount() < 2 ) //both required inputing a pin
        {
        PINin += '3';
        //Prints the PINin
        oled.setCursor(menu4X,menu4Y);
        oled.setTextColor(clkMenu.getColor());
        oled.print(PINin);
        }
    break; //case '3'

    case '4':
      if (clkMenu.getCount() < 2 ) //both required inputing a pin
        {
        PINin += '4';
        //Prints the PINin
        oled.setCursor(menu4X,menu4Y);
        oled.setTextColor(clkMenu.getColor());
        oled.print(PINin);
        }
    break; //case '4'

    case '5':
      if (clkMenu.getCount() < 2 ) //both required inputing a pin
        {
        PINin += '5';
        //Prints the PINin
        oled.setCursor(menu4X,menu4Y);
        oled.setTextColor(clkMenu.getColor());
        oled.print(PINin);
        }
    break; //case '5'

    case '6':
      if (clkMenu.getCount() < 2 ) //both required inputing a pin
        {
        PINin += '6';
        //Prints the PINin
        oled.setCursor(menu4X,menu4Y);
        oled.setTextColor(clkMenu.getColor());
        oled.print(PINin);
        }
    break; //case '6'

    case '7':
      if (clkMenu.getCount() < 2 ) //both required inputing a pin
        {
        PINin += '7';
        //Prints the PINin
        oled.setCursor(menu4X,menu4Y);
        oled.setTextColor(clkMenu.getColor());
        oled.print(PINin);
        }
    break; //case '7'

    case '8':
      if (clkMenu.getCount() < 2 ) //both required inputing a pin
        {
        PINin += '8';
        //Prints the PINin
        oled.setCursor(menu4X,menu4Y);
        oled.setTextColor(clkMenu.getColor());
        oled.print(PINin);
        }
    break; //case '8'

    case '9':
      if (clkMenu.getCount() < 2 ) //both required inputing a pin
        {
        PINin += '9';
        //Prints the PINin
        oled.setCursor(menu4X,menu4Y);
        oled.setTextColor(clkMenu.getColor());
        oled.print(PINin);
        }
    break; //case '9'

    case '0':
      if (clkMenu.getCount() < 2 ) //both required inputing a pin
        {
        PINin += '0';
        //Prints the PINin
        oled.setCursor(menu4X,menu4Y);
        oled.setTextColor(clkMenu.getColor());
        oled.print(PINin);
        }
    break; //case '0'

    case '*':
      if (clkMenu.getCount() == 0 && PINin == clkMenu.getPIN())
        {
        if(clkMenu.getLevel() == 40)
          {
          clkMenu.setCount(2);

          //clear screen
          oled.setTextColor(OLED_Backround_Color);
          oled.setCursor(menu2X,menu2Y);
          oled.print("Enter your PIN\nfollowed by *\n");oled.print(PINin);

          //print next menu
          oled.setTextColor(clkMenu.getColor());
          oled.setCursor(menu2X,menu2Y);
          oled.print("Child Safety is\ncurrently:");
          if (clkMenu.getChildSafety()){oled.print("ON\n1:Keep ON\n2:Turn OFF");}
          else {oled.print("OFF\n1:Turn ON\n2:Keep OFF");}
          PINin = "";
          }//goes to child safety submenu

        else
          {
          clkMenu.incCount(); //change pin submenu

          //clear screen
          oled.setTextColor(OLED_Backround_Color);
          oled.setCursor(menu2X,menu2Y);
          oled.print("Enter your PIN\n\n");oled.print(PINin);
          //print next menu
          oled.setTextColor(clkMenu.getColor());
          oled.setCursor(menu2X,menu2Y);
          oled.print("Enter a new PIN");

          PINin = ""; //resets PINin to allow input of new PINin
            }//goes to change pin submenu
        }
      else if (clkMenu.getCount() == 0 && PINin != clkMenu.getPIN())
        {
        clkMenu.setCount(3);
        //clear screen
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu2X,menu2Y);
        oled.print("Enter your PIN\nfollowed by *\n");oled.print(PINin);
        //print Error message
        oled.setTextColor(clkMenu.getColor());
        oled.setCursor(menu2X,menu2Y);
        oled.print("Wrong PIN\n1:Retry Input\n2:Exit");

        }//error submenu
      else if (clkMenu.getCount() == 1)
        {
        clkMenu.setPIN(PINin);
        //clear screan
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab,menu1Y);
        oled.print("Change Pin\nEnter a new PIN\nfollowed by a *\n");oled.print(PINin);
        clkMenu.setLevel(0);clkMenu.setClkON(true);
        } //Finished inputing new PIN

    break; //case '*'


   // Return to Prev Menu
    case '#':
    // UPDATE FOR THE SUB MENU TEXT OPTIONS

    //clears screen
      oled.setTextColor(OLED_Backround_Color);
      oled.setCursor(menu1Xtab,menu1Y);
      if(clkMenu.getLevel() == 40){oled.print("Child Safety\nEnter your PIN\nfollowed by *\n");oled.print(PINin);}
      else if(clkMenu.getLevel() == 50){oled.print("Change PIN\nEnter your PIN\nfollowed by *\n");oled.print(PINin);}
    //prev menu
      oled.setTextColor(clkMenu.getColor());
      oled.setCursor(menu1X,menu1Y);
      oled.setTextSize(1);
      oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");

      clkMenu.setLevel(1); customKey = 'z';
    break;//case '#'
    default:
    customKey = 'z';

   } // switch(customKey)

  break;//menuLevel 40 50
// Child SAFETY or Change PIN -------------- ↑ --------------

// WiFi
  case 60:
     oled.setTextSize(1);
     /*
uint16_t abLine = 0;
//  keypad press:  1   2   3   4    5   6    7   8   9
char alphabet[] = {'a','b','c' ,'d','e','f' ,'g','h','i',   // 0
                   'j','k','l' ,'m','n','o' ,'p','q','r',   // 1
                   's','t','u' ,'v','w','x' ,'y','z',' ',   // 2
                   'A','B','C' ,'D','E','F' ,'G','H','I',   // 3
                   'J','K','L' ,'M','N','N' ,'O','P','Q',   // 4
                   'R','S','T' ,'U','V','W' ,'X','Y','Z',   // 5
                   '0','1','2' ,'3','4','5' ,'6','7','8',   // 6
                   '9','!','@' ,'#','$','%' ,'^','&','*',   // 7
                   '(',')','-' ,'_','=','+' ,',','?','.',   // 8
                   '<','>','\'','"','\\','/','|',':',';',   // 9
                   '"','[',']' ,'{','}' ,'`','~',' ',' ',}  // 10
      */
//print first 9

// The Char Select will display 9 char at at time for 1-9 to select them with
// * : prev menu, # : next menu, 0 : Finish
//Store into a temp string
//count = 0 for SSID, count = 1 for PASS          Add char to string          print the char
  switch(customKey)
  {
    case '1': inputString2 += alphabet[0 + (abLine * 9) ];  oled.print(alphabet[0 + (abLine * 9) ]);  break;
    case '2': inputString2 += alphabet[1 + (abLine * 9) ];  oled.print(alphabet[1 + (abLine * 9) ]);  break;
    case '3': inputString2 += alphabet[2 + (abLine * 9) ];  oled.print(alphabet[2 + (abLine * 9) ]);  break;
    case '4': inputString2 += alphabet[3 + (abLine * 9) ];  oled.print(alphabet[3 + (abLine * 9) ]);  break;
    case '5': inputString2 += alphabet[4 + (abLine * 9) ];  oled.print(alphabet[4 + (abLine * 9) ]);  break;
    case '6': inputString2 += alphabet[5 + (abLine * 9) ];  oled.print(alphabet[5 + (abLine * 9) ]);  break;
    case '7': inputString2 += alphabet[6 + (abLine * 9) ];  oled.print(alphabet[6 + (abLine * 9) ]);  break;
    case '8': inputString2 += alphabet[7 + (abLine * 9) ];  oled.print(alphabet[7 + (abLine * 9) ]);  break;
    case '9': inputString2 += alphabet[8 + (abLine * 9) ];  oled.print(alphabet[8 + (abLine * 9) ]);  break;

    //Scroll Left for input chars
    case '0':
      if( clkMenu.getCount() < 2 &&abLine > 0 )
    {
      //clear old line
      oled.setCursor(36, menu6Y);
      oled.setTextColor(OLED_Backround_Color);
      for(int i = 0; i < 9; i++){oled.print(alphabet[abLine * 9 + i]);}

      //decrement abLine
      abLine -= 1;

      //print new line
      oled.setCursor(36, menu6Y);
      oled.setTextColor(clkMenu.getColor());
      for(int i = 0; i < 9; i++){oled.print(alphabet[abLine * 9 + i]);}

      //print new line and reprint the SSID/PASS: line so the cursor is in the correct spot
      oled.setCursor(30, menu4Y);
      oled.print(inputString2);
    }
      else if( clkMenu.getCount() < 2 &&abLine == 0 )
    {
      //clear old line
      oled.setCursor(36, menu6Y);
      oled.setTextColor(OLED_Backround_Color);
      for(int i = 0; i < 9; i++){oled.print(alphabet[abLine * 9 + i]);}

      //decrement abLine
      abLine = 10;

      //print new line
      oled.setCursor(36, menu6Y);
      oled.setTextColor(clkMenu.getColor());
      for(int i = 0; i < 9; i++){oled.print(alphabet[abLine * 9 + i]);}

      //print new line and reprint the SSID/PASS: line so the cursor is in the correct spot
      oled.setCursor(30, menu4Y);
      oled.print(inputString2);
    }
    break;// case '0'

    //Scroll Right for input chars
    case '#':
      if(clkMenu.getCount() < 2 && abLine < 10)
      {
      //clear old line
      oled.setCursor(36, menu6Y);
      oled.setTextColor(OLED_Backround_Color);
      for(int i = 0; i < 9; i++){oled.print(alphabet[abLine * 9 + i]);}

      //increment abLine
      abLine += 1;

      //print new line
      oled.setCursor(36, menu6Y);
      oled.setTextColor(clkMenu.getColor());
      for(int i = 0; i < 9; i++){oled.print(alphabet[abLine * 9 + i]);}

      //print new line and reprint the SSID/PASS: line so the cursor is in the correct spot
      oled.setCursor(30, menu4Y);
      oled.print(inputString2);
      }

      else if(clkMenu.getCount() < 2 && abLine == 10)
      {
      //clear old line
      oled.setCursor(36, menu6Y);
      oled.setTextColor(OLED_Backround_Color);
      for(int i = 0; i < 9; i++){oled.print(alphabet[abLine * 9 + i]);}

      //loop abLine
      abLine = 0;

      //print new line
      oled.setCursor(36, menu6Y);
      oled.setTextColor(clkMenu.getColor());
      for(int i = 0; i < 9; i++){oled.print(alphabet[abLine * 9 + i]);}

      //print new line and reprint the SSID/PASS: line so the cursor is in the correct spot
      oled.setCursor(30, menu4Y);
      oled.print(inputString2);
      }

      else if(clkMenu.getCount() == 2)
      {
      //clear the screen
      oled.setTextColor(OLED_Backround_Color);
      oled.setCursor(menu1Xtab,menu1Y);
      oled.print("WiFi\nWhat you entered\nSSID:");
      oled.print(inputString1);

      oled.setCursor(menu2X,menu5Y);
      oled.print("PASS:");
      oled.print(inputString2);

      oled.setCursor(menu2X,menu7Y);
      oled.print("Press * to save\nPress # to exit");

      oled.setTextColor(clkMenu.getColor());
      clkMenu.setLevel(0);
      clkMenu.setClkON(true);
      }
    break;//end of #

    //Finish Input
    case '*':
    if(clkMenu.getCount() == 0)
      {
      // set the SSID
      inputString1 = inputString2;
      //Ask for Password
      oled.setTextColor(OLED_Backround_Color);
      oled.setCursor(66,menu2Y); // This x value is for [S]SID
      oled.print("SSID");
      oled.setCursor(menu4X,menu4Y); // This x value is for [S]SID:
      oled.print("SSID");
      oled.setCursor(30,menu4Y); // This x value is for SSID:[]
      oled.print(inputString2);
      inputString2 = "";

      oled.setTextColor(clkMenu.getColor());
      oled.setCursor(66,menu2Y); // This x value is for [S]SID
      oled.print("PASS");
      oled.setCursor(menu4X,menu4Y); // This x value is for [S]SID:
      oled.print("PASS:");
      clkMenu.incCount();
      }
    else if(clkMenu.getCount() == 1)
      {
      //set the wifi pass
      oled.setTextColor(OLED_Backround_Color);

      //Clear the screen
      oled.setCursor(menu2X,menu2Y);
      oled.print("Enter your PASS\nfollowed by *\nPASS:");
      oled.print(inputString2);
      oled.setCursor(6,menu6Y); // This value is for [C]har;
      oled.print("Char:");
      for(int i = 0; i < 9; i++){oled.print(alphabet[abLine * 9 + i]);}
      oled.print("\nPress:123456789\nPrev:0    Next:#");

      oled.setTextColor(clkMenu.getColor());
      //Tell the user SSID was set to ___ and Pass was set to ___
      oled.setCursor(menu2X,menu2Y);
      oled.print("What you entered\nSSID:");
      oled.print(inputString1);

      oled.setCursor(menu2X,menu5Y);
      oled.print("PASS:");
      oled.print(inputString2);

      oled.setCursor(menu2X,menu7Y);
      oled.print("Press * to save\nPress # to exit");
      //press * to return to clock
      clkMenu.incCount();
      }
     else if(clkMenu.getCount() == 2)
      {
      //save the values
      clkMenu.setSSID(inputString1);
      clkMenu.setPASS(inputString2);
      //clear the screen
      oled.setTextColor(OLED_Backround_Color);
      oled.setCursor(menu1Xtab,menu1Y);
      oled.print("WiFi\nWhat you entered\nSSID:");
      oled.print(clkMenu.getSSID());

      oled.setCursor(menu2X,menu5Y);
      oled.print("PASS:");
      oled.print(clkMenu.getPASS());

      oled.setCursor(menu2X,menu7Y);
      oled.print("Press * to save\nPress # to exit");

      oled.setTextColor(clkMenu.getColor());
      clkMenu.setLevel(0);
      clkMenu.setClkON(true);
      }
    customKey = 'z'; //prevents menu jumping
      break; //end of case'*'
    default:
      customKey = 'z';
  }//end of switch(customKey)
  break; // end of wifi Menu level 60

// Colors
  case 70:
    oled.setTextSize(1);
  // Open the color menu
  switch(customKey)
  {
    case '1': clkMenu.setColor(OLED_Color_Blue);    break;
    case '2': clkMenu.setColor(OLED_Color_Cyan);    break;
    case '3': clkMenu.setColor(OLED_Color_Green);   break;
    case '4': clkMenu.setColor(OLED_Color_Yellow);  break;
    case '5': clkMenu.setColor(OLED_Color_Magenta); break;
    case '6': clkMenu.setColor(OLED_Color_White);   break;
    case '#':
        OLED_Text_Color = clkMenu.getColor();
        //clears screen
      oled.setTextColor(OLED_Backround_Color);
    oled.setCursor(menu1Xtab,menu1Y);
    oled.print("Colors\nPick Font Color\n1:Blue\n2:Cyan\n3:Green\n4:Yellow\n5:Magenta\n6:White");
        //prev menu
        oled.setTextColor(clkMenu.getColor());
        oled.setCursor(menu1X,menu1Y);
        oled.setTextSize(1);
        oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");

      clkMenu.setLevel(1); customKey = 'z';
    break;//case '#'
    default:
    customKey = 'z';
  }//end of switch(customKey)
  break; //case 70 colors
// Pills Replaced
  case 80:
   oled.setTextSize(1);
// Reset the pill status
   if(customKey == '1')
   {
    //Yes, Reset the OUT OF PILLS ALARM, return to clock screen
    OLED_Text_Color = clkMenu.getColor();
   }
   else if(customKey == '2')
   {
    //No, Exit to clock screen
        //clears screen
      oled.setTextColor(OLED_Backround_Color);
      oled.setCursor(menu1Xtab,menu1Y);
      oled.print("Pills Replaced\nHave you reset\nyour pills?\n1:Yes\n2:No");
          //clock menu
      clkMenu.setLevel(0); customKey = 'z';
      //Turns clock back on
      clkMenu.setClkON(true);
   }
   else if (customKey == '#')
   {
          //clears screen
      oled.setTextColor(OLED_Backround_Color);
      oled.setCursor(menu1Xtab,menu1Y);
      oled.print("Pills Replaced\nHave you reset\nyour pills?\n1:Yes\n2:No");
          //prev menu
      oled.setTextColor(clkMenu.getColor());
      oled.setCursor(menu1X,menu1Y);
      oled.setTextSize(1);
      oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");

      clkMenu.setLevel(1); customKey = 'z';
   }
  break;//case 80 pills replaced
  default:
  customKey = 'z';
  }//END of switch(clkMenu.getLevel())
}//END OF KEPAD MENU FUNC


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

   if(clkMenu.getClkON()) // This will skip this code when in a menu
   {
     oled.setCursor(40,12); oled.print(':'); // This is the :, HH:MM, it doesn't need to be printed elsewhere     

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
        if(hourOld < 9)         {oled.setCursor(RTChour2X,RTChour2Y);oled.print(now.hour(), DEC);}
        else if(hourOld == 10)  {oled.setCursor(RTChour1X,RTChour1Y);oled.print(now.hour(), DEC);}
        else if(hourOld < 19)   {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 10), DEC);}
        else if(hourOld == 19)  {oled.setCursor(RTChour1X,RTChour1Y);oled.print(now.hour(), DEC);}
        else if (hourOld < 22)  {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 20), DEC);}
        else /* hourOld == 23*/ {oled.setCursor(RTChour1X,RTChour1Y);oled.print('0');oled.print(now.hour(), DEC);}
        
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
        if((hourOld > 0) && (hourOld < 9)) {oled.setCursor(RTChour2X,RTChour2Y); oled.print(now.hour(), DEC);}
        else if((hourOld > 12) && (hourOld < 21)) {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 22), DEC);}
        //midnight and noon OLD
        else if((hourOld == 0)||(hourOld == 12))  {oled.setCursor(RTChour1X,RTChour1Y);oled.print("01");}
        //9,10,11 am and pm OLD
        else if((hourOld >= 9)&&(hourOld <= 11))  {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 10), DEC);}
        else /* hourOld == 21 or 22 or 23 */      {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 22), DEC);}
        
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
        else if(minOld == 10)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(minOld);}
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
        
        if(minOld < 9)         {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print(now.minute(), DEC);}
        else if(minOld == 10)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute(), DEC);}
        else if(minOld < 19)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 10), DEC);}
        else if(minOld == 19)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute(), DEC);}
        else if(minOld < 29)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 20), DEC);}
        else if(minOld == 29)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute(), DEC);}
        else if(minOld < 39)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 30), DEC);}
        else if(minOld == 39)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute(), DEC);}
        else if(minOld < 49)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 40), DEC);}
        else if(minOld == 49)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute(), DEC);}
        else if(minOld < 59)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 50), DEC);}
        else/* minOld == 59 */ {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute(), DEC);}

         //update minOld
         if(minOld < 59){minOld += 1;} else{minOld -= 59;}
       }//END UPDATE MIN
   }//END Checks if Display Clock is ON

}//RTC TIME


void setup()
{
//rtcTime
rtc.begin();
//rtc.adjust(DateTime(__DATE__, __TIME__));
// settling time for the rtc
delay(1250);
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
//keypad
keypadMenu();

//RTC CLOCK TIME
rtcTime(0);

//CALL THE PILL ALARM FUNCTION
//  if(Pill_Alarm_Trigger_Time || pillAlarmTripped == 1){pillAlarmTripped = pillAlarm(); }

//call the alarm function here
//  if(Alarm_Trigger_Time || alarmTripped == 1 || Snooze_Alarm_Trigger_Time){alarmTripped = alarm(); }

// no need to be in too much of a hurry, shorten if too much latency
delay(100);
}