#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <Keypad.h>
#include "clock.h" //contains clock::
#include "menu.h" //contains Menu::
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
const uint8_t OLED_pin_scl_sck = SCL;  //12 old
const uint8_t OLED_pin_sda_mosi = SDA; //11 old
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
const uint16_t menu1X = 0;   //menu line 1 
const uint16_t menu1Xtab = 4;//menu line 1 indent
const uint16_t menu1Y = 1;  //menu line 1 

const uint16_t menu2X = 0;   //menu line 2
const uint16_t menu2Y = 9;  //menu line 2

const uint16_t menu4X = 0;   //menu line 4
const uint16_t menu4Y = 25;  //menu line 4

const uint16_t menu3Y = 17;  //menu line 3
const uint16_t menu5Y = 33;  //menu line 5
const uint16_t menu6Y = 41;  //menu line 6
const uint16_t menu7Y = 49;  //menu line 7
const uint16_t menu8Y = 57;  //menu line 8

//location of HH:MM
const uint16_t hour1X = 0;  //menu clock input
const uint16_t hour1Y = 17; //menu clock input
const uint16_t hour2X = 6;  //menu clock input
const uint16_t hour2Y = 17; //menu clock input
const uint16_t min1X = 18;  //menu clock input
const uint16_t min1Y = 17;  //menu clock input
const uint16_t min2X = 24;  //menu clock input
const uint16_t min2Y = 17;  //menu clock input 

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
                   '"','[',']' ,'{','}' ,'`','~',' ',' ',
                   'Ä','Ï','Ö','Ü','ß' ,'ä','ï' ,'ö','ü'}; // these german char do not work so they are being ignored

// declare the display
Adafruit_SSD1331 oled = Adafruit_SSD1331(OLED_pin_cs_ss,OLED_pin_dc_rs,OLED_pin_sda_mosi,OLED_pin_scl_sck,OLED_pin_res_rst);
//declare the menu
Menu clkMenu;
uint16_t OLED_Text_Color = clkMenu.getColor();

// assume the display is off until configured in setup()
bool isDisplayVisible = false;
// declare size of working string buffers. Basic strlen("d hh:mm:ss") = 10
const size_t MaxString = 16;
// the string being displayed on the SSD1331 (initially empty)
char oldTimeString[MaxString] = { 0 };
// the interrupt service routine affects this
volatile bool isButtonPressed = false;

volatile uint16_t PINin = 0; 
volatile uint16_t hourIn = 0;
volatile uint16_t minIn = 0;
volatile uint16_t ampmIn = 0; //0:not set 1:AM 2:PM
//volatile uint16_t clkMenu.setColor(OLED_Color_Green);

// interrupt service routine
void senseButtonPressed() {
    if (!isButtonPressed) {isButtonPressed = true;}
}


