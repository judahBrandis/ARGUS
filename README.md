# Automated Remote Grid Utility System (ARGUS)
An STM32 based project that takes power related measurments, stores them, and sends the data
to a control station via Modbus.
## Project Overview
Status: Early development (v0.4)

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
- Voltage data acquisition
- Current data acquisition
- Power measurement
- SD Card Data logging

### Planned Features:
- Data communication via RS485
- Modbus protocal with control station
- Smart dashboard via control station

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
<img src="Images/MAX485CPA+ Wiring Diagram.png" width="60%">