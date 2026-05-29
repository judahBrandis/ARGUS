// Requires only MAX485CPA+ module wired

#include <Arduino.h>
#include <MAX485CPA.h>
#include <ArduinoRS485.h>

void setup () {
  Serial.begin(9600); // baud rate
  
    setupRS485(); // sets up RS485
}

// Send "hello world" via RS485 every second
void loop () {
  RS485.beginTransmission();
  RS485.println("Hello world");                    
  RS485.endTransmission();
  delay(1000);                    // Ensures that only one message is sent per second
}