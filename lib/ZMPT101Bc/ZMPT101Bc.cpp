#include <Arduino.h>
#include <ZMPT101Bc.h>

float getSensitivity (ZMPT101B& voltageSensor, float ACTUAL_VOLTAGE) { // Stores the sensitivity value as a floating point integer 
    const float START_VALUE = 0; // Initial sensitivity
    const float STOP_VALUE = 1000; // Max sensitivity limit
    const float STEP_VALUE = 0.25; // Increment step for calibration
    const float TOLLERANCE = 1; // Acceptable voltage deviation

    float MAX_TOLLERANCE_VOLTAGE = ACTUAL_VOLTAGE + TOLLERANCE; // Upper tolerance limit
    float MIN_TOLLERANCE_VOLTAGE = ACTUAL_VOLTAGE - TOLLERANCE; // Lower tolerance limit

  float senstivityValue = START_VALUE;
  voltageSensor.setSensitivity(senstivityValue);
  float voltageNow = voltageSensor.getRmsVoltage();

  Serial.println("Starting sensitivity calculations");

  // Adjust sensitivity until voltage is within tolerance
  while (voltageNow > MAX_TOLLERANCE_VOLTAGE || voltageNow < MIN_TOLLERANCE_VOLTAGE) {
    if (senstivityValue < STOP_VALUE) {
      senstivityValue += STEP_VALUE;
      voltageSensor.setSensitivity(senstivityValue);
      voltageNow = voltageSensor.getRmsVoltage();
      
      Serial.print(senstivityValue);
      Serial.print(" => ");
      Serial.println(voltageNow);
    } else {
      Serial.println("Unfortunately, the sensitivity value cannot be determined");
      return 0.0; // Stop if sensitivity reaches limit
    }
  }

  Serial.print("Closest voltage within tolerance: ");
  Serial.println(voltageNow);
  Serial.print("Sensitivity Value: ");
  Serial.println(senstivityValue, 10);

  return senstivityValue; 
}