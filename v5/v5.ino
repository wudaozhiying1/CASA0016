#include <Wire.h>
#include <Adafruit_SGP40.h>
#include <SensirionI2cScd30.h>

// 初始化 SGP40
Adafruit_SGP40 sgp;

// 初始化 SCD30
SensirionI2cScd30 scd30;

// 初始化 MiCS6814

bool sensorConnected = false; // 标志传感器是否连接成功


void setup() {
  // 初始化串口
  Serial.begin(115200);
  Wire.begin();

  // 初始化 LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  // 初始化 SGP40
  if (!sgp.begin()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SGP40 Error!");
    Serial.println("Failed to initialize SGP40!");
    while (1);
  }
  Serial.println("SGP40 Ready!");


  // 初始化 SCD30
  scd30.begin(Wire, SCD30_I2C_ADDR_61); // 默认地址 0x61
  scd30.startPeriodicMeasurement(0);
  Serial.println("SCD30 Ready!");


}

void loop() {
  // SCD30 数据读取
  float co2 = 0.0, temp = 0.0, hum = 0.0;
  if (scd30.blockingReadMeasurementData(co2, temp, hum) == NO_ERROR) {
    Serial.print("CO2: ");
    Serial.print(co2);
    Serial.print(" ppm, Temp: ");
    Serial.print(temp);
    Serial.print(" C, Humidity: ");
    Serial.println(hum);
  } else {
    Serial.println("Error reading SCD30!");
  }
  delay(100);

  // SGP40 数据读取
  uint16_t rawVoc = sgp.measureRaw(temp, hum);
  int32_t vocIndex = sgp.measureVocIndex(temp, hum);

  Serial.print("Raw VOC: ");
  Serial.print(rawVoc);
  Serial.print(" | VOC Index: ");
  Serial.println(vocIndex);

  delay(100);
}
