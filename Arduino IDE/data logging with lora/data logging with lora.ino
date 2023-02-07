#include <string.h>
#include <SD.h>
#include <SPI.h>
#include <SoftwareSerial.h>

File file;

#define trigPin 6
#define echoPin 7
#define pinCS 10
#define receiveInterval 5000

float duration, distance;
int lastReceive;
int lastTransmission;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {}

  // HR-SR04 pin setup:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // SD card setup:
  if (SD.begin(pinCS)) {
    Serial.println("SD card is ready to use.");
  } else {
    Serial.println("SD card initialization failed.");
    return;
  }

  Serial.println("Initialization completed.");

}

String sendMessage(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0343;

  String sentData;
  String params = "AT+SEND=2,6,";  
  sentData += params;
  sentData += String(distance, 3);
  //Serial.println(sentData);
  

  file = SD.open("data.txt", FILE_WRITE);
  if (file) {
    file.println(distance);
    file.close();
  } else {
    //Serial.println("Error opening data.txt");
  }
  return sentData;
}

int interval = 3000;
bool sent = 0;

void loop() {

  // if (Serial.available()) {
  // //   Serial.println(Serial.readString());
  // // }
  
  // Serial.println(sendMessage());
  lastTransmission = millis();

  String incoming;
  while (millis() < interval + lastTransmission) {
    if (Serial.available()) {
      incoming = Serial.readString();
      Serial.println(incoming);
    }
  }


  // if (!sent) {
  //   Serial.println(sendMessage());
  //   lastTransmission = millis();
  //   sent = 1;
  // }
  // else {
  //   String incoming;
  //   while (millis() < interval + lastTransmission) {
      
  //   }
  // }


}

