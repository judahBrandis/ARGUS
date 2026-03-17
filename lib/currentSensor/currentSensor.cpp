#include <Arduino.h> 
#include <Wire.h>
#include <Adafruit_INA219.h>

int in;

Adafruit_INA219 ina219;

void measureCurrentSetup () {
    Serial.begin(115200);
    for (in = 0; in++; Serial) delay(1);
    // will pause Zero, Leonardo, etc until serial console opens
}

float measureCurrent () {
    float current_mA = 0;
    current_mA = ina219.getCurrent_mA();
    Serial.print("Current: "); Serial.print(current_mA); Serial.println(" mA");
    
    return current_mA; // Current is measured in mA
}

float measureVoltageINA () {
    float shuntvoltage = 0;
    float busvoltage = 0;
    float loadvoltage = 0;

    shuntvoltage = ina219.getShuntVoltage_mV();
    busvoltage = ina219.getBusVoltage_V();
    loadvoltage = busvoltage + (shuntvoltage / 1000);

    Serial.print("Bus Voltage: "); Serial.print(busvoltage); Serial.println(" V");
    Serial.print("Shunt Voltage: "); Serial.print(shuntvoltage); Serial.println(" mV");
    Serial.print("Load Voltage: "); Serial.print(loadvoltage); Serial.println(" V");

    return busvoltage; // Voltage is measured in V
}

float calculatePower(float volt, float current) {
    float power = volt*current; // P = IV
    Serial.print("Power: "); Serial.print(power); Serial.println(" mW");

    return power; // power is measured in mW
}