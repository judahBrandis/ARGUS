#include <Arduino.h> 
#include <ZMPT101B.h>

// ZMPT101B pin on STM32
#define ZMPpin (A0)

// Define which pin the ZMPB101 sensor is connected to on the STM32
ZMPT101B voltageSensor(ZMPpin);

// Setup the voltage measuring sensor - Everything that goes in setup function in main file
void measureVoltageSetup () {
    // Prints message and waits 0.1 seconds
    Serial.println("Calibrating... Ensure that no current flows through the sensor at this moment");
    delay(100);

    // Calibrates the voltage sensor (ZMPT101B)
    voltageSensor.calibrate();

    // Prints message to show that voltage sensor setup is complete
    Serial.println("Done!");
}

float measureVoltage () {
    // measures and then sets local variable to voltage
    float measuredVolt = voltageSensor.getVoltageAC();

    // Prints and then sets function equal to the voltage
    Serial.print(measuredVolt);
    return measuredVolt;
}