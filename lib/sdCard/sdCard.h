#pragma once

// The two functions I created in my BMP280 library
void setupSD(); // Used in setup, deployed once
void storeSD (float time, float volt, float current, float temp); // Stores data in the sd card