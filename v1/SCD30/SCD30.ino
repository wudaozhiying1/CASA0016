#include <Arduino.h>
#include <SensirionI2cScd30.h>
#include <Wire.h>

SensirionI2cScd30 sensor;

static char errorMessage[128];
static int16_t error;

void setup() {

    Serial.begin(115200);
    while (!Serial) {
        delay(100);
    }
    Wire.begin();
    sensor.begin(Wire, SCD30_I2C_ADDR_61);

    sensor.stopPeriodicMeasurement();
    sensor.softReset();
    delay(2000);
    uint8_t major = 0;
    uint8_t minor = 0;
    error = sensor.readFirmwareVersion(major, minor);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute readFirmwareVersion(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    Serial.print("firmware version major: ");
    Serial.print(major);
    Serial.print("\t");
    Serial.print("minor: ");
    Serial.print(minor);
    Serial.println();
    error = sensor.startPeriodicMeasurement(0);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute startPeriodicMeasurement(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
}

void loop() {

    float co2Concentration = 0.0;
    float temperature = 0.0;
    float humidity = 0.0;
    delay(1500);
    error = sensor.blockingReadMeasurementData(co2Concentration, temperature,
                                               humidity);
    if (error != NO_ERROR) {
        Serial.print("Error trying to execute blockingReadMeasurementData(): ");
        errorToString(error, errorMessage, sizeof errorMessage);
        Serial.println(errorMessage);
        return;
    }
    Serial.print("co2Concentration: ");
    Serial.print(co2Concentration);
    Serial.print("\t");
    Serial.print("temperature: ");
    Serial.print(temperature);
    Serial.print("\t");
    Serial.print("humidity: ");
    Serial.print(humidity);
    Serial.println();
}
