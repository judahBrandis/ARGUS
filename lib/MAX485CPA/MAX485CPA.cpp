#include <Arduino.h>
#include <ArduinoRS485.h>
#include <sdFat.h>

const int txPin = D1;
const int dePin = A0;
const int rePin = -1;       // Tells code that rePin and dePin are tied together

void setupRS485 (int BAUD_RATE) {
    RS485.begin(BAUD_RATE);

    RS485.setPins(txPin, dePin, rePin);
}

// Send one line from the CSV file via RS485
void transmitData (File &csvFile) {
    String line;

    csvFile.rewind(); // Brings 'cursor' back to beginning of csv file

    while (csvFile.available() == 1) {          // Send data line by line until there's no data left to send
        line = csvFile.readStringUntil('\n');   // Read line and then move 'cursor' down to next line

        // Send line from csv file
        RS485.beginTransmission();
        RS485.println(line);                    // Uses println instead of print so that when sending data it sends in neat rows
        RS485.endTransmission();
    }
}