# Node485
An STM32 based project that takes power related measurments, stores them, and sends the data
to a control station via Modbus.
## Project Overview
Status: Early development (v0.4)

The goal of Node485 is to create a PCB that is able to measure and log equipment voltage, 
current, and its own enclosure temperature. Another device then pulls that data using modbus 
and SCADA and displays real time information while providing important information and 
data logging.

This is very similar to existing equipment in applications like substations, transmission lines, and 
simple equipment power meters. For example, in a substation a device might be installed on a 
piece of equipment to measure its power consumption. To do this, the measuring device could use a voltage 
and current sensor as well as a temperature sensor for indication of whether or not it’s overheating. 
This information is then pulled through modbus by a device in a safer location that then uses this data. 

Modbus is used for its reliability, ease of use, and ruggedness. Not only does it make this project 
simpler, but it’s also used in real applications all the time for those exact reasons.

## Technical Details

### Hardware:
- [Breakout Board: STM32F446 NUCLEO](https://www.digikey.com/en/products/detail/stmicroelectronics/NUCLEO-F446RE/5347712?utm_source=chatgpt.com)
- [Temperature Sensor: BMP280](https://www.amazon.com/dp/B07VNDZ6N4?ref=ppx_yo2ov_dt_b_fed_asin_title&th=1)
- [Current & Voltage Sensor: INA219](https://www.adafruit.com/product/904#tutorials)
- [Micro SD Card Module](https://www.amazon.com/dp/B08C4WY2WR?ref=ppx_yo2ov_dt_b_fed_asin_title)
- [RS485 Tranceiver: MAX485CPA+](https://www.digikey.com/en/products/detail/analog-devices-inc-maxim-integrated/MAX485CPA/948026?gclid=8f93f0dd57ea13ac1df099f881cb0a2e&gclsrc=3p.ds&msclkid=8f93f0dd57ea13ac1df099f881cb0a2e)
- [RS485 to USB Adapter](https://www.amazon.com/dp/B081MB6PN2?ref=clp_hp_h_pc)
  
### Current Features:
- Temperature data acquisition
- DC voltage data acquisition
- DC current data acquisition
- DC power measurement
- SD Card Data logging

### Planned Features:
1. Data communication via RS485
2. Modbus protocal with control station
3. Smart dashboard via control station
4. AC voltage data acquisition
5. AC current data acquisition
6. AC power measurement

## Setting Up

### Getting Started:
1. Obtain hardware listed in hardware section
2. Download VS Code Appliation
3. Upload code from Github to VS Code
4. Wire according to the provided wiring diagrams
5. Run test code in src main file to test/run components individually 

### Helpful Debugging
- BMP280: Soldering the pins to the sensor helps with connectivity
- INA219: 
    - Soldering the pins to sensor helps with connectivity
    - There are two sets of Vin, only use one
- SD Card Reader: 
    - Should hear click from sd card when inserted into reader
    - sd card can be pushed in to release from lock mechanism in reader
    - Must manually clear data when you want to refresh data
- MAX485CPA+: The RS485 to USB adapter has three indicator lights 
    - Power should be on anytime nucleo board has power 
    - RXD should be on whenever information is being sent from nucleo to computer
    - TXD should be on whenever information is being sent from computer to nucleo

## Wiring Diagrams

### BMP280 (Temperature Sensor):
<img src="Images/BMP280%20Wiring%20Diagram.png" width="60%">

### INA219 (Current & Voltage Sensor):
<img src="Images/INA219 Wiring Diagram.png" width="60%">

### SD Card Reader (SPI):
<img src="Images/sdCard Wiring Diagram.png" width="60%">

### MAX485CPA+ (RS485 Tranceiver):
<img src="Images/MAX485CPA Wiring Diagram.png" width="60%">

## Methods

<!-- ----------------------------------------------------------------------------------------------- -->
<!-- setupBMP280() -->

<details>
<summary id="Node485-1"><strong>setupBMP280()</strong></summary>

<blockquote>

### Description
Automatically connects to the BMP280 sensor and uploads the standard settings to the sensor. 
This function is only meant to be run once, and should be ran before the BMP280 sensor is used.

### Syntax
- `setupBMP280()`

### Parameters
- None

### Example
```cpp
#include <BMP280.h>

void setup () {
    setupBMP280();
}
```

</blockquote>
    
</details>

<!-- ----------------------------------------------------------------------------------------------- -->
<!-- setupINA() -->

<details>
<summary id="Node485-2"><strong>setupINA()</strong></summary>

<blockquote>

### Description
Automatically connects to the INA219 sensor. 
This function is only meant to be run once, and should be ran before the INA219 sensor is used.

### Syntax
- `setupINA()`

### Parameters
- None

### Example
```cpp
#include <INA219j.h>

void setup () {
    setupINA();
}
```

</blockquote>
    
</details>

<!-- ----------------------------------------------------------------------------------------------- -->
<!-- setupSD() -->

<details>
<summary id="Node485-3"><strong>setupSD()</strong></summary>

<blockquote>

### Description
Automatically connects to the micro sd card module and uploads the standard settings to the sensor. 
If a CSV file with the given file name doesn't exist, then a new file with that name will be created and given column titles in the first row of the CSV file.
This function is only meant to be run once, and should be ran before the sd card is used.

### Syntax
- `setupSD(file_name)`

### Parameters
- `file_name`: a pointer to an array of `char` data types, or essentially a string. It's the name of the file that data will be stored in. If a file with the given name doesn't exist, then one will be created.

### Example
```cpp
#include <sdCard.h>

char *file_name = "Net485.CSV";

void setup () {
    setupSD(file_name);
}
```

</blockquote>
    
</details>

<!-- ----------------------------------------------------------------------------------------------- -->
<!-- setupModBus() -->

<details>
<summary id="Node485-4"><strong>setupModBus()</strong></summary>

<blockquote>

### Description
Configures ModBus by defining communication pins, baud rate, and registers. 
This function is only meant to be run once, and should be ran before any ModBus commands are used.

### Syntax
- `setupModBus(ModBusID, baud_rate, inputRegisters, numInputRegisters)`

### Parameters
- `ModBusID`: `int` data type representing the id of the Node485 module. Each module must have a unique id so that
the master computer can differentiate data from different modules and request data individually. 
- `baud_rate`: `int` data type re baud rate of the Node485 module. By defualt, the baud rate is 9600
- `inputRegisters`: An array of `float` values. Each index holds a different data measurement. For example, index 0 holds
the time that a measurement was taken, index 1 the temperature, etc. There are 6 indexes, and when the master computer desires data,
the registers are automatically sent.
- `NumInputRegisters`: `int` data type. How many data measurements are sent via ModBus. By defualt this is 6 as there are 6 data points
measured by a Node485 module, but by changing this you could send only the first 5 or such while still saving all 6 data points to the CSV file.

### Example
```cpp
#include <ModBusj.h>

numInputRegisters = 6;
float inputRegisters[numInputRegisters] = {0};

void setup () {
    int baud_rate = 9600;
    int ModBusID = 1;

    setupModBus(ModBusID, baud_rate, inputRegisters, numInputRegisters);
}
```

</blockquote>
    
</details>

<!-- ----------------------------------------------------------------------------------------------- -->
<!-- measureTime() -->

<details>
<summary id="Node485-5"><strong>measureTime()</strong></summary>

<blockquote>

### Description
Meausres how much time has passed since the microcontroller turned on and began operating. The 
return type is a float, and measures in seconds and is accurate to a milisecond. 

### Syntax
- `measureTime()`

### Parameters
- None

### Example
```cpp
#include <sdCard.h>

float time = measureTime();
```

</blockquote>
    
</details>

<!-- ----------------------------------------------------------------------------------------------- -->
<!-- measureVoltage() -->

<details>
<summary id="Node485-6"><strong>measureVoltage()</strong></summary>

<blockquote>

### Description
Meausres DC voltage across two points using the INA219 sensor. Make sure to run `setupINA()` before using this command as the 
sensor must be connected to before being used. 

### Syntax
- `measureVoltage()`

### Parameters
- None

### Example
```cpp
#include <INA219j.h>

setupINA();
float voltMeasured = measureVoltage();
```

</blockquote>
    
</details>

<!-- ----------------------------------------------------------------------------------------------- -->
<!-- measureCurrent() -->

<details>
<summary id="Node485-7"><strong>measureCurrent()</strong></summary>

<blockquote>

### Description
Meausres DC current between two points using the INA219 sensor. Make sure to run `setupINA()` before using this command as the 
sensor must be connected to before being used. 

### Syntax
- `measureCurrent()`

### Parameters
- None

### Example
```cpp
#include <INA219j.h>

setupINA();
float currentMeasured = measureCurrent();
```

</blockquote>
    
</details>

<!-- ----------------------------------------------------------------------------------------------- -->
<!-- measureTemperature() -->

<details>
<summary id="Node485-8"><strong>measureTemperature()</strong></summary>

<blockquote>

### Description
Meausres temperature in Celcius using the BMP280 sensor. Make sure to run `setupBMP280()` before using this command as the 
sensor must be connected to before being used. 

### Syntax
- `measureTemperature()`

### Parameters
- None

### Example
```cpp
#include <BMP280.h>

setupBMP280();
float temperatureMeasured = measureTemperature();
```

</blockquote>
    
</details>

<!-- ----------------------------------------------------------------------------------------------- -->
<!-- updateRegisters() -->

<details>
<summary id="Node485-8"><strong>updateRegisters()</strong></summary>

<blockquote>

### Description
Updates the ModBus registers with new data from sensors. 
`setupModBus()` does not need to be used before using this command as the ModBus communication isn't required to update or define registers. 
### Syntax
- `updateRegisters(modRegister, time, temp, DCvolt, DCcurrent, ACvolt, ACcurrent)`

### Parameters
- `modRegister`: An array of `float` values. Each index holds a different data measurement. For example, index 0 holds
the time that a measurement was taken, index 1 the temperature, etc. There are 6 indexes, and when the master computer desires data,
the registers are automatically sent.
- `time`: `float` data type. How much time has passed since the microcontroller began operating
- `temp`: `float` data type. A temperature reading (C). 
- `DCvolt`: `float` data type. A DC voltage reading (V).
- `DCcurrent`: `float` data type. A DC current reading (A).
- `ACvolt`: `float` data type. An AC voltage reading (Vrms).
- `ACcurrent`: `float` data type. An AC current reading (Arms).

### Example
```cpp

// take data measurements
float timeMeasure = measureTime();
float voltageMeasure = measureVoltage();
float currentMeasure = measureCurrent();
float tempMeasure = measureTemperature();

// in this example it's a DC system, so no AC voltage or current, only DC
float ACvoltage = 0.0;
float ACcurrent = 0.0;

// update the registers with newly acquired data
updateRegisters(myRegisters, timeMeasure, tempMeasure, voltageMeasure, currentMeasure, ACvoltage, ACcurrent);
```

</blockquote>
    
</details>

<!-- ----------------------------------------------------------------------------------------------- -->
<!-- sendData() -->

<details>
<summary id="Node485-8"><strong>sendData()</strong></summary>

<blockquote>

### Description
Check if the master computer has requested any data. If so, automatically send the data stored in the register and return 1.
Otherwise, return 0 and do nothing. Make sure to run `setupModBus()` before using this command as the 
ModBus communication must be setup before being used. 

### Syntax
- `sendData()`

### Parameters
- None

### Example
```cpp
#include <ModBusj.h>

// for setting up ModBus communication
numInputRegisters = 6;
float inputRegisters[numInputRegisters] = {0};

void setup () {
    int baud_rate = 9600;
    int ModBusID = 1;

    setupModBus(ModBusID, baud_rate, inputRegisters, numInputRegisters);
}

// constantly check if data has been requested and if so, send the data stored in the registers
// in this example, the registers aren't updated, so when data is requested, the registers will contain 0, not accurate data
void loop () {
    int dataSent = sendData();
}
```

</blockquote>
    
</details>