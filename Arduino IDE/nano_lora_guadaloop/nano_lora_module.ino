#include <string.h>

// The address of the LoRa connected to the nano is 1
void setup() {
  Serial.begin(115200);
  //Serial.begin(9600);
}


void loop() {

/* Working Code */
  String s;
  s = Serial.readString();
  Serial.print(s);
  delay(100);
  Serial.println("AT+SEND=0,4,Hi\r\n");
  delay(100);




  

  
  // lastTransmission = millis();
  // while(millis() < interval + lastTransmission){
  //   if(Serial.available()){
  //     String s = Serial.readString();
  //     Serial.println(s);  

}
