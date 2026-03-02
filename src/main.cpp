#include <arduino.h>
#include <voltageSensor.h>

#define voltageTune (5)
#define volt        (A0)

void setup() {
  Serial.begin(9600);
  measureVoltageSetup(volt);
}

void loop () {
  measureVoltage(volt, voltageTune);
}