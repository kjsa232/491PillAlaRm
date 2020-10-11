//This is just a barebone file for the alarm functions that will allow me to incorporate this into the KeypadClockV4.ino


//STTART_GOLBAL_VARIABLES
//helper variable to set state of the alarm to allow loops without using a loop that will freeze the program
uint8_t pillAlarmState = 0;
uint8_t alarmState = 0;

uint8_t pillAlarmTripped = 0; //for pillAlarm()
uint8_t alarmTripped = 0; //for alarm()
//END_GLOBAL_VARIABLES

//have these as variable of menu class, public variables
//have them set when the alarm time is set, same function call
uint8_t snoozeAlarmHH = clkMenu.getAlarmHH();
uint8_t snoozeAlarmMM = clkMenu.getAlarmMM();



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
