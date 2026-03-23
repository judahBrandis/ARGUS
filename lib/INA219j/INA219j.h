#pragma once

#include <arduino.h>

// The three functions I created in my INA sensor library
void setupINA(); // Used in setup, deployed once
float measureVoltage(); // Stores the voltage and displays in seriole output
float measureCurrent(); // Stores the current and displays in seriole output
float calculatePower(float volt, float current); // Calculates, stores, & displays power