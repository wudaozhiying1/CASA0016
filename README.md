# CASA0016
# Introduction

This repository contains multiple Arduino programs demonstrating the use of various sensor modules for environmental data collection and hardware control. These programs include functionalities like CO2 monitoring, temperature and humidity measurement, gas sensor operations, and LED displays.

## File Descriptions

1. v1.ino

Functionality:

Uses the SCD30 sensor to measure CO2 concentration, temperature, and humidity.

Computes BCMI (Body Comfort Metric Index) to evaluate human comfort based on environmental parameters.

Modules Used:

Sensirion SCD30 I2C sensor.

2. v2.ino

Functionality:

Collects CO2, temperature, and humidity data using the SCD30 sensor.

Displays data in real-time on an LCD and LED matrix module.

Modules Used:

Sensirion SCD30 I2C sensor.

20x4 I2C LCD display.

MD_MAX72XX LED matrix display module.

3. v3.ino

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

5. v5.ino

Functionality:

Enhances the integration of SGP40 and SCD30 sensors.

Adds improved error handling and debug output.

Modules Used:

Adafruit SGP40 VOC sensor.

Sensirion SCD30 CO2 sensor.

6. LED.ino

Functionality:

Demonstrates how to display a "heart pattern" on an MD_MAX72XX LED matrix.

Modules Used:

MD_MAX72XX LED matrix module.

7. SCD30.ino

Functionality:

Demonstrates basic usage of the SCD30 sensor for CO2, temperature, and humidity measurement.

Provides examples for sensor firmware version retrieval and initialization.

Modules Used:

Sensirion SCD30 CO2 sensor.

8. test.txt

Functionality:

Integrates multiple sensors, including SCD30, SGP40, and MiCS6814.

Displays environmental data (e.g., CO2, VOC, gas concentrations) on an LCD and LED matrix.

Modules Used:

Sensirion SCD30 CO2 sensor.

Adafruit SGP40 VOC sensor.

MiCS6814 gas sensor.

LiquidCrystal_I2C LCD.

MD_MAX72XX LED matrix.

9. lcd co2.txt

Functionality:

Demonstrates how to use an LCD to display CO2 concentration, temperature, and humidity measured by the SCD30 sensor.

Modules Used:

Sensirion SCD30 CO2 sensor.

LiquidCrystal_I2C LCD.

10. v6.ino

Functionality:

Expands on the functionalities of test.txt, integrating sensors for enhanced environmental monitoring.

Provides additional visualization and error handling features.

Modules Used:

Sensirion SCD30 CO2 sensor.

Adafruit SGP40 VOC sensor.

MiCS6814 gas sensor.

LiquidCrystal_I2C LCD.

MD_MAX72XX LED matrix.

Hardware Requirements

Arduino-compatible development board (e.g., Arduino Uno, Mega, Nano).

Supported sensor modules:

SCD30 (CO2, temperature, humidity)

SGP40 (VOC)

MiCS-6814 (multiple gases)

Display modules:

20x4 I2C LCD.

MD_MAX72XX LED matrix module.

Software Requirements

Arduino IDE.

Install the following libraries via Arduino Library Manager:

Wire

Adafruit_SGP40

SensirionI2cScd30

LiquidCrystal_I2C

MD_MAX72XX

MD_Parola

Instructions

Clone this repository:

git clone https://github.com/your-repo-name.git

Open the Arduino IDE and load the desired .ino file.

Ensure the hardware is correctly connected and the necessary libraries are installed.

Adjust configurations in the code (e.g., I2C addresses, pin definitions) as needed.

Compile and upload the code to the development board.

Use the Serial Monitor or observe the LCD/LED outputs to view the results.

Notes

Ensure the voltage of sensors and display modules is compatible with the Arduino board (typically 3.3V or 5V).

Use the Serial Monitor during debugging to view detailed error messages.

Contribution

Contributions are welcome! Feel free to:

Raise issues.

Suggest improvements.

Submit Pull Requests.
