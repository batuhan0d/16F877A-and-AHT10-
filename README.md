# PIC16F877A with AHT10 & OLED
![Microcontroller](https://img.shields.io/badge/MCU-PIC16F877A-blue?style=flat-square&logo=microchip&logoColor=white)
![Compiler](https://img.shields.io/badge/Compiler-CCS%20C-darkred?style=flat-square)
![Language](https://img.shields.io/badge/Language-C-00599C?style=flat-square&logo=c&logoColor=white)
![Simulation](https://img.shields.io/badge/Simulation-Proteus-009639?style=flat-square)
![Protocol](https://img.shields.io/badge/Protocol-I2C-orange?style=flat-square)

A project demonstrating how to read temperature and humidity from an AHT10 sensor using a PIC16F877A and display the results on an I2C OLED display. This project is written in C for the **CCS C Compiler**.

## Features

* Reads real-time temperature (in Celsius °C).
* Reads real-time relative humidity (in %).
* Displays the data clearly on a 128x64 OLED screen.
* Written in C and compiled with the CCS C Compiler.
## Schematic
* Below is a preview of the schematic of the circuit drawn in Proteus.
   * **Schematic:** ![schematic](schematic.jpg)    
## 💻 Software & Tools

* **IDE/Compiler:** CCS C Compiler IDE (v5.025)
* **Libraries:**
    * **SSD1306 OLED Driver:** This project uses a third-party SSD1306 driver library.
    * **Source:** The library was obtained from (http://simple-circuit.com/). The original library files are included in this web site.