void keypadMenu() {
      customKey = customKeypad.getKey();
    if (customKey){Serial.println(customKey);}

    if(clkMenu.getLevel() == 0)
    {
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
    }
// SUB MENU LOOP ---- ↓ -------------------------
    if(clkMenu.getLevel() == 1)
    { 
      oled.setTextSize(1);
      //SET TIME
     if (customKey == '1')
     {
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X,menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced"); 
   
     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("Time\nEnter the time\nXX:XX");
     clkMenu.setLevel(10);
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
     }
      //SET PILL ALARM
     else if (customKey == '2')
     {
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced"); 
   
     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("Pill Alarm\nEnter the time\nXX:XX");
     clkMenu.setLevel(20);  
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1  
     }
      //SET ALARM
     else if (customKey == '3')
     {
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced"); 
   
     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("Alarm\nEnter the time\nXX:XX");
     clkMenu.setLevel(30); 
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1  
     }
      //CHILD SAFETY
     else if (customKey == '4')
     {
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced"); 
   
     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("Child Safety\nEnter your PIN\nfollowed by *");
     clkMenu.setLevel(40);
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1  
     }
     //CHANGE PIN
     else if (customKey == '5')
     {
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced"); 
   
     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("Change PIN\nEnter your PIN\nfollowed by *");
     clkMenu.setLevel(50);
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1  
     }
     //WIFI
     else if (customKey == '6')
     {
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced"); 
   
     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("WiFi\nEnter your SSID\nfollowed by *\nSSID:\n\n Char:");
     for(int i = 0; i < 9; i++){oled.print(alphabet[abLine * 9 + i]);}
     oled.print("\nPress:123456789\nPrev:0    Next:#");
     oled.setCursor(30, menu4Y);
     clkMenu.setLevel(60);
     abLine = 0;
     inputString1 = "";
     inputString2 = "";
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1  
     }
     //Color Menu
     else if (customKey == '7')
     {
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
     }
     //Pills Replaced
     else if (customKey == '8')
     {
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced"); 
   
     oled.setTextColor(clkMenu.getColor());
     oled.setCursor(menu1Xtab, menu1Y);
     oled.print("Pills Replaced\nHave you reset\nyour pills?\n1:Yes\n2:No");
     clkMenu.setLevel(80);
     customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1  
     }
   //Return to cloclk
   else if (customKey == '#')
     {
     //clear screen text
     oled.setTextColor(OLED_Backround_Color);
     oled.setCursor(menu1X, menu1Y);
     oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced"); 
   
     clkMenu.setLevel(0);
   
   
   clkMenu.setClkON(true);
   customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1  
     }
    }
// SUB MENU LOOP ---- ↑ -------------------------
    
// TIME/Pill Alarm/Alarm MENU LOOP  ---------- ↓ ---------------
  // uses hourIn and minIn for temp storage, volatile uint16_t count is used counter var
    if(clkMenu.getLevel() == 10 || clkMenu.getLevel() == 20 || clkMenu.getLevel() == 30)
    { 
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

      //IF PILL ALARM

      //IF ALARM
      
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
   if (customKey == '1')
      {
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
      else if (clkMenu.getCount() == 5)
        {
      ampmIn = 1; clkMenu.incCount();
        }
    }
   else if (customKey == '2')
      {
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
      else if (clkMenu.getCount() == 5)
        {
      ampmIn = 2; clkMenu.incCount();
        }
    }
   else if (customKey == '3')
      {
      
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
    }
   else if (customKey == '4')
      {
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
     }
   else if (customKey == '5')
      {
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
     }
   else if (customKey == '6')
      {
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
     }
   else if (customKey == '7')
      {
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
     }     
   else if (customKey == '8')
      {
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
     }     
   else if (customKey == '9')
      {
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
     }
   else if (customKey == '0')
      {
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
    }
   //else if (customKey == '*'){}
   else if (customKey == '#')
   {
          //clears screen
      oled.setTextColor(OLED_Backround_Color);
      oled.setCursor(menu1Xtab,menu1Y);
      if(clkMenu.getLevel() == 10){oled.print("Time\nEnter the time\nXX:XX");}
      else if(clkMenu.getLevel() == 20){oled.print("Pill Alarm\nEnter the time\nXX:XX");}
      else if(clkMenu.getLevel() == 30){oled.print("Alarm\nEnter the time\nXX:XX");}
      if(hourIn < 10){oled.setCursor(hour1X,hour1Y);oled.print("0");
              oled.setCursor(hour2X,hour2Y);oled.print(hourIn);}  
      else       {oled.setCursor(hour1X,hour1Y);oled.print(hourIn);}
      if(minIn > 9) {oled.setCursor(min1X,min1Y);oled.print(minIn);}
      else       {oled.setCursor(min1X,min1Y);oled.print("0");
              oled.setCursor(min2X,min2Y);oled.print(minIn);}
      oled.setCursor(menu4X,menu4Y);
      oled.print("1:AM\n2:PM");
      
      oled.setTextColor(clkMenu.getColor());
      oled.setCursor(menu1X,menu1Y);
      oled.setTextSize(1);
      oled.print("1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Colors\n8:Pills Replaced");
      
      clkMenu.setLevel(1); customKey = 'z';
   }     
}
// TIME/Pill Alarm/Alarm MENU LOOP  ---------- ↑ ---------------

// Child SAFETY or Change PIN -------------- ↓ --------------
if(clkMenu.getLevel() == 40 || clkMenu.getLevel() == 50) //count == 0 geting pin , count ==1 safety, count ==2 change PIN, count ==3 error menu
  { 
     oled.setTextSize(1);
     //Loop adding digits until '*' is pressed
     
    if (customKey == '1')
          {
          if (clkMenu.getCount() == 0 )
            { 
            PINin = PINin * 10 + 1;  
            //Prints the PINin
            oled.setCursor(menu4X,menu4Y);
            oled.setTextColor(clkMenu.getColor());
            oled.print(PINin);
            }
          else if (clkMenu.getCount() == 1 )
            { 
          oled.print(PINin);
            }
          else if (clkMenu.getCount() == 2 )
          oled.print(PINin);
          }
   // Return to Prev Menu
   else if (customKey == '#')
   {
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
   }
     //Compare input number to clkMenu.getPIN(); if equal go into sub menu for safety/PIN change if wrong go into error menu(ask to re-enter pin or go back to clock

     //Safety Toggle Menu

     //Change PIN Menu

     //Wrong PIN Menu
  }
// Child SAFETY or Change PIN -------------- ↑ --------------
  
// WiFi
if(clkMenu.getLevel() == 60)
  { 
     oled.setTextSize(1);
     //117, 115/9=13, so 13 different "screens" to view, 2empty,last 2 are spaces inc case they are clicked
     /*
int abLine = 0;
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
                   '"','[',']' ,'{','}' ,'`','~',' ',' ',   // 10
                   'Ä','Ï','Ö','Ü','ß' ,'ä','ï' ,'ö','ü'};  // 11 // these german char do not work so they are being ignored
      */
//print first 9

     
// The Char Select will display 9 char at at time for 1-9 to select them with
// * : prev menu, # : next menu, 0 : Finish
//Store into a temp string
//count = 0 for SSID, count = 1 for PASS          Add char to string          print the char
       if(customKey == '1') {inputString2 += alphabet[0 + (abLine * 9) ];  oled.print(alphabet[0 + (abLine * 9) ]);}
  else if(customKey == '2') {inputString2 += alphabet[1 + (abLine * 9) ];  oled.print(alphabet[1 + (abLine * 9) ]);}
  else if(customKey == '3') {inputString2 += alphabet[2 + (abLine * 9) ];  oled.print(alphabet[2 + (abLine * 9) ]);}
  else if(customKey == '4') {inputString2 += alphabet[3 + (abLine * 9) ];  oled.print(alphabet[3 + (abLine * 9) ]);}
  else if(customKey == '5') {inputString2 += alphabet[4 + (abLine * 9) ];  oled.print(alphabet[4 + (abLine * 9) ]);}
  else if(customKey == '6') {inputString2 += alphabet[5 + (abLine * 9) ];  oled.print(alphabet[5 + (abLine * 9) ]);}
  else if(customKey == '7') {inputString2 += alphabet[6 + (abLine * 9) ];  oled.print(alphabet[6 + (abLine * 9) ]);}
  else if(customKey == '8') {inputString2 += alphabet[7 + (abLine * 9) ];  oled.print(alphabet[7 + (abLine * 9) ]);}
  else if(customKey == '9') {inputString2 += alphabet[8 + (abLine * 9) ];  oled.print(alphabet[8 + (abLine * 9) ]);}
  
  //Scroll Left for input chars
  else if(customKey == '0' && abLine > 0 )  
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
   else if(customKey == '0' && abLine == 0 )  
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
  
  //Scroll Right for input chars
  else if(customKey == '#') 
    {
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
    }//end of #
  
  //Finish Input
  else if(customKey == '*') 
    {
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
    customKey == 'z'; //prevents menu jumping  
    } //end of customKey == '*'
  } // end of wifi Menu
  
// Colors
if(clkMenu.getLevel() == 70)
  { 
     oled.setTextSize(1);
// Open the color menu

        if(customKey == '1'){ clkMenu.setColor(OLED_Color_Blue);}
   else if(customKey == '2'){ clkMenu.setColor(OLED_Color_Cyan);}
   else if(customKey == '3'){ clkMenu.setColor(OLED_Color_Green);}
   else if(customKey == '4'){ clkMenu.setColor(OLED_Color_Yellow);}
   else if(customKey == '5'){ clkMenu.setColor(OLED_Color_Magenta);}
   else if(customKey == '6'){ clkMenu.setColor(OLED_Color_White);}
   else if(customKey == '#')
   {
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
   }
  }
// Pills Replaced
if(clkMenu.getLevel() == 80)
  { 
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

     
  }  
}//END OF KEPAD MENU FUNC

