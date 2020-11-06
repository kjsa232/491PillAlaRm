
/*
 * Created by K. Suwatchai (Mobizt)
 * 
 * Email: k_suwatchai@hotmail.com
 * 
 * Github: https://github.com/mobizt
 * 
 * Copyright (c) 2020 mobizt
 * 
 * This example is for FirebaseESP8266 Arduino library v 2.8.9 or later
 *
*/

//FirebaseESP8266.h must be included before ESP8266WiFi.h
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#define FIREBASE_HOST "***********" //Without http:// or https:// schemes
#define FIREBASE_AUTH "************"
#define WIFI_SSID "************"
#define WIFI_PASSWORD "************"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

FirebaseJson json;

void printResult(FirebaseData &data);

SoftwareSerial ser(6,7);

void setup()
{

  Serial.begin(115200);

  ser.begin(9600);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  firebaseData.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  firebaseData.setResponseSize(1024);

  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");

  //optional, set the decimal places for float and double data to be stored in database
  Firebase.setFloatDigits(2);
  Firebase.setDoubleDigits(6);

  /*
  This option allows get and delete functions (PUT and DELETE HTTP requests) works for device connected behind the
  Firewall that allows only GET and POST requests.
  
  Firebase.enableClassicRequest(firebaseData, true);
  */

 // String path = "/users";

  Serial.println("-----------------------------------");
  Serial.println("----------Begin Set Test-----------");
  Serial.println("-----------------------------------");
  Serial.println();

  pinMode(D1, INPUT_PULLUP);
}

unsigned long lastSendTime = 0;

void loop()
{
  unsigned long now = millis();
  if( (digitalRead(D1) == LOW) && (now - lastSendTime > 1000)){
      String path = "/users";
      Serial.println("sending");
      Firebase.setBool(firebaseData, path + "/55555/taken", false);
      lastSendTime = millis();
  }
  
}
