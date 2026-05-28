// Requires sd card module as well as MAX485CPA+ wired 

#include <Arduino.h>
#include <sdCard.h>
#include <stdio.h>
#include <stdlib.h>
#include <MAX485CPA+.h>

int upperBound = 100; // Upper bound of random values for data
bool transmited = false;
float time;

void setup () {
    Serial.begin(9600);

    setupSD(); // sets up the INA sensor
    setupRS485(); // sets up RS485
}

void loop () {
  // get random value for voltage, current, and temperature with values ranging from 0 to upperbound
  int voltage = rand() % (upperBound + 1);
  int current = rand() % (upperBound + 1);
  int temperature = rand() % (upperBound + 1);

  // read and log timestamp, current, voltage, and temperature
  time = measureTime();
  storeSD(time, voltage, current, temperature); 
  delay(10);

  if (time >= 10 && transmited == false) {         // Once Argus has ran for 10 seconds, send all data
    File file = getFile();  // Brings file variable to main for transmitData funtion parameter
    transmitData(file);     // Transmit data to master computer
    file.close();           // Close file so that sd card data doesn't corrupt (can be opened later)
    transmited = true;
  }
}