#include <SPI.h>
#include <LoRa.h>
const int ledPin = 7;
const int buttonPin = 8;

int count =10;

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
    if(counter==1000){
      counter = 1;
    }
    if (counter % 5 == 0) {
      nano = true;
    } else {
      nano = false;
    }
  }
}


void send(int s) {

  LoRa.beginPacket();
  int temp = s + 1000;
  String send = String(temp);
  send = send.substring(1,4);
  send = send + createPacket(counter%5);
  LoRa.print(send);
  LoRa.endPacket();
  Serial.print("Sending packet: ");
  Serial.println(send);

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
      if(message.equals("1")){
        digitalWrite(ledPin, HIGH);
      }
      else if(message.equals("0")){
        digitalWrite(ledPin, LOW);
      }
      num = counter;
    } else {
      num = message.toInt();
    }
    return true;
  }
  return false;
}









void updateCount(){
  count++;
  if(count>99){
    count=10;
  }
  return;
}


String createPacket(int identifier){  
  int num = identifier;
  String s = ",";
  s += String(num);
  num -=1;
  num *= 6;
  num +=1;

  for(int i=0;i<6;i++){
    s += ",";
    s += String(num+i);
    s += String(count);
  }
  

  updateCount();
  return s;

}
