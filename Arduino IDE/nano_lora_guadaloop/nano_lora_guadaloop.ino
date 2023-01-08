#include <string.h>

unsigned long lastTransmission;
const int interval = 2000;

String incomingString;

// The address of the LoRa connected to the nano is 1
void setup() {
  
  Serial.begin(115200);
  lastTransmission = 0;
}


void loop() {
  
  if (millis() >= interval + lastTransmission) {
    Serial.println("AT+SEND=2,2,Hi");
    lastTransmission = millis();
  }
}
