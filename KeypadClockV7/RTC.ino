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
      else if((now.hour() > 21) && (now.hour() < 24)) {oled.setCursor(RTChour1X,RTChour1Y);oled.print((now.hour()), DEC);}
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

        //ADD the AM/PM indicator
        //Add AM if hourOld == 0
        if(hourOld == 0) {oled.setTextSize(2);oled.setCursor(RTCampmX,RTCampmY);oled.print('A');oled.setTextSize(3);}
        //Add PM if hourOld == 12
        if(hourOld == 12){oled.setTextSize(2);oled.setCursor(RTCampmX,RTCampmY);oled.print('P');oled.setTextSize(3);}

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
