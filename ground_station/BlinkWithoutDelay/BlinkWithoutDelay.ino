// constants won't change. Used here to set a pin number:
const int ledPin2 = 13;// the number of the LED pin
const int ledPin = 10;
const int buttonPin = 2;
// Variables will change:
int ledState = LOW;             // ledState used to set the LED
int buttonState = 0; 

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
// unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change:
// const long interval = 1000;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(buttonPin, INPUT);
}
char c;
int count =10;
void loop() {
  
  read();
  send();
  // delay(500);

}

void updateCount(){
  count++;
  if(count>99){
    count=10;
  }
  return;
}

int sendCount = 1;

void send(){
  // buttonState = digitalRead(buttonPin);

  // // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  // if (buttonState == HIGH) {
  //   // turn LED on:
  //   Serial.println("Hello World");
  // } else {
  //   // turn LED off:
  //   Serial.println("Goodbye World");
  // }

  Serial.println(createPacket(sendCount));




  sendCount++;
  if(sendCount>3){
    sendCount=1;
  }


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


void read(){
    if(Serial.available()){
    c = Serial.read();
    if(c=='1'){
      ledState = HIGH;
      digitalWrite(ledPin2, LOW);

    }
    else if(c=='0'){
      ledState = LOW;
      digitalWrite(ledPin2, LOW);

    }
    // else{
    //   Serial.println(c);
    // }
    
    digitalWrite(ledPin, ledState);
  }

}
