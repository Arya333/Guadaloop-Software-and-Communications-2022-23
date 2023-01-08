#include <string.h>


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  

}


void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    String incomingString = Serial.readString();
    Serial.println(incomingString);
  }
  delay(2000);
}
