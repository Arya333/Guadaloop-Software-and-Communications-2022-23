/*  Receiver Side Code
* 
 Module SX1278 // Arduino Nano  
   Vcc         ->   3.3V
   MISO        ->   D12
   MOSI        ->   D11     
   SLCK        ->   D13
   Nss         ->   D10
   GND         ->   GND
*/

#include <SPI.h>
#include <LoRa.h>  

String inString = "";    // string to hold incoming charaters
String message = ""; // Holds the complete message

void setup() {
  Serial.begin(9600);
 
  while (!Serial);
  Serial.println("LoRa Receiver");
  if (!LoRa.begin(915E6)) { 
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) { 
    // read packet    
    while (LoRa.available())
    {
      int inChar = LoRa.read();
      inString += (char)inChar;
      message = inString;       
    }
    inString = "";     
    LoRa.packetRssi();    
  }
      
  Serial.println(message);  
  
}
