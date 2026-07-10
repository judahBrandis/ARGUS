#pragma once

#include <Arduino.h>
#include <sdFat.h>

void setupRS485(int BAUD_RATE); // Used in setup, deployed once
void transmitData(File &csvFile); // Send all current data