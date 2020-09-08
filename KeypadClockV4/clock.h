//clock.h

#ifndef HEADER_CLOCK
  #define HEADER_CLOCK
   
class Clock
{
public:
  // Default Constructor
  Clock();
  Clock(uint16_t HH_in, uint16_t MM_in, uint16_t AMPM_in);
  Clock(uint16_t HH_in, uint16_t MM_in, uint16_t SS_in, uint16_t AMPM_in);

// functions
  //returns the value
  uint16_t getHH();
  uint16_t getMM();
  uint16_t getSS();
  uint16_t getAMPM(); //not set=0 AM=1 PM=2

  //pull the values from the internet and updates the values
  void pullHH();
  void pullMM();
  void pullSS();
  void pullAMPM(); //not set=0 AM=1 PM=2

  //updates the values from input
  void setHH(uint16_t hour_in);
  void setMM(uint16_t min_in);
  void setSS(uint16_t sec_in);
  void setAMPM(uint16_t AMPM_in); //not set=0 AM=1 PM=2

  void setAlarm(uint16_t hour_in, uint16_t min_in, uint16_t AMPM_in, uint16_t alarmType_in);
  void tripAlarm(uint16_t alarmType_in);
  void resetAlarm(uint16_t alarmType_in);

private:
  // time data
  uint16_t HH; //hours
  uint16_t MM; //minutes
  uint16_t SS; //seconds
  uint16_t AMPM; //not set=0 AM=1 PM=2
  uint16_t alarmType; // alarm=0 pillAlarm=1
  // alarm data
  uint16_t HHa; //alarm hour
  uint16_t MMa; //alarm minute
  uint16_t AMPMa; //not set=0 AM=1 PM=2
  // pill alarm data
  uint16_t HHp; //pill alarm hour
  uint16_t MMp; //pill alarm minute
  uint16_t AMPMp; //not set=0 AM=1 PM=2

  // functions

}; 
   
#endif
