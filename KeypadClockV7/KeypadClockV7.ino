//KeypadClockV7.ino
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>
#include <Keypad.h>
#include <EEPROM.h>
#include "menu.h" //contains Menu::
//RTC CLOCK
#include "RTClib.h"
#include <Wire.h>
#include "ds3231.h"

//Motor in alarm
#include <Servo.h>
#define outputA 49
#define outputB 50


//CALL THE ANALOG PINS AS DIGITAL: call them [Pin 14 .. Pin 19]

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

///////////////////DISPLAY///////////////////////////////
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
const uint8_t menu1Y = 0;  //menu line 1
const uint8_t menu2X = 0;   //menu line 2
const uint8_t menu2Y = 8;  //menu line 2
const uint8_t menu4X = 0;   //menu line 4
const uint8_t menu4Y = 24;  //menu line 4
const uint8_t menu3X = 0;
const uint8_t menu3Y = 16;  //menu line 3
const uint8_t menu5Y = 32;  //menu line 5
const uint8_t menu6Y = 40;  //menu line 6
const uint8_t menu7Y = 48;  //menu line 7
const uint8_t menu8Y = 56;  //menu line 8

//location of HH:MM for time Menus
const uint8_t hour1X = 0;  //menu clock input
const uint8_t hour1Y = 16; //menu clock input
const uint8_t hour2X = 6;  //menu clock input
const uint8_t hour2Y = 16; //menu clock input
const uint8_t min1X = 18;  //menu clock input
const uint8_t min1Y = 16;  //menu clock input
const uint8_t min2X = 24;  //menu clock input
const uint8_t min2Y = 16;  //menu clock input

//////WiFi VARS//////////////////////////////////////
String inputString1 = ""; //temp storage
String inputString2 =""; //temp storage
uint16_t abLine = 0;
char alphabet[] = {'a','b','c' ,'d','e','f' ,'g','h','i',
                   'j','k','l' ,'m','n','o' ,'p','q','r',
                   's','t','u' ,'v','w','x' ,'y','z',' ',
                   'A','B','C' ,'D','E','F' ,'G','H','I',
                   'J','K','L' ,'M','N','O' ,'P','Q', 'R',
                   'S','T' ,'U','V','W','X' ,'Y','Z',' ',
                   '0','1','2' ,'3','4','5' ,'6','7','8',
                   '9','!','@' ,'#','$','%' ,'^','&','*',
                   '(',')','-' ,'_','=','+' ,',','?','.',
                   '<','>','\'','"','\\','/','|',':',';',
                   '[',']' ,'{','}' ,'`','~',' ',' ',' '};

// assume the display is off until configured in setup()
bool isDisplayVisible = false;
// declare size of working string buffers. Basic strlen("d hh:mm:ss") = 10
const size_t MaxString = 16;
// the string being displayed on the SSD1331 (initially empty)
char oldTimeString[MaxString] = { 0 };
// the interrupt service routine affects this
volatile bool isButtonPressed = false;

String menu1Text = "1:Time\n2:Pill Alarm\n3:Alarm\n4:Child Safety\n5:Change PIN\n6:WiFi\n7:Pills Replaced\n8:Settings";
String PINin = "";
volatile uint16_t hourIn = 0;
volatile uint16_t minIn = 0;
volatile uint16_t ampmIn = 0; //0:not set 1:AM 2:PM
//volatile uint16_t clkMenu.setColor(OLED_Color_Green);

///////////////////////RTC VAR///////////////////
//rtc clock times
uint8_t hourOld;
uint8_t minOld;
//uint8_t secOld;

// rtc clock location
const uint8_t RTChour1X = 4;  //menu clock input
const uint8_t RTChour1Y = 11; //menu clock input
const uint8_t RTChour2X = 22;  //menu clock input
const uint8_t RTChour2Y = 11; //menu clock input
const uint8_t RTCmin1X = 58;  //menu clock input
const uint8_t RTCmin1Y = 11;  //menu clock input
const uint8_t RTCmin2X = 76;  //menu clock input
const uint8_t RTCmin2Y = 11;  //menu clock input
const uint8_t RTCampmX = 15;
const uint8_t RTCampmY = 34;

/////////////////ALARM VARS//////////////////////////
//helper variable to set state of the alarm to allow loops without using a loop that will freeze the program
uint8_t pillAlarmState = 0;
uint8_t alarmState = 0;
uint8_t pillAlarmTripped = 0; //for pillAlarm()
uint8_t alarmTripped = 0; //for alarm()
uint8_t snoozeAlarmHH = 70; //garbage value before its set
uint8_t snoozeAlarmMM = 70; //garbage value before its set

