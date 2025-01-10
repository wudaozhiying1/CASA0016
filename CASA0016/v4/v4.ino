#include <Wire.h>
#include <Adafruit_SGP40.h>
#include <SensirionI2cScd30.h>


Adafruit_SGP40 sgp;
SensirionI2cScd30 scd30;


static char errorMessage[128];
static int16_t error;

void setup() {

  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("SGP40 + SCD30 on same I2C bus test");


  if (!sgp.begin()) {
    Serial.println("SGP40 sensor not found :(");
    while (1);
  }
  Serial.print("SGP40 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);


  Wire.begin(); 
  scd30.begin(Wire, SCD30_I2C_ADDR_61);  
  scd30.stopPeriodicMeasurement();
  scd30.softReset();
  delay(2000);

  uint8_t major = 0;
  uint8_t minor = 0;
  error = scd30.readFirmwareVersion(major, minor);
  if (error != NO_ERROR) {
    Serial.print("Error reading SCD30 firmware: ");
    errorToString(error, errorMessage, sizeof errorMessage);
    Serial.println(errorMessage);
    while (1);
  }
  Serial.print("SCD30 firmware version: ");
  Serial.print(major);
  Serial.print(".");
  Serial.println(minor);


  error = scd30.startPeriodicMeasurement(0);
  if (error != NO_ERROR) {
    Serial.print("Error starting SCD30 measurement: ");
    errorToString(error, errorMessage, sizeof errorMessage);
    Serial.println(errorMessage);
    while (1);
  }
}

void loop() {
  float co2Concentration = 0.0;
  float temperature = 0.0;
  float humidity = 0.0;


  error = scd30.blockingReadMeasurementData(co2Concentration, temperature, humidity);
  if (error != NO_ERROR) {
    Serial.print("Error reading SCD30 data: ");
    errorToString(error, errorMessage, sizeof errorMessage);
    Serial.println(errorMessage);
    return;
  }


  Serial.print("CO2 (ppm): ");
  Serial.print(co2Concentration);
  Serial.print("  Temp (°C): ");
  Serial.print(temperature);
  Serial.print("  Hum (%): ");
  Serial.println(humidity);


  uint16_t rawVoc = sgp.measureRaw(temperature, humidity);
  int32_t vocIndex = sgp.measureVocIndex(temperature, humidity);

  Serial.print("Raw VOC: ");
  Serial.print(rawVoc);
  Serial.print("  VOC Index: ");
  Serial.println(vocIndex);

  delay(1000);
}
