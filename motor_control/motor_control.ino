#include <Servo.h>
Servo myservo;
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#define outputA 6
#define outputB 7
 
int counter = 0;
int aState;
int aLastState;
int angle = 0;

void setup() {
myservo.attach(9);
pinMode (outputA,INPUT);
pinMode (outputB,INPUT);
 
Serial.begin (9600);
lcd.begin(16,2);
// Reads the initial state of the outputA
aLastState = digitalRead(outputA);
 
}
 
void loop() {
aState = digitalRead(outputA); // Reads the "current" state of the outputA
// If the previous and the current state of the outputA are different, that means a Pulse has occured
myservo.write(90);
if (aState != aLastState){
// If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
if (digitalRead(outputB) != aState) {
counter ++;
lcd.clear();
} else {
counter --;
lcd.clear();
}
Serial.print("Position: ");
Serial.println(counter);
lcd.setCursor(0, 0);
lcd.print("Position: ");
lcd.setCursor(10, 0);
lcd.print(counter);
angle=counter;


 
}
if(angle > 3){
  myservo.write(92);
  delay(10);
  exit(0);
}

aLastState = aState; // Updates the previous state of the outputA with the current state
 
}
