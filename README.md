Status: Early development (v0.1.4)

The goal of ARGUS is to create a PCB that is able to measure and log equipment voltage, 
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

Hardware:
- STM32F446 NUCLEO
- BMP280 pressure sensor
- INA219 current sensor
  
Current Features:
- Temperature data acquisition

Planned Features:
- Voltage data acquisition
- Current data acquisition
- Power measurement
- Resistance measurement
- Data logging
- Data communication via modbus
- Smart dashboard via control station

Getting Started:
1. Install PlatformIO in VS Code
2. Create a new project and select nucleo_f446re as the board
3. Upload code from Github to project
4. Wire according to the provided wiring diagrams
