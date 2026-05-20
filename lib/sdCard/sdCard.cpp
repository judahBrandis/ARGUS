#include <Arduino.h>
#include <SdFat.h>

#define FILE_NAME "ARGUS_Data.csv" // Change to whatever file name and type you want

const int chipSelect = D10; // Change to whatever pin your chip select for SPI is 

SdFat sd;
SdFile myFile;

// Setup sd card - should be run in setup in main file
void setupSD () {
    Serial.begin(9600);
    while (!Serial) {}  // wait for Leonardo
    
    // Initialize SdFat or print a detailed error message and halt
    // Use half speed like the native library.
    // change to SPI_FULL_SPEED for more performance.
    if (!sd.begin(chipSelect, SPI_HALF_SPEED)) sd.initErrorHalt();

    if (!sd.exists(FILE_NAME)) {
        myFile.open(FILE_NAME, O_WRITE | O_CREAT | O_APPEND);
        myFile.println("Time (s), Voltage (V),Current (mA),Temperature (C)");
        myFile.close();
    }
}

// Log data in sd card
void storeSD (uint32_t time, float volt, float current, float temp) {
    myFile.open(FILE_NAME, O_WRITE | O_CREAT | O_APPEND); // Reopens the sd card to be used before closing again

    // Store voltage, current, and temperature into 3 seperate columns 
    // [voltage] | [current] | [temperature]
    myFile.print(time, 2); // The 2 is for 2 decimal places 
    myFile.print(","); // New column
    myFile.print(volt, 2);
    myFile.print(",");
    myFile.print(current, 2);
    myFile.print(",");
    myFile.println(temp, 2);

    myFile.close(); // Ensures all data reaches sd card and closes it to avoid corruption
}

// Measure total elapsed time that ARGUS has been running in seconds
uint32_t measureTime () {
    return millis() / 1000; 
}

// Makes file available in main file where it can be used in other libraries
File getFile() {
    return sd.open(FILE_NAME, O_READ);
}