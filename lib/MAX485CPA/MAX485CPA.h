#pragma once

#include <Arduino.h>
#include <sdFat.h>

void setupRS485(); // Used in setup, deployed once
void transmitData(File &csvFile); // Send all current data