#include <string.h>
#define ledPin 13
String incomingString;

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);

}
char c;
void loop() {
//  c = Serial.read();
//  if(c=='+'){
//      digitalWrite(ledPin,HIGH);
//      delay(0);
//      digitalWrite(ledPin,LOW);
//      Serial.flush();
//  }



  if(Serial.available()){
    incomingString = Serial.readString();
    char c = incomingString.charAt(9);
    if(c=='0'){
      digitalWrite(ledPin,LOW);
    }
    else if(c=='1'){
      digitalWrite(ledPin,HIGH);
    }
    else{
      digitalWrite(ledPin,HIGH);
      delay(100);
      digitalWrite(ledPin,LOW);
    }

  }
}