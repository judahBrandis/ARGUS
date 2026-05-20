#include <Arduino.h>
#include <ArduinoRS485.h>
#include <sdFat.h>

const int BAUD_RATE = 9600; // Change to board baud rate

void setupRS485 () {
    RS485.begin(BAUD_RATE);
}

// Send one line from the CSV file via RS485
void transmitData (File &csvFile) {
    String line;

    csvFile.rewind(); // Brings 'cursor' back to beginning of csv file

    while (csvFile.available() == 1) {          // Send data line by line until there's no data left to send
        line = csvFile.readStringUntil('\n');   // Read line and then move 'cursor' down to next line

        // Send line from csv file
        RS485.beginTransmission();
        RS485.print(line);
        RS485.endTransmission();
    }
}