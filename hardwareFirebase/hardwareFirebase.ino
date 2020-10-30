

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  delay(1000);
  Serial.println("starting");

  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
}
bool oneTime = true;

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){
    Serial.println(Serial.read());
    Serial.println("sending");

    digitalWrite(12, LOW);
    delay(200);
    digitalWrite(12, HIGH);
    
    oneTime = false;
    
  }
}
