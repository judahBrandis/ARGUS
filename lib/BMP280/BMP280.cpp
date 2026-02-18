// Only library I added myself
#include <Arduino.h> 

// All 3 libraries are from the Adafruit BMP280 library
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h> 

// I defined both pins in the hopes of solving the I2C issue
#define SDA_PIN D14
#define SCL_PIN D15

// Used by Adafruit in test code
Adafruit_BMP280 bmp;
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

// Sets up the tempeature reading function - everything that goes in setup()
void measureTemperatureSetup () {
  // I believe this is declaring the I2C pins? 
  // Wasn't in origonal library code, added for debugging
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.println("Wire.begin(); ran");

  // Checks if connected to I2C address
  // Wasn't in origonal library code, added for debugging
  // 0x76 if SDO is connected to ground, 0x77 if SDO connected to VCC
  if (!bmp.begin(0x77)) { 
    Serial.println("Error: BMP280 is not providing correct data");
  }
  
  // Default settings from library (sensortest) & datasheet
  bmp.setSampling
  (
    Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
    Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
    Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
    Adafruit_BMP280::FILTER_X16,      /* Filtering. */
    Adafruit_BMP280::STANDBY_MS_500
  ); /* Standby time. */
  bmp_temp->printSensorDetails();
} 

// Displays the temperature and serves as a variable - everything in main()
float readTemperature () {
  // saves the temperature in a veriable
  sensors_event_t temp_event;
  float mesTemperature = temp_event.temperature;

  // prints the temperature to the screen
  Serial.print(F("Temperature = "));
  Serial.print(temp_event.temperature);
  Serial.println(" *C");

  // sets the value of the readTemperature function to the current temperature reading
  return mesTemperature;
} 