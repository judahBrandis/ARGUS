#include <Arduino.h>
#include <ZMPT101Bj.h>

void setup() {
  Serial.begin(9600);

  measureVoltageSetup(); // sets up the temperature measuring function
}

void loop() {
  measureVoltage(); // Function stores temperature variable to be used as needed and internally prints temperature value
  delay(1000); // Pauses for 1 second before printing temperature again
}