#include <Arduino.h>
#include <sdCard.h>
#include <INA219j.h>
#include <BMP280.h>
#include <MAX485CPA+.h>
#include <sdFat.h>

const int DELAY_TIME = 1000; // delay (in miliseconds) between measurements are taken

bool sendData = false;
int desiredLine;

void setup () {
    Serial.begin(9600);

    setupBMP280(); // sets up the temperature measuring function
    setupINA(); // sets up the INA sensor
    setupSD(); // sets up the INA sensor
    setupRS485(); // sets up RS485
}

void loop () {
    // read and log timestamp, current, voltage, and temperature
    storeSD(measureTime(), measureVoltage(), measureCurrent(), measureTemperature()); 
    delay(DELAY_TIME);

    // Send requested line 
    if (sendData == true) {
        File file = getFile();
        transmitData(file);
        file.close();
    }
}