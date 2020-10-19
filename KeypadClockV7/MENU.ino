//MENU.ino


void keypadMenu()
{
  customKey = customKeypad.getKey();
  if (customKey) {
    Serial.println(customKey);
  }
  switch (clkMenu.getLevel())
  {
    case 0:
          if (customKey == '1'){ OLED_Text_Color = OLED_Color_White; }
          else if (customKey == '2'){ OLED_Text_Color = OLED_Color_Green; }
          else if (customKey == '3'){ oled.setCursor(menu1X, menu7Y); oled.setTextSize(1);
          oled.print(clkMenu.getPIN().c_str()); oled.print(clkMenu.getSSID().c_str()); oled.print(clkMenu.getPASS().c_str());   }
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
            oled.drawPixel(89, 1, OLED_Backround_Color);
            oled.drawPixel(95, 1, OLED_Backround_Color);
                        // X←,Y↑,↔,↨, Color
             oled.fillRect(90, 2, 5, 7, OLED_Color_Green); //Green Fill
                       // X, Y, Color
             oled.drawPixel(90, 2, OLED_Color_White);  //Outline
             oled.drawPixel(94, 2, OLED_Color_White);

          }
          else if (customKey == '6')
          {
            //Wifi Connected
            //outline
            oled.drawLine(77,3,82,8,OLED_Color_White); // x1 y1 x2 y2 color
            oled.drawLine(83,7,87,3,OLED_Color_White); // x1 y1 x2 y2 color
            oled.drawPixel(86,2,OLED_Color_White);
            oled.drawPixel(86,2,OLED_Color_White);
            oled.drawPixel(85,1,OLED_Color_White);
            oled.drawPixel(84,1,OLED_Color_White);
            oled.drawLine(83,0,81,0,OLED_Color_White); // x1 y1 x2 y2 color
            oled.drawPixel(80,1,OLED_Color_White);
            oled.drawPixel(79,1,OLED_Color_White);
            oled.drawPixel(78,2,OLED_Color_White);
            //fill connected
            oled.fillTriangle(78,3,82,7,86,3, clkMenu.getColor()  ); //x0 y0 x1 y1 x2 y2 color
            oled.drawLine(79,2,85,2, clkMenu.getColor() );
            oled.drawLine(81,1,83,1, clkMenu.getColor() );
          }
          else if (customKey == '7')
          {
            //Wifi Disconnected
            //outline
            oled.drawLine(77,3,82,8,OLED_Color_White); // x1 y1 x2 y2 color
            oled.drawLine(83,7,87,3,OLED_Color_White); // x1 y1 x2 y2 color
            oled.drawPixel(86,2,OLED_Color_White);
            oled.drawPixel(86,2,OLED_Color_White);
            oled.drawPixel(85,1,OLED_Color_White);
            oled.drawPixel(84,1,OLED_Color_White);
            oled.drawLine(83,0,81,0,OLED_Color_White); // x1 y1 x2 y2 color
            oled.drawPixel(80,1,OLED_Color_White);
            oled.drawPixel(79,1,OLED_Color_White);
            oled.drawPixel(78,2,OLED_Color_White);
            //fill connected
            oled.fillTriangle(78,3,82,7,86,3, OLED_Backround_Color  ); //x0 y0 x1 y1 x2 y2 color
            oled.drawLine(79,2,85,2, OLED_Backround_Color );
            oled.drawLine(81,1,83,1, OLED_Backround_Color );
          }
          else if (customKey == '9'){OLED_Color_Black;}
          else if (customKey == '*')  //Menu
      {
        clkMenu.setClkON(false);
        oled.fillScreen(OLED_Color_Black);   //SLOW

        //oled.setTextColor(OLED_Backround_Color);
        //oled.setCursor(hhX,hhY);
        //oled.print("XXXXX");
        oled.setTextColor(OLED_Text_Color);
        oled.setCursor(menu1X, menu1Y);
        oled.setTextSize(1);
        oled.print(menu1Text);
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
      switch (customKey)
      {
        //SET TIME
        case '1':
          //clear screen text
          oled.setTextColor(OLED_Backround_Color);
          oled.setCursor(menu1X, menu1Y);
          oled.print(menu1Text);

          oled.setTextColor(OLED_Text_Color);
          oled.setCursor(menu1Xtab, menu1Y);
          oled.print("Time\nEnter the time\nXX:XX");
          if (clkMenu.getTimeFormat() == 12) {
            clkMenu.setLevel(10); //12hr
          }
          else { /* == 24 */
            clkMenu.setLevel(15); //24hr
          }
          customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
          break; // case '1'

        //SET PILL ALARM
        case '2':
          //clear screen text
          oled.setTextColor(OLED_Backround_Color);
          oled.setCursor(menu1X, menu1Y);
          oled.print(menu1Text);

          oled.setTextColor(OLED_Text_Color);
          oled.setCursor(menu1Xtab, menu1Y);
          oled.print("Pill Alarm\nEnter the time\nXX:XX\n\n\nCurrently set to");
          if (clkMenu.getTimeFormat() == 12) 
          {
            //1-9 am
            if((clkMenu.getPillHH() > 0) && (clkMenu.getPillHH() < 10))       {oled.print('0'); oled.print(clkMenu.getPillHH(), DEC);}
            //1-9 pm
            else if((clkMenu.getPillHH() > 12) && (clkMenu.getPillHH() < 22)) {oled.print('0'); oled.print(clkMenu.getPillHH() - 12, DEC);}
            //10am-Noon (
            else if((clkMenu.getPillHH() > 9) && (clkMenu.getPillHH() < 13))  {oled.print((clkMenu.getPillHH()), DEC);}
            //10pm-midnight
            else if((clkMenu.getPillHH() > 21) && (clkMenu.getPillHH() < 24)) {oled.print(clkMenu.getPillHH() - 12, DEC);}
            else if(clkMenu.getPillHH() == 0)                                 {oled.print("12");}
            oled.print(':');
            if(clkMenu.getPillMM() < 10)                                      {oled.print('0');}oled.print(clkMenu.getPillMM());
            //AM PM
            if((clkMenu.getPillHH() >= 0) && (clkMenu.getPillHH() < 12))      {oled.print(" AM");} //AM
            else                                                              {oled.print(" PM");} //PM
            clkMenu.setLevel(20); //12hr
          }
          else /* == 24 */
          { 
            if(clkMenu.getPillHH() < 10){oled.print('0');}oled.print(clkMenu.getPillHH());
            oled.print(':');
            if(clkMenu.getPillMM() < 10){oled.print('0');}oled.print(clkMenu.getPillMM());
            clkMenu.setLevel(25); //24hr
          }
          customKey = 'z'; //This prevents the 1st input for the sub menu from being a 2
          break;//case '2'

        //SET ALARM
        case '3':
          //clear screen text
          oled.setTextColor(OLED_Backround_Color);
          oled.setCursor(menu1X, menu1Y);
          oled.print(menu1Text);

          oled.setTextColor(OLED_Text_Color);
          oled.setCursor(menu1Xtab, menu1Y);
          oled.print("Alarm\nEnter the time\nXX:XX\n\n\nCurrently set to");
          if (clkMenu.getTimeFormat() == 12) 
          {
             //1-9 am
            if((clkMenu.getAlarmHH() > 0) && (clkMenu.getAlarmHH() < 10))       {oled.print('0'); oled.print(clkMenu.getAlarmHH(), DEC);}
            //1-9 pm
            else if((clkMenu.getAlarmHH() > 12) && (clkMenu.getAlarmHH() < 22)) {oled.print('0'); oled.print(clkMenu.getAlarmHH() - 12, DEC);}
            //10am-Noon (
            else if((clkMenu.getAlarmHH() > 9) && (clkMenu.getAlarmHH() < 13))  {oled.print((clkMenu.getAlarmHH()), DEC);}
            //10pm-midnight
            else if((clkMenu.getAlarmHH() > 21) && (clkMenu.getAlarmHH() < 24)) {oled.print(clkMenu.getAlarmHH() - 12, DEC);}
            else if(clkMenu.getAlarmHH() == 0)                                  {oled.print("12");}
            oled.print(':');
            if(clkMenu.getAlarmMM() < 10)                                        {oled.print('0');}oled.print(clkMenu.getAlarmMM());
            //AM PM
            if((clkMenu.getAlarmHH() >= 0) && (clkMenu.getAlarmHH() < 12))      {oled.print(" AM");} //AM
            else                                                                {oled.print(" PM");} //PM
            clkMenu.setLevel(30); //12hr
          }
          else  /* == 24 */
          {
            if(clkMenu.getAlarmHH() < 10){oled.print('0');}oled.print(clkMenu.getAlarmHH());
            oled.print(':');
            if(clkMenu.getAlarmMM() < 10){oled.print('0');}oled.print(clkMenu.getAlarmMM());
            clkMenu.setLevel(35); //24hr
          }
          customKey = 'z'; //This prevents the 1st input for the sub menu from being a 3
          break; //case '3'

        //CHILD SAFETY
        case '4':
          //clear screen text
          oled.setTextColor(OLED_Backround_Color);
          oled.setCursor(menu1X, menu1Y);
          oled.print(menu1Text);

          oled.setTextColor(OLED_Text_Color);
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
          oled.print(menu1Text);

          oled.setTextColor(OLED_Text_Color);
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
          oled.print(menu1Text);

          oled.setTextColor(OLED_Text_Color);
          oled.setCursor(menu1Xtab, menu1Y);
          oled.print("WiFi\nEnter your SSID\nfollowed by *\nSSID:\n\n Char:");
          abLine = 0;
          for (int i = 0; i < 9; i++) {
            oled.print(alphabet[abLine * 9 + i]);
          }
          oled.print("\nPress:123456789\nPrev:0    Next:#");
          oled.setCursor(30, menu4Y);
          clkMenu.setLevel(60);
          inputString1 = "";
          inputString2 = "";
          customKey = 'z'; //This prevents the 1st input for the sub menu from being a 6
          break; //case '6'

        //Pills Replaced
        case '7':
          //clear screen text
          oled.setTextColor(OLED_Backround_Color);
          oled.setCursor(menu1X, menu1Y);
          oled.print(menu1Text);

          oled.setTextColor(OLED_Text_Color);
          oled.setCursor(menu1Xtab, menu1Y);
          oled.print("Pills Replaced\nHave you reset\nyour pills?\n1:Yes\n2:No");
          clkMenu.setLevel(70);
          customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
          break; //case '7'

        //Settings Menu
        case '8':
          //clear screen text
          oled.setTextColor(OLED_Backround_Color);
          oled.setCursor(menu1X, menu1Y);
          oled.print(menu1Text);

          oled.setTextColor(OLED_Text_Color);
          oled.setCursor(menu1Xtab, menu1Y);
          oled.print("Settings\n1:Colors\n2:Time Format");
          clkMenu.setLevel(80);
          customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
          break; //case '8'

        //Return to clock
        case '#':
          //clear screen text
          oled.setTextColor(OLED_Backround_Color);
          oled.setCursor(menu1X, menu1Y);
          oled.print(menu1Text);

          clkMenu.setLevel(0); rtcTime(1);
          clkMenu.setClkON(true);

          customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
          break; //case '#'
        default:
          customKey = 'z';
          //end default
      }// switch(customKey)
      break; //menuLevel 1
    // SUB MENU LOOP ---- ↑ -------------------------

    // TIME/Pill Alarm/Alarm MENU LOOP 12 hour ---------- ↓ ---------------
    // uses hourIn and minIn for temp storage, volatile uint16_t count is used counter var
    case 10: case 20: case 30:
      oled.setTextSize(1);
      if (clkMenu.getCount() == 4) //ADDS THE AM PM selection
      {
        clkMenu.incCount();
        oled.setTextColor(OLED_Text_Color);
        oled.setCursor(menu4X, menu4Y);
        oled.print("1:AM\n2:PM");
      }
      else if (clkMenu.getCount() == 6) // UPDATES THE (TIME or PILL ALARM or ALARM) WITH THE INPUT then leaves menu
      {
        //ADD CODE

        //IF TIME
        if (clkMenu.getLevel() == 10)
        {
          //This will set the time
          if(ampmIn == 2){
                          if(hourIn != 12){rtc.adjust(DateTime(now.year(), now.month(), now.day(), hourIn + 12, minIn, 0));}
                          else            {rtc.adjust(DateTime(now.year(), now.month(), now.day(), 12         , minIn, 0));}
                          }
          else           {
                          if(hourIn != 12){rtc.adjust(DateTime(now.year(), now.month(), now.day(), hourIn, minIn, 0));}
                          else            {rtc.adjust(DateTime(now.year(), now.month(), now.day(), 0     , minIn, 0));}
                         }
        }
        //IF PILL ALARM
        else if (clkMenu.getLevel() == 20)
        {
          oled.setTextColor(OLED_Backround_Color);
          //clear old pill alarm
          oled.setCursor(menu3X, menu6Y);
          oled.print("Currently set to");
          //1-9 am
          if((clkMenu.getPillHH() > 0) && (clkMenu.getPillHH() < 10))       {oled.print('0'); oled.print(clkMenu.getPillHH(), DEC);}
          //1-9 pm
          else if((clkMenu.getPillHH() > 12) && (clkMenu.getPillHH() < 22)) {oled.print('0'); oled.print(clkMenu.getPillHH() - 12, DEC);}
          //10am-Noon (
          else if((clkMenu.getPillHH() > 9) && (clkMenu.getPillHH() < 13))  {oled.print((clkMenu.getPillHH()), DEC);}
          //10pm-midnight
          else if((clkMenu.getPillHH() > 21) && (clkMenu.getPillHH() < 24)) {oled.print(clkMenu.getPillHH() - 12, DEC);}
          else if(clkMenu.getPillHH() == 0)                                 {oled.print("12");}
          oled.print(':');
          if(clkMenu.getPillMM() < 10)                                      {oled.print('0');}oled.print(clkMenu.getPillMM());
          //AM PM
          if((clkMenu.getPillHH() >= 0) && (clkMenu.getPillHH() < 12))      {oled.print(" AM");} //AM
          else                                                              {oled.print(" PM");} //PM
          
          //this will set the Pill alarm
          clkMenu.setPillTime(hourIn, minIn);
        }
        //IF ALARM
        else if (clkMenu.getLevel() == 30)
        {
          oled.setTextColor(OLED_Backround_Color);
          //clear old pill alarm
          oled.setCursor(menu3X, menu6Y);
          oled.print("Currently set to");
          //1-9 am
          if((clkMenu.getAlarmHH() > 0) && (clkMenu.getAlarmHH() < 10))       {oled.print('0'); oled.print(clkMenu.getAlarmHH(), DEC);}
          //1-9 pm
          else if((clkMenu.getAlarmHH() > 12) && (clkMenu.getAlarmHH() < 22)) {oled.print('0'); oled.print(clkMenu.getAlarmHH() - 12, DEC);}
          //10am-Noon (
          else if((clkMenu.getAlarmHH() > 9) && (clkMenu.getAlarmHH() < 13))  {oled.print((clkMenu.getAlarmHH()), DEC);}
          //10pm-midnight
          else if((clkMenu.getAlarmHH() > 21) && (clkMenu.getAlarmHH() < 24)) {oled.print(clkMenu.getAlarmHH() - 12, DEC);}
          else if(clkMenu.getAlarmHH() == 0)                                  {oled.print("12");}
          oled.print(':');
          if(clkMenu.getAlarmMM() < 10)                                       {oled.print('0');}oled.print(clkMenu.getAlarmMM());
          //AM PM
          if((clkMenu.getAlarmHH() >= 0) && (clkMenu.getAlarmHH() < 12))      {oled.print(" AM");} //AM
          else                                                                {oled.print(" PM");} //PM
          
          // this will set the alarm
          clkMenu.setAlarmTime(hourIn, minIn);
        }

        //clears screen
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        if (clkMenu.getLevel() == 10) {
          oled.print("Time\nEnter the time\n  :");
        }
        else if (clkMenu.getLevel() == 20) {
          oled.print("Pill Alarm\nEnter the time\n  :");
        }
        else if (clkMenu.getLevel() == 30) {
          oled.print("Alarm\nEnter the time\n  :");
        }
        if (hourIn < 10) {
          oled.setCursor(hour1X, hour1Y); oled.print("0");
          oled.setCursor(hour2X, hour2Y); oled.print(hourIn);
        }
        else       {
          oled.setCursor(hour1X, hour1Y);
          oled.print(hourIn);
        }
        if (minIn > 9) {
          oled.setCursor(min1X, min1Y);
          oled.print(minIn);
        }
        else       {
          oled.setCursor(min1X, min1Y); oled.print("0");
          oled.setCursor(min2X, min2Y); oled.print(minIn);
        }
        oled.setCursor(menu4X, menu4Y);
        oled.print("1:AM\n2:PM");
        
        clkMenu.setLevel(0); rtcTime(1);

        //Turns clock back on
        clkMenu.setClkON(true);
      } //end of menu
      switch (customKey)
      {
        case '1':
          if (clkMenu.getCount() == 0 )
          {
            hourIn = 1; clkMenu.incCount();
            //CLEARS the first X
            oled.setCursor(hour1X, hour1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first hour digit
            oled.setCursor(hour1X, hour1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("1");
          }
          else if (clkMenu.getCount() == 1 )
          {
            hourIn = hourIn * 10 + 1; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("1");
          }
          else if (clkMenu.getCount() == 2 )
          {
            minIn = 1; clkMenu.incCount();
            //CLEARS the third X
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first min digit
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("1");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 1; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("1");
          }
          else if (clkMenu.getCount() == 5) {
            ampmIn = 1;
            clkMenu.incCount();
          }
          break;//case '1'

        case '2':
          if (clkMenu.getCount() == 1 )
          {
            hourIn = hourIn * 10 + 2; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("2");
          }
          else if (clkMenu.getCount() == 2 )
          {
            minIn = 2; clkMenu.incCount();
            //CLEARS the third X
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first min digit
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("2");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 2; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("2");
          }
          else if (clkMenu.getCount() == 5) {
            ampmIn = 2;
            //hourIn += 12;
            clkMenu.incCount();
          }
          break;//case '2'

        case '3':
          if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
            hourIn = 3; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("3");
          }
          else if (clkMenu.getCount() == 2 )
          {
            minIn = 3; clkMenu.incCount();
            //CLEARS the third X
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first min digit
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("3");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 3; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("3");
          }
          break;//case '3'

        case '4':
          if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
            hourIn = 4; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("4");
          }
          else if (clkMenu.getCount() == 2 )
          {
            minIn = 4; clkMenu.incCount();
            //CLEARS the third X
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first min digit
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("4");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 4; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("4");
          }
          break;//case '4'

        case '5':
          if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
            hourIn = 5; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("5");
          }
          else if (clkMenu.getCount() == 2 )
          {
            minIn = 5; clkMenu.incCount();
            //CLEARS the third X
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first min digit
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("5");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 5; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("5");
          }
          break;//case '5'

        case '6':
          if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
            hourIn = 6; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("6");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 6; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("6");
          }
          break;//case '6'

        case '7':
          if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
            hourIn = 7; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("7");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 7; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("7");
          }
          break;//case '7'

        case '8':
          if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
            hourIn = 8; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("8");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 8; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("8");
          }
          break;//case '8'

        case '9':
          if (clkMenu.getCount() == 1 && hourIn == 0 )
          {
            hourIn = 9; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("9");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 9; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("9");
          }
          break;//case '9'

        case '0':
          if (clkMenu.getCount() == 0 )
          {
            hourIn = 0; clkMenu.incCount();
            //CLEARS the first X
            oled.setCursor(hour1X, hour1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first hour digit
            oled.setCursor(hour1X, hour1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("0");
          }
          else if ((clkMenu.getCount() == 1) && (hourIn != 0) )
          {
            hourIn = hourIn * 10 + 0; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("0");
          }
          else if (clkMenu.getCount() == 2 )
          {
            minIn = 0; clkMenu.incCount();
            //CLEARS the third X
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first min digit
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("0");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 0; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("0");
          }
          break;//case '0'

        //else if (customKey == '*'){}
        case '#':
          //clears screen
          oled.setTextColor(OLED_Backround_Color);
          oled.setCursor(menu1Xtab, menu1Y);
          if (clkMenu.getLevel() == 10) 
          {
            oled.print("Time\nEnter the time\nXX:XX");
            oled.setCursor(menu3X, menu3Y);
            if(hourIn < 10){oled.print(hourIn);oled.setCursor(menu3X, menu3Y);oled.print('0');} oled.print(hourIn);
            oled.print(':');
            if(minIn < 10) {oled.print(minIn);oled.setCursor(menu3X, menu3Y);oled.print('0');} oled.print(minIn);
          }
          else if (clkMenu.getLevel() == 20) 
          {
            oled.print("Pill Alarm\nEnter the time\nXX:XX");
            oled.setCursor(menu3X, menu3Y);
            if(hourIn < 10){oled.print(hourIn);oled.setCursor(menu3X, menu3Y);oled.print('0');} oled.print(hourIn);
            oled.print(':');
            if(minIn < 10) {oled.print(minIn);oled.setCursor(menu3X, menu3Y);oled.print('0');} oled.print(minIn);
            oled.print("\n\n\nCurrently set to");
            //1-9 am
            if((clkMenu.getPillHH() > 0) && (clkMenu.getPillHH() < 10))       {oled.print('0'); oled.print(clkMenu.getPillHH(), DEC);}
            //1-9 pm
            else if((clkMenu.getPillHH() > 12) && (clkMenu.getPillHH() < 22)) {oled.print('0'); oled.print(clkMenu.getPillHH() - 12, DEC);}
            //10am-Noon (
            else if((clkMenu.getPillHH() > 9) && (clkMenu.getPillHH() < 13))  {oled.print((clkMenu.getPillHH()), DEC);}
            //10pm-midnight
            else if((clkMenu.getPillHH() > 21) && (clkMenu.getPillHH() < 24)) {oled.print(clkMenu.getPillHH() - 12, DEC);}
            else if(clkMenu.getPillHH() == 0)                                 {oled.print("12");}
            oled.print(':');
            if(clkMenu.getPillMM() < 10)                                      {oled.print('0');}oled.print(clkMenu.getPillMM());
            //AM PM
            if((clkMenu.getPillHH() >= 0) && (clkMenu.getPillHH() < 12))      {oled.print(" AM");} //AM
            else                                                              {oled.print(" PM");} //PM
            }
          else if (clkMenu.getLevel() == 30) 
          {
            oled.print("Alarm\nEnter the time\nXX:XX");
            oled.setCursor(menu3X, menu3Y);
            if(hourIn < 10){oled.print(hourIn);oled.setCursor(menu3X, menu3Y);oled.print('0');} oled.print(hourIn);
            oled.print(':');
            if(minIn < 10) {oled.print(minIn);oled.setCursor(menu3X, menu3Y);oled.print('0');} oled.print(minIn);
            oled.print("\n\n\nCurrently set to");
            //1-9 am
            if((clkMenu.getAlarmHH() > 0) && (clkMenu.getAlarmHH() < 10))       {oled.print('0'); oled.print(clkMenu.getAlarmHH(), DEC);}
            //1-9 pm
            else if((clkMenu.getAlarmHH() > 12) && (clkMenu.getAlarmHH() < 22)) {oled.print('0'); oled.print(clkMenu.getAlarmHH() - 12, DEC);}
            //10am-Noon (
            else if((clkMenu.getAlarmHH() > 9) && (clkMenu.getAlarmHH() < 13))  {oled.print((clkMenu.getAlarmHH()), DEC);}
            //10pm-midnight
            else if((clkMenu.getAlarmHH() > 21) && (clkMenu.getAlarmHH() < 24)) {oled.print(clkMenu.getAlarmHH() - 12, DEC);}
            else if(clkMenu.getAlarmHH() == 0)                                  {oled.print("12");}
            oled.print(':'); 
            if(clkMenu.getAlarmMM() < 10)                                       {oled.print('0');}oled.print(clkMenu.getAlarmMM());
            //AM PM
            if((clkMenu.getAlarmHH() >= 0) && (clkMenu.getAlarmHH() < 12))      {oled.print(" AM");} //AM
            else                                                                {oled.print(" PM");} //PM
          }

          if (hourIn < 10) {
            oled.setCursor(hour1X, hour1Y); oled.print("0");
            oled.setCursor(hour2X, hour2Y); oled.print(hourIn);
          }
          else           {
            oled.setCursor(hour1X, hour1Y);
            oled.print(hourIn);
          }

          if (minIn > 9)  {
            oled.setCursor(min1X, min1Y);
            oled.print(minIn);
          }
          else           {
            oled.setCursor(min1X, min1Y); oled.print("0");
            oled.setCursor(min2X, min2Y); oled.print(minIn);
          }

          oled.setCursor(menu4X, menu4Y);
          oled.print("1:AM\n2:PM");

          oled.setTextColor(OLED_Text_Color);
          oled.setCursor(menu1X, menu1Y);
          oled.setTextSize(1);
          oled.print(menu1Text);

          clkMenu.setLevel(1); customKey = 'z';
          break;// case '#'
        default:
          customKey = 'z';
      }//switch(customKey)
      break;//menuLevel 10 20 30
    // TIME/Pill Alarm/Alarm MENU LOOP  12 hour---------- ↑ ---------------



    // TIME/Pill Alarm/Alarm MENU LOOP 24 Hour  ---------- ↓ ---------------
    // uses hourIn and minIn for temp storage, volatile uint16_t count is used counter var
    case 15: case 25: case 35:
      oled.setTextSize(1);

      if (clkMenu.getCount() == 4) // UPDATES THE (TIME or PILL ALARM or ALARM) WITH THE INPUT then leaves menu
      {
        //ADD CODE

        //IF TIME
        if (clkMenu.getLevel() == 15)
        {
          //This will set the time
          rtc.adjust(DateTime(now.year(), now.month(), now.day(), hourIn, minIn, 0));          
        }
        //IF PILL ALARM
        else if (clkMenu.getLevel() == 25)
        {
          oled.setTextColor(OLED_Backround_Color);
          //clear old pill alarm
          oled.setCursor(menu3X, menu6Y);
          oled.print("Currently set to");
          if(clkMenu.getPillHH() < 10){oled.print('0');}oled.print(clkMenu.getPillHH());
          oled.print(':');
          if(clkMenu.getPillMM() < 10){oled.print('0');}oled.print(clkMenu.getPillMM());          
          //this will set the Pill alarm
          clkMenu.setPillTime(hourIn, minIn);
        }
        //IF ALARM
        else if (clkMenu.getLevel() == 35)
        {
          oled.setTextColor(OLED_Backround_Color);
          //clear old pill alarm
          oled.setCursor(menu3X, menu6Y);
          oled.print("Currently set to");
          if(clkMenu.getAlarmHH() < 10){oled.print('0');}oled.print(clkMenu.getAlarmHH());
          oled.print(':');
          if(clkMenu.getAlarmMM() < 10){oled.print('0');}oled.print(clkMenu.getAlarmMM()); 
          // this will set the alarm
          clkMenu.setAlarmTime(hourIn, minIn);
        }

        //clears screen
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        if (clkMenu.getLevel() == 15) {
          oled.print("Time\nEnter the time\n  :");
        }
        else if (clkMenu.getLevel() == 25) {
          oled.print("Pill Alarm\nEnter the time\n  :");
        }
        else if (clkMenu.getLevel() == 35) {
          oled.print("Alarm\nEnter the time\n  :");
        }
        if (hourIn < 10) {
          oled.setCursor(hour1X, hour1Y); oled.print("0");
          oled.setCursor(hour2X, hour2Y); oled.print(hourIn);
        }
        else           {
          oled.setCursor(hour1X, hour1Y);
          oled.print(hourIn);
        }
        if (minIn > 9)  {
          oled.setCursor(min1X, min1Y);
          oled.print(minIn);
        }
        else           {
          oled.setCursor(min1X, min1Y); oled.print("0");
          oled.setCursor(min2X, min2Y); oled.print(minIn);
        }
        clkMenu.setLevel(0); rtcTime(1);
        //Turns clock back on
        clkMenu.setClkON(true);
      } //end of menu
      switch (customKey)
      {
        case '1':
          if (clkMenu.getCount() == 0 )
          {
            hourIn = 1; clkMenu.incCount();
            //CLEARS the first X
            oled.setCursor(hour1X, hour1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first hour digit
            oled.setCursor(hour1X, hour1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("1");
          }
          else if (clkMenu.getCount() == 1 )
          {
            hourIn = hourIn * 10 + 1; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("1");
          }
          else if (clkMenu.getCount() == 2 )
          {
            minIn = 1; clkMenu.incCount();
            //CLEARS the third X
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first min digit
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("1");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 1; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("1");
          }
          break;//case '1'

        case '2':
          if (clkMenu.getCount() == 0 )
          {
            hourIn = 2; clkMenu.incCount();
            //CLEARS the first X
            oled.setCursor(hour1X, hour1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first hour digit
            oled.setCursor(hour1X, hour1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("2");
          }
          else if (clkMenu.getCount() == 1 )
          {
            hourIn = hourIn * 10 + 2; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("2");
          }
          else if (clkMenu.getCount() == 2 )
          {
            minIn = 2; clkMenu.incCount();
            //CLEARS the third X
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first min digit
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("2");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 2; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("2");
          }
          break;//case '2'

        case '3':
          if (clkMenu.getCount() == 1 )
          {
            hourIn = hourIn * 10 + 3; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("3");
          }
          else if (clkMenu.getCount() == 2 )
          {
            minIn = 3; clkMenu.incCount();
            //CLEARS the third X
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first min digit
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("3");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 3; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("3");
          }
          break;//case '3'

        case '4':
          if (clkMenu.getCount() == 1 && hourIn < 2 )
          {
            hourIn = 4; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("4");
          }
          else if (clkMenu.getCount() == 2 )
          {
            minIn = 4; clkMenu.incCount();
            //CLEARS the third X
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first min digit
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("4");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 4; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("4");
          }
          break;//case '4'

        case '5':
          if (clkMenu.getCount() == 1 && hourIn < 2 )
          {
            hourIn = 5; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("5");
          }
          else if (clkMenu.getCount() == 2 )
          {
            minIn = 5; clkMenu.incCount();
            //CLEARS the third X
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first min digit
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("5");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 5; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("5");
          }
          break;//case '5'

        case '6':
          if (clkMenu.getCount() == 1 && hourIn < 2 )
          {
            hourIn = 6; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("6");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 6; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("6");
          }
          break;//case '6'

        case '7':
          if (clkMenu.getCount() == 1 && hourIn < 2 )
          {
            hourIn = 7; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("7");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 7; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("7");
          }
          break;//case '7'

        case '8':
          if (clkMenu.getCount() == 1 && hourIn < 2 )
          {
            hourIn = 8; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("8");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 8; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("8");
          }
          break;//case '8'

        case '9':
          if (clkMenu.getCount() == 1 && hourIn < 2 )
          {
            hourIn = 9; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("9");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 9; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("9");
          }
          break;//case '9'00000000000000000

        case '0':
          if (clkMenu.getCount() == 0 )
          {
            hourIn = 0; clkMenu.incCount();
            //CLEARS the first X
            oled.setCursor(hour1X, hour1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first hour digit
            oled.setCursor(hour1X, hour1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("0");
          }
          else if (clkMenu.getCount() == 1 )
          {
            hourIn = hourIn * 10 + 0; clkMenu.incCount();
            //CLEARS the second X
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second hour digit
            oled.setCursor(hour2X, hour2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("0");
          }
          else if (clkMenu.getCount() == 2 )
          {
            minIn = 0; clkMenu.incCount();
            //CLEARS the third X
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the first min digit
            oled.setCursor(min1X, min1Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("0");
          }
          else if (clkMenu.getCount() == 3 )
          {
            minIn = minIn * 10 + 0; clkMenu.incCount();
            //CLEARS the fourth X
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Backround_Color);
            oled.print("X");
            //Prints the second min digit
            oled.setCursor(min2X, min2Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print("0");
          }
          break;//case '0'

        //else if (customKey == '*'){}
        case '#':
          //clears screen
          oled.setTextColor(OLED_Backround_Color);
          oled.setCursor(menu1Xtab, menu1Y);
          if (clkMenu.getLevel() == 15) {oled.print("Time\nEnter the time\nXX:XX");}
          else if (clkMenu.getLevel() == 25) {oled.print("Pill Alarm\nEnter the time\nXX:XX");}
          else if (clkMenu.getLevel() == 35) {oled.print("Alarm\nEnter the time\nXX:XX");}

          oled.setCursor(hour1X, hour1Y);
          if(hourIn < 10){oled.print(hourIn);oled.setCursor(hour1X, hour1Y);oled.print('0');} oled.print(hourIn);
          oled.print(':');
          if(minIn < 10) {oled.print(minIn);oled.setCursor(hour1X, hour1Y);oled.print('0');} oled.print(minIn);

          oled.setCursor(menu3X, menu6Y);
          oled.print("Currently set to");
          if (clkMenu.getLevel() == 25) 
          {
          if(clkMenu.getPillHH() < 10){oled.print('0');}oled.print(clkMenu.getPillHH());
          oled.print(':');
          if(clkMenu.getPillMM() < 10){oled.print('0');}oled.print(clkMenu.getPillMM());  
          }
          else if (clkMenu.getLevel() == 35) 
          {
          if(clkMenu.getAlarmHH() < 10){oled.print('0');}oled.print(clkMenu.getAlarmHH());
          oled.print(':');
          if(clkMenu.getAlarmMM() < 10){oled.print('0');}oled.print(clkMenu.getAlarmMM());
          }

          oled.setTextColor(OLED_Text_Color);
          oled.setCursor(menu1X, menu1Y);
          oled.setTextSize(1);
          oled.print(menu1Text);

          clkMenu.setLevel(1); customKey = 'z';
          break;// case '#'
        default:
          customKey = 'z';
      }//switch(customKey)
      break;//menuLevel 10 20 30
    // TIME/Pill Alarm/Alarm MENU LOOP  24 HOUR---------- ↑ ---------------



    // Child SAFETY or Change PIN -------------- ↓ --------------
    //PINin is a temp value
    case 40: case 50: //count == 0 geting pin , count == 2 safety, count == 1 change PIN, count == 3 error menu
      oled.setTextSize(1);


      switch (customKey)
      {
        case '1':
          if (clkMenu.getCount() < 2 ) //both required inputing a pin
          {
            PINin += '1';
            //Prints the PINin
            oled.setCursor(menu4X, menu4Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print(PINin);
          }
          else if (clkMenu.getCount() == 2 )
          {
            //clear screan, exit menu
            oled.setTextColor(OLED_Backround_Color);
            oled.setCursor(menu1Xtab, menu1Y);
            oled.print("Child Safety\nChild Safety is\ncurrently:");
            if (clkMenu.getChildSafety()) {
              oled.print("ON\n1:Keep ON\n2:Turn OFF");
            }
            else {
              oled.print("OFF\n1:Turn ON\n2:Keep OFF");
            }
            clkMenu.setLevel(0); rtcTime(1); clkMenu.setClkON(true);
            //safety on
            clkMenu.setChildSafety(true);
          }
          else
          {
            //clear screen
            oled.setTextColor(OLED_Backround_Color);
            oled.setCursor(menu2X, menu2Y);
            oled.print("Wrong PIN\n1:Retry Input\n2:Exit");
            //print retry
            oled.setTextColor(OLED_Text_Color);
            oled.setCursor(menu2X, menu2Y);
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
            oled.setCursor(menu4X, menu4Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print(PINin);
          }
          else if (clkMenu.getCount() == 2 )
          {
            //clear screen, exit menu
            oled.setTextColor(OLED_Backround_Color);
            oled.setCursor(menu1Xtab, menu1Y);
            oled.print("Child Safety\nChild Safety is\ncurrently:");
            if (clkMenu.getChildSafety()) {
              oled.print("ON\n1:Keep ON\n2:Turn OFF");
            }
            else {
              oled.print("OFF\n1:Turn ON\n2:Keep OFF");
            }
            clkMenu.setLevel(0); rtcTime(1); clkMenu.setClkON(true);
            //Safety Off
            clkMenu.setChildSafety(false);
          }
          else
          {
            //clear screen
            oled.setTextColor(OLED_Backround_Color);
            oled.setCursor(menu1Xtab, menu1Y);
            (clkMenu.getLevel() == 40) ? oled.print("Child Safety\n") : oled.print("Change PIN\n");
            oled.print("Wrong PIN\n1:Retry Input\n2:Exit");
            //exit
            clkMenu.setLevel(0); rtcTime(1); clkMenu.setClkON(true);
          }
          break; //case '2'

        case '3':
          if (clkMenu.getCount() < 2 ) //both required inputing a pin
          {
            PINin += '3';
            //Prints the PINin
            oled.setCursor(menu4X, menu4Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print(PINin);
          }
          break; //case '3'

        case '4':
          if (clkMenu.getCount() < 2 ) //both required inputing a pin
          {
            PINin += '4';
            //Prints the PINin
            oled.setCursor(menu4X, menu4Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print(PINin);
          }
          break; //case '4'

        case '5':
          if (clkMenu.getCount() < 2 ) //both required inputing a pin
          {
            PINin += '5';
            //Prints the PINin
            oled.setCursor(menu4X, menu4Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print(PINin);
          }
          break; //case '5'

        case '6':
          if (clkMenu.getCount() < 2 ) //both required inputing a pin
          {
            PINin += '6';
            //Prints the PINin
            oled.setCursor(menu4X, menu4Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print(PINin);
          }
          break; //case '6'

        case '7':
          if (clkMenu.getCount() < 2 ) //both required inputing a pin
          {
            PINin += '7';
            //Prints the PINin
            oled.setCursor(menu4X, menu4Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print(PINin);
          }
          break; //case '7'

        case '8':
          if (clkMenu.getCount() < 2 ) //both required inputing a pin
          {
            PINin += '8';
            //Prints the PINin
            oled.setCursor(menu4X, menu4Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print(PINin);
          }
          break; //case '8'

        case '9':
          if (clkMenu.getCount() < 2 ) //both required inputing a pin
          {
            PINin += '9';
            //Prints the PINin
            oled.setCursor(menu4X, menu4Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print(PINin);
          }
          break; //case '9'

        case '0':
          if (clkMenu.getCount() < 2 ) //both required inputing a pin
          {
            PINin += '0';
            //Prints the PINin
            oled.setCursor(menu4X, menu4Y);
            oled.setTextColor(OLED_Text_Color);
            oled.print(PINin);
          }
          break; //case '0'

        case '*':
          if (clkMenu.getCount() == 0 && PINin == clkMenu.getPIN())
          {
            if (clkMenu.getLevel() == 40)
            {
                clkMenu.setCount(2);
  
                //clear screen
                oled.setTextColor(OLED_Backround_Color);
                oled.setCursor(menu2X, menu2Y);
                oled.print("Enter your PIN\nfollowed by *\n"); oled.print(PINin);
  
                //print next menu
                oled.setTextColor(OLED_Text_Color);
                oled.setCursor(menu2X, menu2Y);
                oled.print("Child Safety is\ncurrently:");
                if (clkMenu.getChildSafety()) {
                  oled.print("ON\n1:Keep ON\n2:Turn OFF");
                }
                else {
                  oled.print("OFF\n1:Turn ON\n2:Keep OFF");
                }
                PINin = "";
                
            }//goes to child safety submenu

            else
            {
              clkMenu.incCount(); //change pin submenu

              //clear screen
              oled.setTextColor(OLED_Backround_Color);
              oled.setCursor(menu2X, menu2Y);
              oled.print("Enter your PIN\n\n"); oled.print(PINin);
              //print next menu
              oled.setTextColor(OLED_Text_Color);
              oled.setCursor(menu2X, menu2Y);
              oled.print("Enter a new PIN");

              PINin = ""; //resets PINin to allow input of new PINin
            }//goes to change pin submenu
          }
          else if (clkMenu.getCount() == 0 && PINin != clkMenu.getPIN())
          {
            clkMenu.setCount(3);
            //clear screen
            oled.setTextColor(OLED_Backround_Color);
            oled.setCursor(menu2X, menu2Y);
            oled.print("Enter your PIN\nfollowed by *\n"); oled.print(PINin);
            //print Error message
            oled.setTextColor(OLED_Text_Color);
            oled.setCursor(menu2X, menu2Y);
            oled.print("Wrong PIN\n1:Retry Input\n2:Exit");

          }//error submenu
          else if (clkMenu.getCount() == 1)
          {
            clkMenu.setPIN(PINin);
            //clear screan
            oled.setTextColor(OLED_Backround_Color);
            oled.setCursor(menu1Xtab, menu1Y);
            oled.print("Change PIN\nEnter a new PIN\nfollowed by *\n"); oled.print(PINin);
            clkMenu.setLevel(0); rtcTime(1); clkMenu.setClkON(true);
          } //Finished inputing new PIN

          break; //case '*'


        // Return to Prev Menu
        case '#':
          // UPDATE FOR THE SUB MENU TEXT OPTIONS

          //clears screen
          oled.setTextColor(OLED_Backround_Color);
          oled.setCursor(menu1Xtab, menu1Y);
          if (clkMenu.getLevel() == 40) 
          {
            if(clkMenu.getCount() < 2)
            {
            oled.print("Child Safety\nEnter your PIN\nfollowed by *\n");
            oled.print(PINin);
            PINin = "";
            }
            else if (clkMenu.getCount() == 2 )
            {
            //clear screan, exit menu
            oled.setTextColor(OLED_Backround_Color);
            oled.setCursor(menu1Xtab, menu1Y);
            oled.print("Child Safety\nChild Safety is\ncurrently:");
            if (clkMenu.getChildSafety()) {oled.print("ON\n1:Keep ON\n2:Turn OFF");}
            else {oled.print("OFF\n1:Turn ON\n2:Keep OFF");}
            //clkMenu.setLevel(0); rtcTime(1); clkMenu.setClkON(true);
            }
          }
          else if (clkMenu.getLevel() == 50) 
          {
            oled.print("Change PIN\nEnter your PIN\nfollowed by *\n");
            oled.print(PINin);
            oled.setCursor(menu2X, menu2Y);
            oled.print("Enter a new PIN");
          }
          //prev menu
          oled.setTextColor(OLED_Text_Color);
          oled.setCursor(menu1X, menu1Y);
          oled.setTextSize(1);
          oled.print(menu1Text);
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
      switch (customKey)
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
          if ( clkMenu.getCount() < 2 && abLine > 0 )
          {
            //clear old line
            oled.setCursor(36, menu6Y);
            oled.setTextColor(OLED_Backround_Color);
            for (int i = 0; i < 9; i++) {
              oled.print(alphabet[abLine * 9 + i]);
            }

            //decrement abLine
            abLine -= 1;

            //print new line
            oled.setCursor(36, menu6Y);
            oled.setTextColor(OLED_Text_Color);
            for (int i = 0; i < 9; i++) {
              oled.print(alphabet[abLine * 9 + i]);
            }

            //print new line and reprint the SSID/PASS: line so the cursor is in the correct spot
            oled.setCursor(30, menu4Y);
            oled.print(inputString2);
          }
          else if ( clkMenu.getCount() < 2 && abLine == 0 )
          {
            //clear old line
            oled.setCursor(36, menu6Y);
            oled.setTextColor(OLED_Backround_Color);
            for (int i = 0; i < 9; i++) {
              oled.print(alphabet[abLine * 9 + i]);
            }

            //decrement abLine
            abLine = 10;

            //print new line
            oled.setCursor(36, menu6Y);
            oled.setTextColor(OLED_Text_Color);
            for (int i = 0; i < 9; i++) {
              oled.print(alphabet[abLine * 9 + i]);
            }

            //print new line and reprint the SSID/PASS: line so the cursor is in the correct spot
            oled.setCursor(30, menu4Y);
            oled.print(inputString2);
          }
          break;// case '0'

        //Scroll Right for input chars
        case '#':
          if (clkMenu.getCount() < 2 && abLine < 10)
          {
            //clear old line
            oled.setCursor(36, menu6Y);
            oled.setTextColor(OLED_Backround_Color);
            for (int i = 0; i < 9; i++) {
              oled.print(alphabet[abLine * 9 + i]);
            }

            //increment abLine
            abLine += 1;

            //print new line
            oled.setCursor(36, menu6Y);
            oled.setTextColor(OLED_Text_Color);
            for (int i = 0; i < 9; i++) {
              oled.print(alphabet[abLine * 9 + i]);
            }

            //print new line and reprint the SSID/PASS: line so the cursor is in the correct spot
            oled.setCursor(30, menu4Y);
            oled.print(inputString2);
          }

          else if (clkMenu.getCount() < 2 && abLine == 10)
          {
            //clear old line
            oled.setCursor(36, menu6Y);
            oled.setTextColor(OLED_Backround_Color);
            for (int i = 0; i < 9; i++) {
              oled.print(alphabet[abLine * 9 + i]);
            }

            //loop abLine
            abLine = 0;

            //print new line
            oled.setCursor(36, menu6Y);
            oled.setTextColor(OLED_Text_Color);
            for (int i = 0; i < 9; i++) {
              oled.print(alphabet[abLine * 9 + i]);
            }

            //print new line and reprint the SSID/PASS: line so the cursor is in the correct spot
            oled.setCursor(30, menu4Y);
            oled.print(inputString2);
          }

          else if (clkMenu.getCount() == 2)
          {
            //clear the screen
            oled.setTextColor(OLED_Backround_Color);
            oled.setCursor(menu1Xtab, menu1Y);
            oled.print("WiFi\nWhat you entered\nSSID:");
            oled.print(inputString1);

            oled.setCursor(menu2X, menu5Y);
            oled.print("PASS:");
            oled.print(inputString2);

            oled.setCursor(menu2X, menu7Y);
            oled.print("Press * to save\nPress # to exit");

            oled.setTextColor(OLED_Text_Color);
            clkMenu.setLevel(0); rtcTime(1);
            clkMenu.setClkON(true);
          }
          break;//end of #

        //Finish Input
        case '*':
          if (clkMenu.getCount() == 0)
          {
            // set the SSID
            inputString1 = inputString2;
            //Ask for Password
            oled.setTextColor(OLED_Backround_Color);
            oled.setCursor(66, menu2Y); // This x value is for [S]SID
            oled.print("SSID");
            oled.setCursor(menu4X, menu4Y); // This x value is for [S]SID:
            oled.print("SSID");
            oled.setCursor(30, menu4Y); // This x value is for SSID:[]
            oled.print(inputString2);
            inputString2 = "";

            oled.setTextColor(OLED_Text_Color);
            oled.setCursor(66, menu2Y); // This x value is for [S]SID
            oled.print("PASS");
            oled.setCursor(menu4X, menu4Y); // This x value is for [S]SID:
            oled.print("PASS:");
            clkMenu.incCount();
          }
          else if (clkMenu.getCount() == 1)
          {
            //set the wifi pass
            oled.setTextColor(OLED_Backround_Color);

            //Clear the screen
            oled.setCursor(menu2X, menu2Y);
            oled.print("Enter your PASS\nfollowed by *\nPASS:");
            oled.print(inputString2);
            oled.setCursor(6, menu6Y); // This value is for [C]har;
            oled.print("Char:");
            for (int i = 0; i < 9; i++) {
              oled.print(alphabet[abLine * 9 + i]);
            }
            oled.print("\nPress:123456789\nPrev:0    Next:#");

            oled.setTextColor(OLED_Text_Color);
            //Tell the user SSID was set to ___ and Pass was set to ___
            oled.setCursor(menu2X, menu2Y);
            oled.print("What you entered\nSSID:");
            oled.print(inputString1);

            oled.setCursor(menu2X, menu5Y);
            oled.print("PASS:");
            oled.print(inputString2);

            oled.setCursor(menu2X, menu7Y);
            oled.print("Press * to save\nPress # to exit");
            //press * to return to clock
            clkMenu.incCount();
          }
          else if (clkMenu.getCount() == 2)
          {
            //save the values
            clkMenu.setWiFi(inputString1, inputString2);
            //clear the screen
            oled.setTextColor(OLED_Backround_Color);
            oled.setCursor(menu1Xtab, menu1Y);
            oled.print("WiFi\nWhat you entered\nSSID:");
            oled.print(clkMenu.getSSID());

            oled.setCursor(menu2X, menu5Y);
            oled.print("PASS:");
            oled.print(clkMenu.getPASS());

            oled.setCursor(menu2X, menu7Y);
            oled.print("Press * to save\nPress # to exit");

            oled.setTextColor(OLED_Text_Color);
            clkMenu.setLevel(0); rtcTime(1);
            clkMenu.setClkON(true);
          }
          customKey = 'z'; //prevents menu jumping
          break; //end of case'*'
        default:
          customKey = 'z';
      }//end of switch(customKey)
      break; // end of wifi Menu level 60

    //END WiFi /////////////////////////////START PILLS REPLACED
    // Pills Replaced
    case 70:
      oled.setTextSize(1);
      // Reset the pill status
      if (customKey == '1')
      {
        //Yes, Reset the OUT OF PILLS ALARM, return to clock screen
        clkMenu.resetPillCounter();
        OLED_Text_Color = clkMenu.getColor();

        //clears screen
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Pills Replaced\nHave you reset\nyour pills?\n1:Yes\n2:No");

        //Exit to Clock
        clkMenu.setLevel(0); rtcTime(1);
        clkMenu.setClkON(true);
      }
      else if (customKey == '2')
      {
        //No, Exit to clock screen
        //clears screen
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Pills Replaced\nHave you reset\nyour pills?\n1:Yes\n2:No");
        //clock menu
        clkMenu.setLevel(0); rtcTime(1); customKey = 'z';
        //Turns clock back on
        clkMenu.setClkON(true);
      }
      else if (customKey == '#')
      {
        //clears screen
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Pills Replaced\nHave you reset\nyour pills?\n1:Yes\n2:No");
        //prev menu
        oled.setTextColor(OLED_Text_Color);
        oled.setCursor(menu1X, menu1Y);
        oled.setTextSize(1);
        oled.print(menu1Text);

        clkMenu.setLevel(1); customKey = 'z';
      }
      break;//case 70 pills replaced
    /////// END PILLS REPLACED/////////////// START SETTINGS

    case 80:
      //
      oled.setTextSize(1);
      if (customKey == '1')
      {
        //Color Menu
        //clear screen text
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Settings\n1:Colors\n2:Time Format");

        oled.setTextColor(OLED_Text_Color);
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
        oled.setTextColor(OLED_Text_Color);
        clkMenu.setLevel(81);
        customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
      }
      else if (customKey == '2')
      {
        //Time Format Menu
        //clear screen text
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Settings\n1:Colors\n2:Time Format");

        oled.setTextColor(OLED_Text_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Time Format\n1:12 Hour\n2:24 Hour");
        clkMenu.setLevel(82);
        customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
      }
      else if (customKey == '#')
      {
        //clears screen
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Settings\n1:Colors\n2:Time Format");
        //prev menu
        oled.setTextColor(OLED_Text_Color);
        oled.setCursor(menu1X, menu1Y);
        oled.setTextSize(1);
        oled.print(menu1Text);

        clkMenu.setLevel(1); customKey = 'z';
      }

      break;

    ////////////END SETTINGS START COLORS////////////

    case 81:
      oled.setTextSize(1);
      // Open the color menu
      switch (customKey)
      {
        case '1': clkMenu.setColor(OLED_Color_Blue); OLED_Text_Color = OLED_Color_Blue;
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Colors\nPick Font Color\n1:Blue\n2:Cyan\n3:Green\n4:Yellow\n5:Magenta\n6:White");
        //Exit to Clock
        clkMenu.setLevel(0); rtcTime(1);
        clkMenu.setClkON(true);
        customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1   
        break;
        
        case '2': clkMenu.setColor(OLED_Color_Cyan); OLED_Text_Color = OLED_Color_Cyan;
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Colors\nPick Font Color\n1:Blue\n2:Cyan\n3:Green\n4:Yellow\n5:Magenta\n6:White");
        //Exit to Clock
        clkMenu.setLevel(0); rtcTime(1);
        clkMenu.setClkON(true);
        customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1 
        break;
        
        case '3': clkMenu.setColor(OLED_Color_Green); OLED_Text_Color = OLED_Color_Green;
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Colors\nPick Font Color\n1:Blue\n2:Cyan\n3:Green\n4:Yellow\n5:Magenta\n6:White");
        //Exit to Clock
        clkMenu.setLevel(0); rtcTime(1);
        clkMenu.setClkON(true);
        customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1 
        break;
        
        case '4': clkMenu.setColor(OLED_Color_Yellow); OLED_Text_Color = OLED_Color_Yellow;
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Colors\nPick Font Color\n1:Blue\n2:Cyan\n3:Green\n4:Yellow\n5:Magenta\n6:White");
        //Exit to Clock
        clkMenu.setLevel(0); rtcTime(1);
        clkMenu.setClkON(true);
        customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1 
        break;
        
        case '5': clkMenu.setColor(OLED_Color_Magenta); OLED_Text_Color = OLED_Color_Magenta;
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Colors\nPick Font Color\n1:Blue\n2:Cyan\n3:Green\n4:Yellow\n5:Magenta\n6:White");
        //Exit to Clock
        clkMenu.setLevel(0); rtcTime(1);
        clkMenu.setClkON(true);
        customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1 
        break;
        
        case '6': clkMenu.setColor(OLED_Color_White); OLED_Text_Color = OLED_Color_White;
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Colors\nPick Font Color\n1:Blue\n2:Cyan\n3:Green\n4:Yellow\n5:Magenta\n6:White");
        //Exit to Clock
        clkMenu.setLevel(0); rtcTime(1);
        clkMenu.setClkON(true);
        customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1 
        break;
        
        case '#':
          OLED_Text_Color = clkMenu.getColor();
          //clears screen
          oled.setTextColor(OLED_Backround_Color);
          oled.setCursor(menu1Xtab, menu1Y);
          oled.print("Colors\nPick Font Color\n1:Blue\n2:Cyan\n3:Green\n4:Yellow\n5:Magenta\n6:White");
          //prev menu
          oled.setTextColor(OLED_Text_Color);
          oled.setCursor(menu1Xtab, menu1Y);
          //oled.setTextSize(1);
          oled.print("Settings\n1:Colors\n2:Time Format");

          clkMenu.setLevel(80); customKey = 'z';
          break;//case '#'
        default:
          customKey = 'z';
      }//end of switch(customKey)
      break; //case 81 colors
    //////////////////end COLORS////////////start Time Format
    case 82:
      //
      oled.setTextSize(1);
      if (customKey == '1')
      {
        clkMenu.setTimeFormat(12);
        //clears screen
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Time Format\n1:12 Hour\n2:24 Hour");
        //Exit to Clock
        clkMenu.setLevel(0); rtcTime(1);
        clkMenu.setClkON(true);
        customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
      }
      else if (customKey == '2')
      {
        clkMenu.setTimeFormat(24);
        //clears screen
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Time Format\n1:12 Hour\n2:24 Hour");
        //Exit To Clock
        clkMenu.setLevel(0); rtcTime(1);
        clkMenu.setClkON(true);
        customKey = 'z'; //This prevents the 1st input for the sub menu from being a 1
      }
      else if (customKey == '#')
      {
        //clears screen
        oled.setTextColor(OLED_Backround_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.print("Time Format\n1:12 Hour\n2:24 Hour");
        //prev menu
        oled.setTextColor(OLED_Text_Color);
        oled.setCursor(menu1Xtab, menu1Y);
        oled.setTextSize(1);
        oled.print("Settings\n1:Colors\n2:Time Format");

        clkMenu.setLevel(80); customKey = 'z';
      }
      break; //case 82
    /////////////////////end Time Format/////////////
    default:
      customKey = 'z';
  }//END of switch(clkMenu.getLevel())
}//END OF KEPAD MENU FUNC
