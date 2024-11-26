#include <Wire.h>
#include <Adafruit_SGP40.h>
#include <SensirionI2cScd30.h>

// 初始化 SGP40 和 SCD30
Adafruit_SGP40 sgp;
SensirionI2cScd30 scd30;

// 错误信息存储
static char errorMessage[128];
static int16_t error;

void setup() {
  // 初始化串口
  Serial.begin(115200);
  while (!Serial) delay(10);
  Serial.println("SGP40 + SCD30 on same I2C bus test");

  // 初始化 SGP40
  if (!sgp.begin()) {
    Serial.println("SGP40 sensor not found :(");
    while (1);
  }
  Serial.print("SGP40 serial #");
  Serial.print(sgp.serialnumber[0], HEX);
  Serial.print(sgp.serialnumber[1], HEX);
  Serial.println(sgp.serialnumber[2], HEX);

  // 初始化 SCD30
  Wire.begin();  // 开启 I²C
  scd30.begin(Wire, SCD30_I2C_ADDR_61);  // 默认地址 0x61
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

  // 开启 SCD30 测量
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

  // 读取 SCD30 数据
  error = scd30.blockingReadMeasurementData(co2Concentration, temperature, humidity);
  if (error != NO_ERROR) {
    Serial.print("Error reading SCD30 data: ");
    errorToString(error, errorMessage, sizeof errorMessage);
    Serial.println(errorMessage);
    return;
  }

  // 输出 SCD30 数据
  Serial.print("CO2 (ppm): ");
  Serial.print(co2Concentration);
  Serial.print("  Temp (°C): ");
  Serial.print(temperature);
  Serial.print("  Hum (%): ");
  Serial.println(humidity);

  // 使用 SCD30 数据来计算 SGP40 的 VOC 指数
  uint16_t rawVoc = sgp.measureRaw(temperature, humidity);
  int32_t vocIndex = sgp.measureVocIndex(temperature, humidity);

  // 输出 SGP40 数据
  Serial.print("Raw VOC: ");
  Serial.print(rawVoc);
  Serial.print("  VOC Index: ");
  Serial.println(vocIndex);

  delay(1000);
}
