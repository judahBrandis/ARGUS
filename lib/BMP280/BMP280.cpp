#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void measureTemperatureSetup () {
  /* Default settings from datasheet. */

  Wire.begin();
  Serial.println("Wire.begin(); ran");

  if (!bmp.begin(0x77)) {
    Serial.println("Error: BMP280 is not providing correct data");
  }

  bmp.setSampling(
    Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
    Adafruit_BMP280::STANDBY_MS_500
  ); /* Standby time. */

} // Sets up the tempeature reading function

float readTemperature () {
  float temperature = bmp.readTemperature();
  Serial.print(F("temperature = "));
  Serial.print(temperature);
  Serial.println(" *C");

  return temperature;
} // Displays the temperature and saves as a variable