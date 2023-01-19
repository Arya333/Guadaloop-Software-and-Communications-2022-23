#include <SD.h>
#include <SPI.h>

File file;

#define trigPin 6
#define echoPin 7
#define pinCS 10

float duration, distance;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {}

  // HR-SR04 pin setup:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // SD card setup:
  if (SD.begin(pinCS)) {
    Serial.println("SD card is ready to use.");
  } else {
    Serial.println("SD card initialization failed.");
    return;
  }

  Serial.println("Initialization completed.");
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0343;

  Serial.print("Distance: ");
  if (distance >= 400 || distance <= 2) {
    Serial.println("Out of Range");
  } else {
    Serial.println(distance);
  }

  file = SD.open("data.txt", FILE_WRITE);
  if (file) {
    file.println(distance);
    file.close();
  } else {
    Serial.println("Error opening data.txt");
  }
  //delay(500);
}