void displayUpTime() {

    oled.setTextSize(3);

    // calculate seconds, truncated to the nearest whole second
    unsigned long upSeconds = millis() / 1000;
    // calculate days, truncated to nearest whole day
    unsigned long days = upSeconds / 86400;
    // the remaining hhmmss are
    upSeconds = upSeconds % 86400;
    // calculate hours, truncated to the nearest whole hour
    unsigned long hours = upSeconds / 3600;
    // the remaining mmss are
    upSeconds = upSeconds % 3600;
    // calculate minutes, truncated to the nearest whole minute
    unsigned long minutes = upSeconds / 60;
    // the remaining ss are
    upSeconds = upSeconds % 60;
    // allocate a buffer
    char newTimeString[MaxString] = { 0 };
    // construct the string representation
    sprintf(
        newTimeString,
        "%02lu:%02lu:%02lu",
        hours, minutes, upSeconds
    );

    // has the time string changed since the last oled update?   && Is clock Display on
    if ((strcmp(newTimeString,oldTimeString) != 0) && (clkMenu.getClkON())) {

        // yes! home the cursor
        oled.setCursor(4,12);
        // change the text color to the background color
        oled.setTextColor(OLED_Backround_Color);
        // redraw the old value to erase
        oled.print(oldTimeString);
        // home the cursor
        oled.setCursor(4,12);       
        // change the text color to foreground color
        oled.setTextColor(OLED_Text_Color);
        // draw the new time value
        oled.print(newTimeString);   
        // and remember the new value
        strcpy(oldTimeString,newTimeString);     
    }

// ALARM TEST
    unsigned long alarm = 5;
    if(upSeconds == alarm) 
      {OLED_Text_Color = OLED_Color_Red;}
    else if((upSeconds == alarm + 5)&&(OLED_Text_Color = OLED_Color_Red))
      {OLED_Text_Color = clkMenu.getColor();}
}


void setup() {

    //clock
    #if (SerialDebugging)
    Serial.begin(115200); while (!Serial); Serial.println();
    #endif

    // settling time
    delay(250);

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

void loop() {

    //keypad
    keypadMenu();
    
    //clock
    // unconditional display, regardless of whether display is visible
    displayUpTime();

    // no need to be in too much of a hurry
    delay(100);
}
