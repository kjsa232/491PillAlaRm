int i=0;
int run=1;
void setup() {
  pinMode(9, OUTPUT);
}

void loop() {
  for(i=500;i<700;i++){
  tone(9,i);
  delay(15);

  }
  for(i=700;i>500;i--){
  tone(9,i);
  delay(15);
  }

  exit(0);

  }
