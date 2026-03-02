#include <Arduino.h> 

// Setup the voltage measuring sensor - Everything that goes in setup function in main file
void measureVoltageSetup (uint8_t voltagePin) {
    pinMode(voltagePin, INPUT);
}

float measureVoltage (uint8_t voltagePin, float voltageTune) {
    // measures and then sets local variable to voltage
    float measuredVolt = voltageTune*analogRead(voltagePin);

    // Prints and then sets function equal to the voltage
    Serial.print(measuredVolt);
    Serial.println(" V");
    return measuredVolt;
}