#include <SPI.h>
#include <LoRa.h>
const int ledPin = 7;
const int buttonPin = 8;
int buttonState = 0;

int counter = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(115200);
  while (!Serial)
    ;
  // Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    // Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }

  LoRa.setTxPower(20);
}

int starttime;
int endtime;
void loop() {
  receive();
  // delay(50);
}

void send(String s) {
  LoRa.beginPacket();
  LoRa.print(s);
  LoRa.endPacket();
  // Serial.println("Sending packet: " + s);
}

String message = "";
String c = "";

void receive() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    message = LoRa.readString();
    delay(10);
    if (message == "SEND") {
      if(Serial.available()){
        c = Serial.readString();
        if(c.substring(0,1).equals("1")){
          send("1");
        }
        else if(c.substring(0,1).equals("0")){
          send("0");
        }
        else{
          send("2");
        }
      }
      else{
        send("2");
      }
      // buttonState = digitalRead(buttonPin);
      // if (buttonState == HIGH) {
      //   send("1");             
      // } else {
      //   send("0");
      // }
      // send(String(counter));
      // counter = counter + 1;
    } else {
      Serial.println(message.substring(0));
      send(message.substring(0,3));
    }
  }
}
