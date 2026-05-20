#pragma once
#include <stdint.h>
#include <SdFat.h>

// The two functions I created in my BMP280 library
void setupSD(); // Used in setup, deployed once
void storeSD (uint32_t time, float volt, float current, float temp); // Stores data in the sd card
uint32_t measureTime(); // Measure total elapsed time that ARGUS has been running in seconds
File getFile(); // Makes file available in main file where it can be used in other libraries