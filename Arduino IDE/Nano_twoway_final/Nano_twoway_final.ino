#include <SPI.h>
#include <LoRa.h>
const int ledPin = 7;
const int buttonPin = 8;

int counter = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(9600);
  while (!Serial)
    ;
  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
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
  Serial.println("Sending packet: " + s);
}

String message = "";

void receive() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    message = LoRa.readString();
    Serial.println(message);
    delay(10);
    if (message == "SEND") {
      send(String(counter));
      counter = counter + 1;
    } else {
      send(message);
    }
  }
}
