// Requires only sd card module

#include <Arduino.h>
#include <sdCard.h>
#include <stdio.h>
#include <stdlib.h>

int upperBound = 100; // Upper bound of random values for data

void setup () {
    Serial.begin(9600);

    setupSD(); // sets up the INA sensor
}

void loop () {
  // get random value for voltage, current, and temperature with values ranging from 0 to upperbound
    int voltage = rand() % (upperBound + 1);
    int current = rand() % (upperBound + 1);
    int temperature = rand() % (upperBound + 1);

    // read and log timestamp, current, voltage, and temperature
    storeSD(measureTime(), voltage, current, temperature); 
    delay(10);
}