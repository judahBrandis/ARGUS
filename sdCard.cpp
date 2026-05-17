#include <Arduino.h>
#include <SdFat.h>

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

    if (!sd.exists("test.csv")) {
        myFile.open("test.csv", O_WRITE | O_CREAT);
        myFile.println("Time (), Voltage (V),Current (I),Temperature (C)");
        myFile.close();
    }
}

void storeSD (float time, float volt, float current, float temp) {
    // Store voltage, current, and temperature into 3 seperate columns 
    // [voltage] | [current] | [temperature]
    myFile.print(volt, 2);
    myFile.print(",");
    myFile.print(current, 2);
    myFile.print(",");
    myFile.println(temp, 2);

    myFile.flush(); // Ensures all data reaches sd card while keeping it open
}