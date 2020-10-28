#include <Wire.h>
#include <Keypad.h>

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
uint8_t speakerTripped = 0; //Lets there be sound
uint8_t ledTripped = 0;     //Lets there be light

uint8_t counter = 0;
uint8_t aState;
uint8_t aLastState;
uint8_t angle = 0;

//PINS
uint8_t speaker = 53;
uint8_t led = 52;
uint8_t motor = 51;

uint8_t run = 1; // what does this thing here do?


//functions
void speakerBoom();
void ledIlluminate(uint8_t trip);
void rotatePills();
bool cupDetected)();

void setup()
{
pinMode(speaker, OUTPUT);
pinMode(led, OUTPUT);

//Motor Control
myservo.attach(motor); //previously 9 check PINS above for current
pinMode (outputA,INPUT);
pinMode (outputB,INPUT);

Serial.begin (9600);
lcd.begin(16,2);
// Reads the initial state of the outputA
aLastState = digitalRead(outputA);
}



void loop()
{
  customKey = customKeypad.getKey();
  switch(customKey)
  {
  case '1': speakerTripped = 1; cusomKey = 'z'; break;
  case '2': speakerTripped = 0; cusomKey = 'z'; break;
  case '3': ledTripped = 0; cusomKey = 'z'; break;
  case '4': ledTripped = 1; cusomKey = 'z'; break;
  case '5': rotatePills(); cusomKey = 'z'; break;
  }

  if(speakerTripped == 1){speakerBoom();}
  ledIlluminate(ledTripped);

  if(cupDetected()){digitalWrite(led,HIGH);}
  else{digitalWrite(led,LOW);}
}

//////////////////////////////////////////////////////////////////////////////////////
//Functions

void speakerBoom()
{
// Let there be sound
for(uint8_t i=500;i<700;i++)  {  tone(speaker,i);  delay(15);  }
for(uint8_t i=700;i>500;i--)  {  tone(speaker,i);  delay(15);  }
// and there was sound
}

void ledIlluminate(uint8_t trip)
{
// Let there be light
if(trip == 1){digitalWrite(led,HIGH);}
// there was light
else         {digitalWrite(led,LOW);}
}

void rotatePills()
{
aState = digitalRead(outputA); // Reads the "current" state of the outputA
// If the previous and the current state of the outputA are different, that means a Pulse has occured
myservo.write(90);
if (aState != aLastState)
  {
  // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
  if (digitalRead(outputB) != aState)   {  counter ++;  }
  else                                  {  counter --;  }
  Serial.print("Position: ");  Serial.println(counter);
  angle = counter;

  }
if(angle > 3)
  {
  myservo.write(92);
  delay(10);
  exit(0);
  }
aLastState = aState; // Updates the previous state of the outputA with the current state
}

bool cupDetected)()
{
  bool isThere = false;
  //check for cupDetected

  return isThere;
}