// for alarm tripped func
bool speakerTripped = 0; //Lets there be sound
bool ledTripped = 0;     //Lets there be light
bool rotateTripped = 0;
uint16_t speakerSound = 500;
// for motor and encoder
volatile int16_t rotateCounter = 0;
volatile int16_t aState;
volatile int16_t aLastState;
volatile int16_t rotateAngle = 0;
//PINS
uint8_t speaker = 53;
uint8_t led = 52;
int motor = 41;

//////////////DECLARATIONS OF CLASSES//////////////////////////
// declare the display
Adafruit_SSD1331 oled = Adafruit_SSD1331(OLED_pin_cs_ss,OLED_pin_dc_rs,OLED_pin_sda_mosi,OLED_pin_scl_sck,OLED_pin_res_rst);
//declare the menu
Menu clkMenu;
//declare the clock
RTC_DS3231 rtc;
DateTime now;
//declare servo
Servo myservo;

uint16_t OLED_Text_Color = clkMenu.getColor();
//END GLOBAL VARIABLES ///////////////////////////////////////////

// interrupt service routine
void senseButtonPressed() {
    if (!isButtonPressed) {isButtonPressed = true;}
}
//FUNCTIONS
void keypadMenu();
void clearCurrSetTo(uint8_t hourIn, uint8_t minIn);

void rtcTime(uint8_t in);
uint8_t pillAlarm();
uint8_t alarm();
void speakerBoom(bool trip);
void ledIlluminate(bool trip);
bool rotatePills(bool trip);
bool cupDetected();

//////////////////////////////////////////////////////////////
void setup()
{
//rtcTime
rtc.begin();
//rtc.adjust(DateTime((__DATE__),( __TIME__)));
// settling time for the rtc
delay(750);
//oled.fillScreen(OLED_Backround_Color);

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

//WORKING RTC
RTC_DS3231 rtc;
DateTime now = rtc.now();
hourOld = now.hour();
minOld = now.minute();

//Alarm Tripped Pins
pinMode(speaker, OUTPUT);
pinMode(led, OUTPUT);

//Motor Control
myservo.attach(motor); //previously 9 check PINS above for current
pinMode (outputA,INPUT);
pinMode (outputB,INPUT);
// Reads the initial state of the outputA
aLastState = digitalRead(outputA);

//load variables into clkMenu, Alarms, Pill counter, PIN, WiFi, Time Format, Menu Color, Child Safety
clkMenu.load();
uint8_t snoozeAlarmHH = clkMenu.getAlarmHH();
uint8_t snoozeAlarmMM = clkMenu.getAlarmMM();
OLED_Text_Color = clkMenu.getColor();
oled.fillScreen(OLED_Backround_Color);
rtcTime(1);
}

void loop()
{
//keypad
if((pillAlarmTripped == 0) && (alarmTripped == 0)){keypadMenu();}   //Skip over to allow input into Alarm Functions

//RTC CLOCK TIME
rtcTime(0);
String ssid = clkMenu.getSSID();
String pass = clkMenu.getPASS();
char* SSIDin = ssid.c_str();
char* PASSin = pass.c_str();



//CALL THE PILL ALARM FUNCTION
// check if the trigger time for the pill alarm is the current time
if( (clkMenu.getPillHH() == now.hour() && clkMenu.getPillMM() == now.minute() && now.second() == 0) || (pillAlarmTripped == 1) ) 
  {    pillAlarmTripped = pillAlarm();  }

//CALL THE ALARM FUNCTION
// check if the trigger time for the pill alarm is the current time
if( (clkMenu.getAlarmHH() == now.hour() && clkMenu.getAlarmMM() == now.minute() && now.second() == 0) || (alarmTripped == 1) || 
    (clkMenu.snoozeAlarmHH == now.hour() && clkMenu.snoozeAlarmMM == now.minute() && now.second() == 0) ) 
  {
    // Check if the Pill Alarm is Active, INACTIVE: go into alarm, ACTIVE, delay until Pill Alarm is complete
    if(pillAlarmTripped == 0)    {      alarmTripped = alarm();    }
    else alarmTripped = 1;
  }
  
//CALL ALARM TRIPPED FUNTIONS
rotatePills(rotateTripped);
speakerBoom(speakerTripped);
ledIlluminate(ledTripped);


// no need to be in too much of a hurry, shorten if too much latency
//delay(100);
}
