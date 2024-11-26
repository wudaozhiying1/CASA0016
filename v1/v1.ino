#include <Arduino.h>
#include <SensirionI2cScd30.h>
#include <Wire.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>

// SCD30 I2C 设置
SensirionI2cScd30 sensor;
static char errorMessage[128];
static int16_t error;

// MAX7219 点阵 LED 设置
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define DATA_PIN 6
#define CLK_PIN 7
#define CS_PIN 5

MD_Parola matrix = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup() {
  Wire.begin();
  Serial.begin(115200);
  while (!Serial) {
      delay(100);
  }
  sensor.begin(Wire, SCD30_I2C_ADDR_61);

  // 初始化 SCD30
  sensor.stopPeriodicMeasurement();
  sensor.softReset();
  delay(2000);

  sensor.startPeriodicMeasurement(0);

  // 初始化 MAX7219
  matrix.begin();
  matrix.setIntensity(8);  // 设置亮度
  matrix.displayClear();
}

void loop() {
  float co2Concentration = 0.0;
  float temperature = 0.0;
  float humidity = 0.0;

  // 延迟等待 SCD30 数据
  delay(1500);
  error = sensor.blockingReadMeasurementData(co2Concentration, temperature, humidity);
  if (error != NO_ERROR) {
    Serial.print("Error reading data: ");
    Serial.println(error);
    return;
  }

  // 打印到串口
  Serial.print("CO₂: ");
  Serial.print(co2Concentration);
  Serial.print(" ppm\tTemp: ");
  Serial.print(temperature);
  Serial.print(" °C\tHumidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // 准备滚动显示的内容
  char displayMessage[128];
  int CO2_num = (int)co2Concentration;
  int Temp_num = (int)temperature;
  int Hum_num = (int)humidity;

  snprintf(displayMessage, sizeof(displayMessage), "CO2: %dppm Temp : %dC Hum: %d%%",
           CO2_num, Temp_num, Hum_num);

  // 滚动显示数据
  matrix.displayText(displayMessage, PA_CENTER, 100, 2000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  while (!matrix.displayAnimate()) {
    // 等待滚动动画完成
  }
}