//RTC.ino

 void rtcTime(uint8_t in)
{
   oled.setTextSize(3);
   oled.setTextColor(clkMenu.getColor());
   now = rtc.now();
   if(in == 1)
   {
    oled.setCursor(RTChour1X,RTChour1Y);
    if(clkMenu.getTimeFormat() == 24)
      {
      if(now.hour() < 10){oled.print('0');}
      oled.print(now.hour());
      }
    else //12 hour format
      {
      //1-9 am
      if((now.hour() > 0) && (now.hour() < 10))       { oled.setCursor(RTChour1X,RTChour1Y); oled.print('0'); oled.print(now.hour(), DEC);}
      //1-9 pm
      else if((now.hour() > 12) && (now.hour() < 22)) { oled.setCursor(RTChour1X,RTChour1Y); oled.print('0'); oled.print(now.hour() - 12, DEC);}
      //10am-Noon (
      else if((now.hour() > 9) && (now.hour() < 13))  {oled.setCursor(RTChour1X,RTChour1Y);oled.print((now.hour()), DEC);}
      //10pm-midnight
      else if((now.hour() > 21) && (now.hour() < 24)) {oled.setCursor(RTChour1X,RTChour1Y);oled.print(now.hour() - 12, DEC);}
      else if(now.hour() == 0)                          {oled.setCursor(RTChour1X,RTChour1Y);oled.print("12");}
      //AM PM
      if((now.hour() >= 0) && (now.hour() < 12)){oled.setTextSize(2);oled.setCursor(RTCampmX,RTCampmY);oled.print("AM");oled.setTextSize(3);} //AM
      else                                      {oled.setTextSize(2);oled.setCursor(RTCampmX,RTCampmY);oled.print("PM");oled.setTextSize(3);} //PM
      }

    oled.setCursor(40,12);
    oled.print(':');
    oled.setCursor(RTCmin1X,RTCmin1Y);
    if(now.minute() < 10){oled.print('0');}
    oled.print(now.minute());
    //update hourOld and minOld, for when you are in menu and the min/hour changes
    hourOld = now.hour();
    minOld = now.minute();
   }
   else //update
   {
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
        else if(hourOld == 9)   {oled.setCursor(RTChour1X,RTChour1Y);oled.print('0');oled.print(hourOld);}
        else if(hourOld < 19)   {oled.setCursor(RTChour2X,RTChour2Y);oled.print((hourOld - 10));}
        else if(hourOld == 19)  {oled.setCursor(RTChour1X,RTChour1Y);oled.print(hourOld);}
        else if (hourOld < 23)  {oled.setCursor(RTChour2X,RTChour2Y);oled.print((hourOld - 20));}
        else /* hourOld == 23*/ {oled.setCursor(RTChour1X,RTChour1Y);oled.print(hourOld);}

        oled.setTextColor(clkMenu.getColor());
        //PRINT now.hour(), DEC 24
        if(hourOld < 9)         {oled.setCursor(RTChour2X,RTChour2Y);oled.print(now.hour(), DEC);}
        else if(hourOld == 9)   {oled.setCursor(RTChour1X,RTChour1Y);oled.print(now.hour(), DEC);}
        else if(hourOld < 19)   {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 10), DEC);}
        else if(hourOld == 19)  {oled.setCursor(RTChour1X,RTChour1Y);oled.print(now.hour(), DEC);}
        else if (hourOld < 23)  {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 20), DEC);}
        else /* hourOld == 23*/ {oled.setCursor(RTChour1X,RTChour1Y);oled.print('0');oled.print(now.hour(), DEC);}

       }//end 24 hour

       else if(clkMenu.getTimeFormat() == 12) //12 hour format
       {
        //CLEAR hourOld 12
        //1-8 am and pm
        if((hourOld > 0) && (hourOld < 9))        {oled.setCursor(RTChour2X,RTChour2Y);oled.print(hourOld);}
        else if((hourOld > 12) && (hourOld < 21)) {oled.setCursor(RTChour2X,RTChour2Y);oled.print(hourOld - 12);}
        //midnight and noon
        else if((hourOld == 0)||(hourOld == 12) ) {oled.setCursor(RTChour1X,RTChour1Y);oled.print("12");}
        //9am and 9pm
        else if((hourOld == 9)||(hourOld == 21) ) {oled.setCursor(RTChour1X,RTChour1Y);oled.print("09");}
        //10 and 11 am and pm
        else if((hourOld > 9) && (hourOld < 12))  {oled.setCursor(RTChour2X,RTChour2Y);oled.print((hourOld - 10));}
        else /* hourOld == 22 or 23 */            {oled.setCursor(RTChour2X,RTChour2Y);oled.print((hourOld - 22));}

        //Remove the AM/PM indicator
        //remove AM if hourOld == 11
        if(hourOld == 11){oled.setTextSize(2);oled.print('A');oled.setTextSize(3);}
        //remove PM if hourOld == 23
        else if(hourOld == 23){oled.setTextSize(2);oled.print('P');oled.setTextSize(3);}

        oled.setTextColor(clkMenu.getColor());
        //PRINT now.hour(), DEC 12
        //1-8 am and pm
        if((hourOld > 0) && (hourOld < 9))        {oled.setCursor(RTChour2X,RTChour2Y);oled.print(now.hour());}
        else if((hourOld > 12) && (hourOld < 21)) {oled.setCursor(RTChour2X,RTChour2Y);oled.print(now.hour() - 12);}
        //midnight and noon
        else if((hourOld == 0)||(hourOld == 12) ) {oled.setCursor(RTChour1X,RTChour1Y);oled.print("01");}
        //9am and 9pm
        else if((hourOld == 9)||(hourOld == 21) ) {oled.setCursor(RTChour1X,RTChour1Y);oled.print("10");}
        //10 and 11 am and pm
        else if((hourOld > 9) && (hourOld < 12))  {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 10));}
        else /* hourOld == 22 or 23 */            {oled.setCursor(RTChour2X,RTChour2Y);oled.print((now.hour() - 22));}

        //ADD the AM/PM indicator Prints the M, just to make sure it is there, it was missing in a run through
        //Add AM if hourOld == 0
        if(hourOld == 0) {oled.setTextSize(2);oled.setCursor(RTCampmX,RTCampmY);oled.print("AM");oled.setTextSize(3);}
        //Add PM if hourOld == 12
        if(hourOld == 12){oled.setTextSize(2);oled.setCursor(RTCampmX,RTCampmY);oled.print("PM");oled.setTextSize(3);}

       }//end 12 hour

       //update hourOld
       if(hourOld < 23){hourOld += 1;} else{hourOld = 0;}
     }//END UPDATE HOUR

