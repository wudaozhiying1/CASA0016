# CASA0016
# Introduction

This repository contains multiple Arduino programs demonstrating the use of various sensor modules for environmental data collection and hardware control. These programs include functionalities like CO2 monitoring, temperature and humidity measurement, gas sensor operations, and LED displays.

# File Descriptions

# 1. v1.ino

Uses the SCD30 sensor to measure CO2 concentration, temperature, and humidity.

Computes BCMI (Body Comfort Metric Index) to evaluate human comfort based on environmental parameters.

Modules Used:

Sensirion SCD30 I2C sensor.

# 2. v2.ino

Functionality:

Collects CO2, temperature, and humidity data using the SCD30 sensor. 

Displays data in real-time on an LCD and LED matrix module.

Modules Used:

1. Sensirion SCD30 I2C sensor.

2. 20x4 I2C LCD display.

3. MD_MAX72XX LED matrix display module.

# 3. v3.ino

Functionality:

Uses the MiCS-6814 sensor to monitor concentrations of various gases (e.g., CO, NO2, NH3).

Modules Used:

MiCS-6814 gas sensor.

4. v4.ino

Functionality:

Simultaneously uses the SGP40 and SCD30 sensors.

SGP40 measures Volatile Organic Compounds (VOC).

SCD30 measures CO2 concentration, temperature, and humidity.

Modules Used:

Adafruit SGP40 VOC sensor.

Sensirion SCD30 CO2 sensor.

# 5. v5.ino

Functionality:

Enhances the integration of SGP40 and SCD30 sensors.

Adds improved error handling and debug output.

Modules Used:

Adafruit SGP40 VOC sensor.

Sensirion SCD30 CO2 sensor.

# 6. LED.ino

Functionality:

Demonstrates how to display a "heart pattern" on an MD_MAX72XX LED matrix.

Modules Used:

MD_MAX72XX LED matrix module.

# 7. SCD30.ino

Functionality:

Demonstrates basic usage of the SCD30 sensor for CO2, temperature, and humidity measurement.

Provides examples for sensor firmware version retrieval and initialization.

Modules Used:

Sensirion SCD30 CO2 sensor.

# 8. test.txt

Functionality:

Integrates multiple sensors, including SCD30, SGP40, and MiCS6814.

Displays environmental data (e.g., CO2, VOC, gas concentrations) on an LCD and LED matrix.

Modules Used:

Sensirion SCD30 CO2 sensor.

Adafruit SGP40 VOC sensor.

MiCS6814 gas sensor.

LiquidCrystal_I2C LCD.

MD_MAX72XX LED matrix.

# 9. lcd co2.txt

Functionality:

Demonstrates how to use an LCD to display CO2 concentration, temperature, and humidity measured by the SCD30 sensor.

Modules Used:

Sensirion SCD30 CO2 sensor.

LiquidCrystal_I2C LCD.

# 10. v6.ino

Functionality:

Expands on the functionalities of test.txt, integrating sensors for enhanced environmental monitoring.

Provides additional visualization and error handling features.

Modules Used:

1. Sensirion SCD30 CO2 sensor.

2. Adafruit SGP40 VOC sensor.

3. MiCS6814 gas sensor.

4.LiquidCrystal_I2C LCD.

5.MD_MAX72XX LED matrix.

Hardware Requirements

Arduino-compatible development board (e.g., Arduino Uno, Mega, Nano).

Supported sensor modules:

1. SCD30 (CO2, temperature, humidity)

2. SGP40 (VOC)

3. MiCS-6814 (multiple gases)

Display modules:

1. 20x4 I2C LCD.

2. MD_MAX72XX LED matrix module.

Software Requirements

1. Arduino IDE.

Install the following libraries via Arduino Library Manager:

1. Wire

2. Adafruit_SGP40

3. SensirionI2cScd30

4. LiquidCrystal_I2C

5. MD_MAX72XX

6.MD_Parola

# Instructions


Open the Arduino IDE and load the desired .ino file.

Ensure the hardware is correctly connected and the necessary libraries are installed.

Adjust configurations in the code (e.g., I2C addresses, pin definitions) as needed.

Compile and upload the code to the development board.

Use the Serial Monitor or observe the LCD/LED outputs to view the results.

# Notes

Ensure the voltage of sensors and display modules is compatible with the Arduino board (typically 3.3V or 5V).

Use the Serial Monitor during debugging to view detailed error messages.


