#pragma once
#include <stdint.h>
#include <SdFat.h>

// The two functions I created in my BMP280 library
void setupSD(int baud_rate, char *FILE_NAME); // Used in setup, deployed once
void storeSD (char *FILE_NAME, float time, float volt, float current, float temp); // Stores data in the sd card
float measureTime(); // Measure total elapsed time that ARGUS has been running in seconds
File getFile(char *FILE_NAME); // Makes file available in main file where it can be used in other libraries