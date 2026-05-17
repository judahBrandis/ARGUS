#include <Arduino.h>
#include <sdCard.h>
#include <INA219j.h>
#include <BMP280.h>

#define measureTime (1) // until I can measure time accurately

void setup () {
    Serial.begin(9600);

    measureTemperatureSetup(); // sets up the temperature measuring function
    setupINA(); // sets up the INA sensor
    setupSD(); // sets up the INA sensor
}

void loop () {
    // read and log timestamp, current, voltage, and temperature
    storeSD(measureTime, measureVoltage(), measureCurrent(), readTemperature()); 
    delay(1000);
}