#include <Wire.h>
#include <Adafruit_SGP40.h>
#include <SensirionI2cScd30.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>

// MAX7219 点阵 LED 初始化
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4    // 4 个 8x8 点阵模块
#define DATA_PIN 26       // 数据引脚
#define CLK_PIN 22        // 时钟引脚
#define CS_PIN 24         // 片选引脚
MD_Parola matrix = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// 初始化 SGP40
Adafruit_SGP40 sgp;

// 初始化 SCD30
SensirionI2cScd30 scd30;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // 初始化 MAX7219 点阵 LED
  matrix.begin();
  matrix.setIntensity(5);  // 设置亮度
  matrix.displayClear();

  // 初始化 SGP40
  sgp.begin();

  // 初始化 SCD30
  scd30.begin(Wire, SCD30_I2C_ADDR_61); // 默认地址 0x61
  scd30.startPeriodicMeasurement(0);
}

void loop() {
  // SCD30 数据读取
  float co2 = 0.0, temp = 0.0, hum = 0.0;
if (scd30.blockingReadMeasurementData(co2, temp, hum) != NO_ERROR) {
    Serial.println("读取 SCD30 数据失败！");
  } else {
    Serial.print("SCD30 数据: ");
    Serial.print("CO2: ");
    Serial.print((int)co2);
    Serial.print(" ppm, Temp: ");
    Serial.print((int)temp);
    Serial.print(" C, Hum: ");
    Serial.print((int)hum);
    Serial.println(" %");
    String scd30Data = "CO2: " + String((int)co2) + "ppm | Temp: " + String((int)temp) + "C | Hum: " + String((int)hum) + "%";
    displayOnMatrix(scd30Data);
  }

  delay(2000); // 等待 2 秒

  // SGP40 数据读取
  uint16_t rawVoc = sgp.measureRaw(temp, hum);   // 使用温湿度校正 VOC 数据
  int32_t vocIndex = sgp.measureVocIndex(temp, hum);
  Serial.print("SGP40 数据: ");
  Serial.print("Raw VOC: ");
  Serial.print(rawVoc);
  Serial.print(", VOC Index: ");
  Serial.println(vocIndex);

  // 将 SGP40 数据滚动显示到点阵 LED
  String sgp40Data = "Raw VOC: " + String(rawVoc) + " | VOC Index: " + String(vocIndex);
  displayOnMatrix(sgp40Data);

  delay(2000); // 等待 2 秒
}

// 在点阵 LED 上滚动显示数据
void displayOnMatrix(String data) {
  matrix.displayClear();
  matrix.displayText(data.c_str(), PA_CENTER, 100, 2000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  while (!matrix.displayAnimate()); // 等待滚动完成
}
