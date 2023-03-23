#include <SPI.h>
#include <LoRa.h>
const int ledPin = 7;
const int buttonPin = 8;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("LoRa Receiver");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }

  LoRa.setTxPower(20);
}
int starttime;
int endtime;
int counter = 0;
int num = -1;
bool nano = true;

void loop() {
  if (nano) {
    sendString();
  } else {
    send(counter);
  }
  delay(10);

  starttime = millis();
  endtime = starttime;
  while ((endtime - starttime) <= 100)  // do this loop for up to 1000mS
  {
    if (receive()) {
      break;
    }
    endtime = millis();
  }
  if (num == counter) {
    counter = counter + 1;
    if (counter % 5 == 0) {
      nano = true;
    } else {
      nano = false;
    }
  }
  // delay(50);
  // counter = counter + 1;

  // delay(50);


  // receive();

  // try to parse packet
}


void send(int s) {

  LoRa.beginPacket();
  // LoRa.print(1);
  LoRa.print(s);
  LoRa.endPacket();
  Serial.print("Sending packet: ");
  Serial.println(counter);
}

void sendString() {

  LoRa.beginPacket();
  // LoRa.print(1);
  LoRa.print("SEND");
  LoRa.endPacket();
  Serial.println("Sending packet: SEND");
}


String message = "";

bool receive() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    message = LoRa.readString();
    Serial.println("Confirmation " + message);
    if (nano) {
      num = counter;
    } else {
      num = message.toInt();
    }
    return true;
  }
  return false;
}
