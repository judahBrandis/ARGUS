#include <Arduino.h>
#include <SdFat.h>

const int chipSelect = D10; // Change to whatever pin your chip select for SPI is 

SdFat sd;
SdFile myFile;

void setup() {
  Serial.begin(9600);
  while (!Serial) {}  // wait for Leonardo
  Serial.println("Type any character to start");
  while (Serial.read() <= 0) {}
  delay(400);  // catch Due reset problem
  
  // Initialize SdFat or print a detailed error message and halt
  // Use half speed like the native library.
  // change to SPI_FULL_SPEED for more performance.
  if (!sd.begin(chipSelect, SPI_HALF_SPEED)) sd.initErrorHalt();

  // open the file for write at end like the Native SD library
  if (!myFile.open("test.csv", O_RDWR | O_CREAT | O_AT_END)) {
    sd.errorHalt("opening test.txt for write failed");
  }
  // if the file opened okay, write to it:
  Serial.print("Writing to test.csv...");
  myFile.println("testing 1, 2, 3.");

  // close the file:
  myFile.close();
  Serial.println("done.");

  // re-open the file for reading:
  if (!myFile.open("test.csv", O_READ)) {
    sd.errorHalt("opening test.txt for read failed");
  }
  Serial.println("test.csv");

  // read from the file until there's nothing else in it:
  int data;
  while ((data = myFile.read()) >= 0) Serial.write(data);
  // close the file:
  myFile.close();
}

void loop() {
  // nothing happens after setup
}