#pragma once

#include <arduino.h>

// The two functions I created in my ZMPT101Bj library
void measureVoltageSetup(uint8_t voltagePin); // Used in setup, deployed once
float measureVoltage(uint8_t voltagePin, float voltageTune); // Stores the voltage and displays in seriole output