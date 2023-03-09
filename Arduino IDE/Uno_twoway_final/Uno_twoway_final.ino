#include <SPI.h>
#include <LoRa.h>
const int ledPin = 7;
const int buttonPin = 8;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.setTxPower(20);

}
int starttime;
int endtime;

void loop() {
  starttime = millis();
  endtime = starttime;
  while ((endtime - starttime) <=100) // do this loop for up to 1000mS
  {
    receive();
    endtime = millis();
  }
  send();

  // receive();

  // try to parse packet


}

int counter = 0;
char a;
void send(){
  // Serial.print("Sending packet: ");
  // Serial.println(counter);

  // send packet
  if(Serial.available()){
    a = Serial.read();
    if(a=='1'){
    LoRa.beginPacket();
    LoRa.print(1);
    // LoRa.print(counter);
    LoRa.endPacket();
    }
    else if(a=='0'){
      LoRa.beginPacket();
      LoRa.print(0);
      // LoRa.print(counter);
      LoRa.endPacket();
    }

  }

  // if(digitalRead(buttonPin)){
  //   LoRa.beginPacket();
  //   LoRa.print(1);
  //   // LoRa.print(counter);
  //   LoRa.endPacket();
  // }
  // else{
  //   LoRa.beginPacket();
  //   LoRa.print(0);
  //   // LoRa.print(counter);
  //   LoRa.endPacket();
  // }

}
char c;
void receive(){
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    // Serial.print("Received packet '");
    // read packet
    while (LoRa.available()) {
      c = LoRa.read();
      if(c=='1'){
        Serial.println('1');
        digitalWrite(ledPin, HIGH);

      }
      else if (c=='0'){
        Serial.println('0');
        digitalWrite(ledPin, LOW);
      }
      // Serial.print(c);
    }

    // print RSSI of packet
    // Serial.print("' with RSSI ");
    // Serial.println(LoRa.packetRssi());

  }
}