#include <string.h>
const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPin = 13;    // the number of the LED pin
int buttonState = 0;  // variable for reading the pushbutton status
int count =0;
// The address of the LoRa connected to the nano is 1
void setup() {
  Serial.begin(115200);
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}


void loop() {
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, LOW);
    Serial.println("AT+SEND=0,3,0\r\n");
  } else {
    Serial.println("AT+SEND=0,3,1\r\n");
    // turn LED off:
    digitalWrite(ledPin, HIGH);
  }
  delay(100);





  // count++;
  // // String s;
  // // s = Serial.readString();
  // // Serial.print(s);
  // // delay(100);
  // Serial.println("AT+SEND=0,4,"+ String(count) +"\r\n");
  // delay(900);
  // String s;
  // s = Serial.readString();
  // Serial.print(s);
  // delay(200);



// /* Working Code */
//   String s;

//   while (Serial.available()) {
//     s = Serial.readString();
//     // Serial.println(s);
//   }

//   Serial.println("AT+SEND=0,4,Hi\r\n");
//   delay(900);
//   // s = Serial.readStringUntil('\n');
//   // s = Serial.readString();
//   // Serial.println(s);
//   // Serial.println();
//   while (Serial.available()) {
//     s = Serial.readString();
//     Serial.println(s);
//   }
  
  // // delay(100);
  // // s = Serial.readStringUntil('\n');
  
  // // s = Serial.readStringUntil('\n');
  // s = Serial.readString();
  // Serial.println(s);
  // Serial.println();




  

  
  // lastTransmission = millis();
  // while(millis() < interval + lastTransmission){
  //   if(Serial.available()){
  //     String s = Serial.readString();
  //     Serial.println(s);  

}