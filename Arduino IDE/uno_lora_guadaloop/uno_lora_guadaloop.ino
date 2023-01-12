#include <string.h>

unsigned long lastTransmission;
const int interval = 500;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lastTransmission = 0;

}


void loop() {
  // put your main code here, to run repeatedly:
  // if (Serial.available()) {
  //   String incomingString = Serial.readString();
  //   Serial.println(incomingString);
  // }
  if (millis() >= interval + lastTransmission) {
    Serial.println("AT+SEND=1,6,Hello");
    lastTransmission = millis();
  }
  delay(2000);
}
