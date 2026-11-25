#include "ModBusj.h"
#include <ModbusRTUSlave.h>

const int dePin = A0;
// const int dePin = D2;
// const int tePin = D8;
ModbusRTUSlave node485(Serial1, dePin); // create a modbus object, Serial1 is the first serial port available. Will be dedicated to modbus coms

// set up the ModBus
void setupModBus(int ModBusID, int baud_rate, uint16_t inputRegisters[], int numInputRegisters) {
    // configure the modbus object to use the specified registers
    node485.configureInputRegisters(inputRegisters, numInputRegisters);
  
    // set the baud rate of the dedicated modbus serial port (Serial1) and ensure no parity is used
    Serial1.begin(baud_rate, SERIAL_8N1);

    // set the ModBus slave's ID number, the baud rate, and ensure no parity is used
    node485.begin(ModBusID, baud_rate, SERIAL_8N1);
}

// update the registers (array) that will be sent via ModBus when master computer desires data
void updateRegisters(uint16_t modRegister[], float time, float temp, float DCvolt, float DCcurrent, float ACvolt, float ACcurrent) {
    enum {
        TIME        = 0,
        TEMPERATURE = 1,
        DC_VOLTAGE  = 2,
        DC_CURRENT  = 3,
        AC_VOLTAGE  = 4,
        AC_CURRENT  = 5
    };

    // registers must be in uint16_t format, which is unsigned
    // anything to the right of the decimal is removed, so multiply by some time constant to retain some decimals
    // divide by time constant before using the data on the master computer's side
    const int TIME_CONSTANT = 1000;

    // time only needs one decimal place and rounds over every 108.3 minutes or about 1.8 hours to avoid overflow from uint16_t datatype
    // time is temporarily uint32_t so that it can have a bit more time
    modRegister[TIME] = ((uint32_t)(time * 10)) % 65000;
    modRegister[TEMPERATURE] = (uint16_t)(temp * TIME_CONSTANT);
    modRegister[DC_VOLTAGE] = (uint16_t)(DCvolt * TIME_CONSTANT);
    modRegister[DC_CURRENT] = (uint16_t)(DCcurrent * TIME_CONSTANT);
    modRegister[AC_VOLTAGE] = (uint16_t)(ACvolt * TIME_CONSTANT);
    modRegister[AC_CURRENT] = (uint16_t)(ACcurrent * TIME_CONSTANT);
}

// if data has been sent, then return 1
int sendData() {
    if (node485.poll())
        return 1;
    return 0;
}