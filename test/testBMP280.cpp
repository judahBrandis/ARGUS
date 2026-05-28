// Requires only BMP280 module wired

#include <Arduino.h>
#include <BMP280.h>

void setup() {
  Serial.begin(9600);

  setupBMP280(); // sets up the temperature measuring function
}

void loop() {
  measureTemperature(); // Function stores temperature variable to be used as needed and internally prints temperature value
  delay(1000); // Pauses for 1 second before printing temperature again
}