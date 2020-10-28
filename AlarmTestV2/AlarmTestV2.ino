#include <Wire.h>
#include <Keypad.h>

#include <Arduino.h>

//new includes
#include <Servo.h>

#define outputA 49
#define outputB 50

Servo myservo;

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

// ALARM GLOBALS
bool speakerTripped = 0; //Lets there be sound
bool ledTripped = 0;     //Lets there be light
bool rotateTripped = 0;
uint16_t speakerSound = 500;

int16_t counter = 0;
int16_t aState;
int16_t aLastState;
int16_t angle = 0;

//PINS
uint8_t speaker = 53;
uint8_t led = 52;
uint8_t motor = 51;

uint8_t run = 1; // what does this thing here do?


//functions
void speakerBoom();
void ledIlluminate(uint8_t trip);
void rotatePills();
bool cupDetected();

void setup()
{
pinMode(speaker, OUTPUT);
pinMode(led, OUTPUT);

//Motor Control
myservo.attach(motor); //previously 9 check PINS above for current
pinMode (outputA,INPUT);
pinMode (outputB,INPUT);
// Reads the initial state of the outputA
aLastState = digitalRead(outputA);
}

void loop()
{
  customKey = customKeypad.getKey();
  switch(customKey)
  {
  case '1': speakerTripped = true; customKey = 'z'; break;
  case '2': speakerTripped = false; customKey = 'z'; break;
  case '3': ledTripped = true; customKey = 'z'; break;
  case '4': ledTripped = false; customKey = 'z'; break;
  case '5': rotateTripped = true; customKey = 'z'; break;
  }
  
  speakerBoom(speakerTripped);
  ledIlluminate(ledTripped);
  if(rotateTripped){rotatePills();rotateTripped = false;}
  //delay(300);
  //if(cupDetected()){digitalWrite(led,HIGH);}
  //else{digitalWrite(led,LOW);}
}

//////////////////////////////////////////////////////////////////////////////////////
//Functions

void speakerBoom(bool trip)
{
  if(trip){  tone(speaker,speakerSound); delay(15); speakerSound++; if(speakerSound >= 700){speakerSound = 500;}  }
  else    { noTone(speaker); speakerSound = 500;}

}

void ledIlluminate(bool flag)
{
if(flag){digitalWrite(led,HIGH);}
else    {digitalWrite(led,LOW);}
}

void rotatePills()
{
aState = digitalRead(outputA); // Reads the "current" state of the outputA
// If the previous and the current state of the outputA are different, that means a Pulse has occured
myservo.write(90);
if (aState != aLastState)
  {
  // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
  if (digitalRead(outputB) != aState)   {  counter++;  }
  else                                  {  counter--;  }
  angle = counter;
  }
  
if(angle > 3)
  {
  myservo.write(92);
  delay(10);
  }
aLastState = aState; // Updates the previous state of the outputA with the current state
}

bool cupDetected()
{
  bool isThere = false;
  //check for cupDetected

  return isThere;
}
