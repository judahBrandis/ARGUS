#include <Arduino.h>
#include <BMP280.h>

void setup() {
  Serial.begin(9600);

  measureTemperatureSetup(); // sets up the temperature measuring function
}

void loop() {
  readTemperature(); // Function stores temperature variable to be used as needed and internally prints temperature value
  delay(1000);
}