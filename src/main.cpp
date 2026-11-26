#include <Arduino.h>

#include "sdCard.h" // I'm concerned by this library's use of Serial.begin
#include "ModBusj.h"
#include "INA219j.h"
#include "BMP280.h"

// measurement types: time, DC voltage, DC current, AC voltage, AC current, temperature
const int MEASURMENT_TYPES = 6; 
// registers for ModBus communication initially set to zero
// each index of the array is a different data measurement 
uint16_t myRegisters[MEASURMENT_TYPES] = {0}; 

char *FILE_NAME = "Net485_Data.csv"; // Change to whatever file name and type you want

void setup () {
    // slave id is the id of this Node485 module used in ModBus commmunication
    // will in the future likely use physical switches to change the id number
    int mySlaveID = 1;

    // set up baud rate of board
    int baud_rate = 9600;
    Serial.begin(baud_rate);

    // setup sensors, the sd card reader, and ModBus
    setupBMP280(); // BMP280 Sensor - temperature measuring function
    setupINA(); // INA sensor - voltage and current measuring functions
    setupSD(baud_rate, FILE_NAME); // micro sd card reader
    setupModBus(mySlaveID, baud_rate, myRegisters, MEASURMENT_TYPES); // MAX485CPA+ RS485 - sets up data transmission with master computer via ModBus
}

int lastTimeStored = 0;

void loop () {
    // measure data and store to temporary variables
    float timeMeasure = measureTime();
    float voltageMeasure = measureVoltage();
    float currentMeasure = measureCurrent();
    float tempMeasure = measureTemperature();

    // store data in ModBus registers
    // if master computer requests data, data from these registers will be sent
    updateRegisters(myRegisters, timeMeasure, tempMeasure, voltageMeasure, currentMeasure, 0.0, 0.0);

    // send data from the ModBus registers if the master computer desires it
    // Store data in CSV file if data is sent so that data in master computer can be compared to data in Node485 module
    if (sendData())
        storeSD(FILE_NAME, timeMeasure, voltageMeasure, currentMeasure, tempMeasure); 
    
    // store data in the CSV file every set time interval, independent of the master computer
    const int storeInterval = 60; // 60 seconds, 1 minute

    // check if time since last time data was stored was greater than or equal to set time interval
    if (timeMeasure - lastTimeStored >= storeInterval) {
        // store data
        storeSD(FILE_NAME, timeMeasure, voltageMeasure, currentMeasure, tempMeasure); 

        // update when the last time data was stored
        lastTimeStored = (int)timeMeasure;
    }
}