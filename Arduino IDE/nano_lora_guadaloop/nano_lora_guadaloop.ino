#include <string.h>

unsigned long lastTransmission;
const int interval = 1000;

String incomingString;
int wait = 1;

// The address of the LoRa connected to the nano is 1
void setup() {
  
  Serial.begin(115200);
  lastTransmission = 0;
}


void loop() {
  // if(Serial.available()){
  //     String s = Serial.readString();
  //     Serial.println(s);
  // }


  delay(500);
  Serial.println("AT+SEND=1,2,Hi");
  // lastTransmission = millis();
  // while(millis() < interval + lastTransmission){
  //   if(Serial.available()){
  //     String s = Serial.readString();
  //     Serial.println(s);

      






  //     if(s.substring(0,6).equals("+ERR=2")){
      
  //     }
  //     else{
        
  //       // String out = "";
  //       // String convert = s.substring(9,15);
  //       // double temp = convert.toDouble();
  //       // String str = "AT+SEND=2,6,";
  //       // out += str;
  //       // out += ;

  //       // char con[] = {s.charAt(9),s.charAt(10),s.charAt(11),s.charAt(12),s.charAt(13),s.charAt(14), '\0' };
  //       // char str[] ={'A' , 'T' , '+' , 'S' , 'E' , 'N' , 'D' , '=' , '2' , ',' , '6' , ',', s.charAt(9),s.charAt(10),s.charAt(11),s.charAt(12),s.charAt(13),s.charAt(14), '\0' };
  //       // strcat(str, con);
  //       // sprintf(str, "%f", temp);
        
  //       Serial.println(s);
  //       // String str = "AT+SEND=2,6,";
  //       // str = str + s.substring(9,15);
  //       // Serial.println(str);
        
  //     }
      
  //   }

  // }



  // if(wait =1){
  //   if(Serial.available()){
  //     String s = Serial.readString();
  //     if(s.substring(0,6).equals("+ERR=2")){
      
  //     }
  //     else{
  //       Serial.println(s);
  //       wait = 0;
  //     }
      
  //   }
  // }
  // else{
  //   if (millis() >= interval + lastTransmission) {
  //     Serial.println("AT+SEND=2,2,Hi");
  //     lastTransmission = millis();
  //     wait = 1;
  //   }


  // }



  

}
