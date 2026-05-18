#include <Arduino.h>
#include <SdFat.h>

#define FILE_NAME "ARGUS_Data.csv"

const int chipSelect = D10; // Change to whatever pin your chip select for SPI is 

SdFat sd;
SdFile myFile;

void setupSD () {
    Serial.begin(9600);
    while (!Serial) {}  // wait for Leonardo
    
    // Initialize SdFat or print a detailed error message and halt
    // Use half speed like the native library.
    // change to SPI_FULL_SPEED for more performance.
    if (!sd.begin(chipSelect, SPI_HALF_SPEED)) sd.initErrorHalt();

    if (!sd.exists(FILE_NAME)) {
        myFile.open(FILE_NAME, O_WRITE | O_CREAT | O_APPEND);
        myFile.println("Time (), Voltage (V),Current (I),Temperature (C)");
        myFile.close();
    }
}

void storeSD (float time, float volt, float current, float temp) {
    myFile.open(FILE_NAME, O_WRITE | O_CREAT | O_APPEND); // Reopens the sd card to be used before closing again

    // Store voltage, current, and temperature into 3 seperate columns 
    // [voltage] | [current] | [temperature]
    myFile.print(time, 2);
    myFile.print(",");
    myFile.print(volt, 2);
    myFile.print(",");
    myFile.print(current, 2);
    myFile.print(",");
    myFile.println(temp, 2);

    myFile.close(); // Ensures all data reaches sd card and closes it to avoid corruption
}