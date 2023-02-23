/*  Uno Side Code
* 
 Module SX1278 // Arduino Uno  
   Vcc (Red)      ->   3.3V
   MISO (Brown)   ->   D12
   MOSI (Green)   ->   D11     
   SLCK (Yellow)  ->   D13
   Nss (Orange)   ->   D10
   GND (Black)    ->   GND
*/

#include <SPI.h>
#include <LoRa.h>  

#define buttonPin 8
#define ledPin 9

String outgoing;

byte msgCount = 0;
byte localAddress = 0xBB;
byte destination = 0xFF;
long lastSendTime = 0;
int interval = 50;

int message;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  if (!LoRa.begin(915E6)) {
    Serial.println("LoRa Init Failed");
    while (true);
  }

}

void loop() {
  if (millis() - lastSendTime > interval) {
    if (digitalRead(buttonPin) == HIGH) {
      message = 1;
      sendMessage(message);
    }
 
    if (digitalRead(buttonPin) == LOW) {
      message = 0; 
      sendMessage(message);
    }
 
    //Serial.println("Sending " + message);
    lastSendTime = millis();            // timestamp the message
    interval = random(50) + 100;  
  }
 
  // parse for a packet, and call onReceive with the result:
  onReceive(LoRa.parsePacket());
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return
 
  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length
 
  String incoming = "";
 
  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  // check length for error
  if (incomingLength != incoming.length()) {   
   Serial.println("error: message length does not match length");
   return;                             
  }
 
  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xFF) {
    Serial.println("This message is not for me.");
    return;                             
  }

  Serial.println(incoming);
  Serial.println();
}
