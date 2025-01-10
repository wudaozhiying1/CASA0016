#include <Arduino.h>
#include <SensirionI2cScd30.h>
#include <Wire.h>

SensirionI2cScd30 sensor;
static char errorMessage[128];
static int16_t error;
float wind = 0.0;
float co2Concentration = 0.0;
float temperature = 0.0;
float humidity = 0.0;

void setup() {
  Wire.begin();
  Serial.begin(115200);
  sensor.begin(Wire, SCD30_I2C_ADDR_61);


  sensor.stopPeriodicMeasurement();
  sensor.softReset();
  delay(2000);

  sensor.startPeriodicMeasurement(0);
}

void loop() {

  delay(1500);
  error = sensor.blockingReadMeasurementData(co2Concentration, temperature, humidity);
  if (error != NO_ERROR) {
    Serial.print("Error reading data: ");
    Serial.println(error);
    return;
  }


  float BCMI = BCMICalculate(temperature, humidity, wind);


  Serial.print("CO₂: ");
  Serial.print(co2Concentration);
  Serial.print(" ppm\tTemp: ");
  Serial.print(temperature);
  Serial.print(" °C\tHumidity: ");
  Serial.print(humidity);
  Serial.print(" %\tBCMI: ");
  Serial.println(BCMI);
}

float BCMICalculate(float temperature, float humidity, float wind) {

  float RH = humidity / 100.0;  
  float term1 = (1.8 * temperature + 32);
  float term2 = -0.55 * (1 - RH) * (1.8 * temperature - 26);
  float term3 = -3.2 * sqrt(wind);
  return term1 + term2 + term3;
}
