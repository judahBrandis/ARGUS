#pragma once
#include <stdint.h>

// The two functions I created in my BMP280 library
void setupSD(); // Used in setup, deployed once
void storeSD (uint32_t time, float volt, float current, float temp); // Stores data in the sd card
uint32_t measureTime();