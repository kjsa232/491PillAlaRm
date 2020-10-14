//menu.h

#ifndef HEADER_MENU
#define HEADER_MENU

class Menu
{
public:
  // Default Constructor
  Menu();
  // functions
  
  void load();

  void setLevel(uint8_t newLevel);
  uint8_t getLevel();

  void setCount(uint8_t newCount);
  uint8_t getCount();
  void incCount();

  bool getClkON();
  void setClkON(bool state);

  void setVisability(bool state);

  void setPIN(String newPIN);
  String getPIN();

  void setColor(uint16_t newColor);
  uint16_t getColor();

  void setWiFi(String SSIDin, String PASSin);
  String getSSID(); //convert to char* with : ssid = SSID.c_str();
  String getPASS();

  void setTimeFormat(uint8_t newFormat);
  uint8_t getTimeFormat();

  void setChildSafety(bool newState);
  bool getChildSafety();

  void setAlarmTime(uint8_t hour, uint8_t min);
  uint8_t getAlarmHH();
  uint8_t getAlarmMM();

  void setPillTime(uint8_t hour, uint8_t min);
  uint8_t getPillHH();
  uint8_t getPillMM();
  
  uint8_t getPillCounter();
  void incPillAlarm();
  void resetPillCounter();


//Variables
  uint8_t snoozeAlarmHH;
  uint8_t snoozeAlarmMM;

private:
  // helper functions
  void eepromUpdateString(char address, String DATA);
  String eepromReadString(char address);
  
  // data
  uint8_t count;
  uint8_t menuLevel; // 0:main, 1:SUB MENU , 10:Time, 20:Pill Alarm, 30:Alarm, 40:Child Safety, 50:PIN, 60:WiFi,70:Pills Replaced, 
                      // 80:settings 81:Colors 82: Time Format
                      // 24 hour time menu    15:Time, 25:Pill Alarm, 35:Alarm
  bool clkON; //when true display time, when false disable to allow for menus
  uint16_t menuColor;
  String PIN; //stringg to allow leading zeros in the pin
  String wifiSSID;
  String wifiPASS;
  uint8_t timeFormat;
  bool childSafety;

  uint8_t alarmHH; //alarm hour
  uint8_t alarmMM; //alarm min

  uint8_t pillHH; //pill alarm hour
  uint8_t pillMM; //pill alarm min
  uint8_t pillCounter; //Number of times you have gonw through the pill alarm

  bool isDisplayVisible = false; // assume the display is off until configured in setup()

//Need a way to save the password, and other settings when power is lost, possibly by saving to a file and reading from a file when creating the instance of Menu clkMenu
};
#endif
