//RTC.ino

 void rtcTime(uint8_t in)
{
   
   now = rtc.now();

   if(clkMenu.getClkON()) // This will skip this code when in a menu
     {
     //CHECK IF OUT OF PILLS
     if(clkMenu.getPillCounter() == 7){oled.setTextColor(OLED_Color_Red);}
     else                             {oled.setTextColor(OLED_Backround_Color);}
     // if pill counter == 7 print in red else print in backround
     oled.setTextSize(1);
     oled.setCursor(menu1X,menu1Y);
     oled.print("OUT OF PILLS");
     }
   
   oled.setTextSize(3);
   oled.setTextColor(OLED_Text_Color);
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

    oled.setCursor(40,11);
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
     oled.setCursor(40,11); oled.print(':'); // This is the :, HH:MM, it doesn't need to be printed elsewhere

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

        oled.setTextColor(OLED_Text_Color);
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
        if(hourOld == 11){oled.setTextSize(2);oled.setCursor(RTCampmX,RTCampmY);oled.print('A');oled.setTextSize(3);}
        //remove PM if hourOld == 23
        else if(hourOld == 23){oled.setTextSize(2);oled.setCursor(RTCampmX,RTCampmY);oled.print('P');oled.setTextSize(3);}

        oled.setTextColor(OLED_Text_Color);
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
        else if((hourOld == 23))                  {oled.setCursor(RTChour2X,RTChour2Y);oled.print('2');}
        else /* hourOld == 22*/                   {oled.setCursor(RTChour2X,RTChour2Y);oled.print('1');}

        //ADD the AM/PM indicator
        //Add AM if hour == 0, hour old == 23
        if(hourOld == 23) {oled.setTextSize(2);oled.setCursor(RTCampmX,RTCampmY);oled.print('A');oled.setTextSize(3);}
        //Add PM if hour == 12 , hourold == 11
        else if(hourOld == 11){oled.setTextSize(2);oled.setCursor(RTCampmX,RTCampmY);oled.print('P');oled.setTextSize(3);}

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
        oled.setTextColor(OLED_Text_Color);

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
  customKey = customKeypad.getKey();
  OLED_Text_Color = OLED_Color_Red; //red for alarm
  if(now.minute() == clkMenu.getPillMM()) {rtcTime(1);} else{rtcTime(0);}
  uint8_t AlarmTripped = 1; //0 for false 1 for true
  switch(pillAlarmState)
  {
    case 0:
    // Turn on LEDS that shine on the cup
    // DAVID INSERT HERE
    

    //Turn on the Speaker
    // DAVID INSERT HERE

    if(clkMenu.getChildSafety() == 1)
    {
      oled.setTextSize(1);
      oled.setTextColor(OLED_Text_Color);
      oled.setCursor(menu1X, menu7Y);
      oled.print("Enter PIN then *");
      PINin = "";
      pillAlarmState = 1;  
    }
    else {pillAlarmState = 2; goto CASE2;}
    // NO break; to allow fall through

    case 1:
    //checks shild safety on/OFF
    //if on get PIN INPUT
      oled.setTextSize(1);

      // NON WORKING CASE 1

switch (customKey)
      {
        case '1':
          PINin += '1';
          //Prints the PINin
          oled.setCursor(menu4X, menu8Y);
          oled.setTextColor(OLED_Text_Color);
          oled.print(PINin);
        break; //case '1'

        case '2':
          PINin += '2';
          //Prints the PINin
          oled.setCursor(menu4X, menu8Y);
          oled.setTextColor(OLED_Text_Color);
          oled.print(PINin);
          break; //case '2'

        case '3':
          PINin += '3';
          //Prints the PINin
          oled.setCursor(menu4X, menu8Y);
          oled.setTextColor(OLED_Text_Color);
          oled.print(PINin);
          break; //case '3'

        case '4':
          PINin += '4';
          //Prints the PINin
          oled.setCursor(menu4X, menu8Y);
          oled.setTextColor(OLED_Text_Color);
          oled.print(PINin);
          break; //case '4'

        case '5':
          PINin += '5';
          //Prints the PINin
          oled.setCursor(menu4X, menu8Y);
          oled.setTextColor(OLED_Text_Color);
          oled.print(PINin);
          break; //case '5'

        case '6':
          PINin += '6';
          //Prints the PINin
          oled.setCursor(menu4X, menu8Y);
          oled.setTextColor(OLED_Text_Color);
          oled.print(PINin);
          break; //case '6'

        case '7':
          PINin += '7';
          //Prints the PINin
          oled.setCursor(menu4X, menu8Y);
          oled.setTextColor(OLED_Text_Color);
          oled.print(PINin);
          break; //case '7'

        case '8':
          PINin += '8';
          //Prints the PINin
          oled.setCursor(menu4X, menu8Y);
          oled.setTextColor(OLED_Text_Color);
          oled.print(PINin);
          break; //case '8'

        case '9':
          PINin += '9';
          //Prints the PINin
          oled.setCursor(menu4X, menu8Y);
          oled.setTextColor(OLED_Text_Color);
          oled.print(PINin);
          break; //case '9'

        case '0':
          PINin += '0';
          //Prints the PINin
          oled.setCursor(menu4X, menu8Y);
          oled.setTextColor(OLED_Text_Color);
          oled.print(PINin);
          break; //case '0'

        case '*':
          if (PINin == clkMenu.getPIN())
            {
            oled.setCursor(menu4X, menu7Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("Enter PIN then *\n");
            oled.print(PINin);
            //clear PINin
            PINin = "";
            //Proceed to next phase of Alarm, Dispense the Pills
            pillAlarmState = 2;
      
            }// END RIGHT INPUT
          else if (PINin != clkMenu.getPIN())
            {
            oled.setCursor(menu4X, menu8Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print(PINin);
            //clear PINin
            PINin = "";
            } // END WRONG INPUT
          break; //case '*'
        default:
          customKey = 'z';
      } // switch(customKey)

    break; // this will allow looping over prev

    CASE2:
    case 2:
    //wait for the cup to be in place VIA the light sensor
    // if it is in place set [pillAlarmState = 3;]
    // DAVID INSERT HERE

    //TEST
    if(customKey == '7'){pillAlarmState = 3;customKey = 'z';} //jump over cup in place
    break;

    case 3:
    //rotate the motor to dispense the pills
    // DAVID INSERT HERE

    pillAlarmState = 4;
    //allow fallthrough
    case 4:
    //check if the cup has been removed
    //snooze when removed
    // if it is removed, set [pillAlarmState = 5;]

    //if(removed)
    {
    //stop the speaker
    // DAVID INSERT HERE

    pillAlarmState = 5;
    //calculate time snooze ends
    clkMenu.snoozePillSS = now.second();clkMenu.snoozePillMM = now.minute() + 1; 
    if(clkMenu.snoozePillMM < 60){clkMenu.snoozePillHH = now.hour();}
    else {clkMenu.snoozePillMM = 0; clkMenu.snoozePillHH = (now.hour() + 1) % 24;}
    }
    //TEST
    if(customKey == '8'){pillAlarmState = 5;customKey = 'z';} //jump over pill removed check
    break; //loop until cup removed
    
    case 5:
    //SNOOZE for 1 min, after the min has elapsed this will be called
    if((clkMenu.snoozePillHH == now.hour()) && (clkMenu.snoozePillMM == now.minute()) && (clkMenu.snoozePillSS == now.second()))
      {
      //Enable Speaker
      // DAVID INSERT HERE

      pillAlarmState = 6;
      }
    
    //check if cup was returned
    //true -> turn off Pill ALARM: LED, Speaker
    // DAVID INSERT HERE

    //TEST
    if(customKey == '9'){pillAlarmState = 6;customKey = 'z';} //jump over pill returned check

    break; //loop until cup is returned
    
    case 6:
    //increment the pillAlarm counter
    clkMenu.incPillAlarm();
    AlarmTripped = 0;
    OLED_Text_Color = clkMenu.getColor(); //reset Color
    rtcTime(1);
    pillAlarmState = 0;
    //break;
    //default:
  }//switch(pillAlarmState)
  
  return AlarmTripped;
}//pillAlarm()


// ------------------------------------------------------------------------------------

//use global variables
uint8_t alarm()
{
  customKey = customKeypad.getKey();
  OLED_Text_Color = OLED_Color_Red; //red for alarm
  if((now.minute() == clkMenu.getAlarmMM()) || (now.minute() == clkMenu.snoozeAlarmMM)){rtcTime(1);} else{rtcTime(0);}
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
      clkMenu.snoozeAlarmMM = now.minute() + 1;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '2':
      clkMenu.snoozeAlarmMM = now.minute() +  2;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '3':
      clkMenu.snoozeAlarmMM = now.minute() +  3;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '4':
      clkMenu.snoozeAlarmMM = now.minute() +  4;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '5':
      clkMenu.snoozeAlarmMM = now.minute() +  5;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '6':
      clkMenu.snoozeAlarmMM = now.minute() +  6;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '7':
      clkMenu.snoozeAlarmMM = now.minute() +  7;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '8':
      clkMenu.snoozeAlarmMM = now.minute() +  8;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '9':
      clkMenu.snoozeAlarmMM = now.minute() +  9;
      if(clkMenu.snoozeAlarmMM >= 60){clkMenu.snoozeAlarmMM -= 60; clkMenu.snoozeAlarmHH += 1;}
      alarmState = 2;

      break;
      case '0':
      // normalize the snooze global variables
      clkMenu.snoozeAlarmHH = clkMenu.getAlarmHH();
      clkMenu.snoozeAlarmMM = clkMenu.getAlarmMM();
      alarmState = 2;

      //break;
      default:
      customKey = 'z';
    }
    break; // this will allow looping over

    case 2:
    // turn off ALARM: Speaker
    // DAVID INSERT HERE

    AlarmTripped = 0;
    OLED_Text_Color = clkMenu.getColor(); //reset Color
    rtcTime(1);
    alarmState = 0;
    //break;
    //default:
  }//switch(alarmState)
  return AlarmTripped;
}//alarm()