// CHECK AND UPDATE MINUTES
       oled.setCursor(RTCmin1X,RTCmin1Y);
       if(minOld != now.minute())
       {
        //CLEAR minOld
        oled.setTextColor(OLED_Backround_Color);

        if(minOld < 9)         {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print(minOld);}
        else if(minOld == 9)   {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print('0');oled.print(minOld);}
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
        else if(minOld == 9)   {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute(), DEC);}
        else if(minOld < 19)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 10), DEC);}
        else if(minOld == 19)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute(), DEC);}
        else if(minOld < 29)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 20), DEC);}
        else if(minOld == 29)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute(), DEC);}
        else if(minOld < 39)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 30), DEC);}
        else if(minOld == 39)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute(), DEC);}
        else if(minOld < 49)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 40), DEC);}
        else if(minOld == 49)  {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print(now.minute(), DEC);}
        else if(minOld < 59)   {oled.setCursor(RTCmin2X,RTCmin2Y);oled.print((now.minute() - 50), DEC);}
        else/* minOld == 59 */ {oled.setCursor(RTCmin1X,RTCmin1Y);oled.print('0');oled.print(now.minute(), DEC);}

         //update minOld
         if(minOld < 59){minOld += 1;} else{minOld = 0;}
       }//END UPDATE MIN
   }//END Checks if Display Clock is ON
   }//update
}//RTC TIME

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ALARMS

//have these as variable of menu class, public variables
//have them set when the alarm time is set, same function call
uint8_t snoozeAlarmHH = clkMenu.getAlarmHH();
uint8_t snoozeAlarmMM = clkMenu.getAlarmMM();



