#include <Arduino.h>
#include <INA219j.h>

void setup () {
    Serial.begin(9600);

    setupINA(); // sets up the INA sensor
}

void loop () {
    calculatePower(measureVoltage(), measureCurrent()); // Calculates power 
    Serial.println("");

    delay(2000); // Pauses for 1 second before continuing
}