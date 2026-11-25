#pragma once
#include <ModbusRTUSlave.h>

void setupModBus(int ModBusID, int baud_rate, uint16_t inputRegisters[], int numInputRegisters);
void updateRegisters(uint16_t modRegister[], float time, float temp, float DCvolt, float DCcurrent, float ACvolt, float ACcurrent);
int sendData();