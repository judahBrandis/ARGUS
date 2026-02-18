#include <Arduino.h>
#include <BMP280.h>

void setup() {
  Serial.begin(9600);

  measureTemperatureSetup(); // sets up the temperature measuring function
}

void loop() {
  readTemperature(); // Saves variable and displays temperature
}