#include <Arduino.h>
#include <BMP280.h>

const float param = 30; // In degrees C

void setup() {
  Serial.begin(9600);

  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);

  measureTemperatureSetup(); // sets up the temperature measuring function
}

void loop() {
  readTemperature(); // Saves variable and displays temperature

  if (readTemperature() > param) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
  } // turns blue LED on and red off
  else {
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
  } // turns red LED on and blue off
}