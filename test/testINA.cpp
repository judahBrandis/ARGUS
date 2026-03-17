#include <Arduino.h>
#include <currentSensor.h>

void setup () {
    Serial.begin(9600);

    measureCurrentSetup(); // sets up the INA sensor
}

void loop () {
    measureVoltageINA(); // measures voltage from the INA sensor
    measureCurrent(); // measures current from the INA sensor
    calculatePower(measureCurrent(), measureVoltageINA()); // Calculates power 

    delay(1000); // Pauses for 1 second before continuing
}