uint8_t pillAlarm()
{
  uint8_t AlarmTripped = 1; //0 for false 1 for true
  switch(pillAlarmState)
  {
    case 0:
    // Turn on LEDS that shine on the cup
    // DAVID INSERT HERE

    //Turn on the Speaker
    // DAVID INSERT HERE

    pillAlarmState = 1;
    // NO break; to allow fall through

    case 1:
    //checks shild safety on/OFF
    //if on get PIN INPUT
    if(clkMenu.getChildSafety())
    {
      // I'll do this later, I will just need to paste code in here and modify it minimaly
      // I am leavbing it out because it is a lot of lines
      pillAlarmState = 2; //skips for now
    }
    else {pillAlarmState = 2;} //if child safety is false this will skip this section
    
    if(PINin == clkMenu.getPIN()){pillAlarmState = 2;}
    break; // this will allow looping over

    case 2:
    //wait for the cup to be in place VIA the light sensor
    // if it is in place set [pillAlarmState = 3;]
    // DAVID INSERT HERE
    break;

    case 3:
    //rotate the motor to dispense the pills
    // DAVID INSERT HERE

    pillAlarmState = 4;
    //allow fallthrough
    case 4:
    // I WILL NEED TO ADD THE SNOOZE FROM THE ALARM CODE


    //check if the cup has been removed
    //snooze when removed
    // if it is removed, set [pillAlarmState = 5;]
    // DAVID INSERT HERE

    break; //this causes a loop until cup removed

    case 5:
    //check if cup was returned
    //true -> turn off Pill ALARM: LED, Speaker
    // DAVID INSERT HERE

    //increment the pillAlarm counter
    clkMenu.incPillAlarm();
    AlarmTripped = 0;
    pillAlarmState = 0;
    //break;
    //default:
  }//switch(pillAlarmState)
  return AlarmTripped;
}//pillAlarm()

//This is how to call this function in the loop

// check if the trigger time for the pill alarm is the current time
// These commands will be implemented in final
  //clkMenu.getPillHH();
  //clkMenu.getPillMM();
  //if(Pill_Alarm_Trigger_Time || pillAlarmTripped == 1){pillAlarmTripped = pillAlarm(); }


// ------------------------------------------------------------------------------------

//use global variables
uint8_t alarm()
{
  uint8_t AlarmTripped = 1; //0 for false 1 for true
  switch(alarmState)
  {
    case 0:
    //Turn on the Speaker
    // DAVID INSERT HERE

    alarmState = 1;
    // NO break; to allow fall through

    case 1:
    // Get input from keypad to Snooze alarm, 0 stops, 1 snooze for 1 min, ... 8 snooze for 8 min
    switch(customKey)
    {
      case '1':
      snoozeAlarmMM += 1;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '2':
      snoozeAlarmMM += 2;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '3':
      snoozeAlarmMM += 3;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '4':
      snoozeAlarmMM += 4;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '5':
      snoozeAlarmMM += 5;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '6':
      snoozeAlarmMM += 6;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '7':
      snoozeAlarmMM += 7;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '8':
      snoozeAlarmMM += 8;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '9':
      snoozeAlarmMM += 9;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '0':
      // normalize the snooze global variables
      clkMenu.snoozeAlarmHH = clkMenu.getAlarmHH();
      clkMenu.snoozeAlarmMM = clkMenu.getAlarmMM();

      //break;
      //default:
    }
    break; // this will allow looping over

    case 2:
    // turn off ALARM: Speaker
    // DAVID INSERT HERE

    AlarmTripped = 0;
    alarmState = 0;
    //break;
    //default:
  }//switch(alarmState)
  return AlarmTripped;
}//alarm()

//This is how to call this function in the loop

// check if the trigger time for the pill alarm is the current time
// These commands will be implemented in final
  //clkMenu.getAlarmHH();
  //clkMenu.getAlarmMM();
  //if(Alarm_Trigger_Time || alarmTripped == 1 || Snooze_Alarm_Trigger_Time){alarmTripped = alarm(); }
