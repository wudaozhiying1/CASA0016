#include <Wire.h>
#include <SensirionI2cScd30.h>
#include <LiquidCrystal_I2C.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>

// SCD30 I2C 设置
SensirionI2cScd30 sensor;
static int16_t error;
float co2Concentration = 0.0;
float temperature = 0.0;
float humidity = 0.0;

// MAX7219 点阵 LED 设置
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define DATA_PIN 6
#define CLK_PIN 7
#define CS_PIN 5

MD_Parola matrix = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// LCD 设置
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Wire.begin();  // 初始化 I2C 总线
  Serial.begin(115200);

  // 初始化 SCD30
  sensor.begin(Wire, SCD30_I2C_ADDR_61);
  sensor.stopPeriodicMeasurement();
  sensor.softReset();
  delay(2000);
  sensor.startPeriodicMeasurement(0);

  // 初始化 MAX7219
  matrix.begin();
  matrix.setIntensity(8);  // 设置亮度
  matrix.displayClear();

  // 初始化 LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");
}

void loop() {
  // 延迟等待 SCD30 数据
  delay(1500);
  error = sensor.blockingReadMeasurementData(co2Concentration, temperature, humidity);
  if (error != NO_ERROR) {
    Serial.print("Error reading data: ");
    Serial.println(error);
    return;
  }

  // 将 SCD30 数据打印到串口
  Serial.print("CO₂: ");
  Serial.print(co2Concentration);
  Serial.print(" ppm\tTemp: ");
  Serial.print(temperature);
  Serial.print(" °C\tHumidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // 显示到 LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CO2: ");
  lcd.print((int)co2Concentration);
  lcd.print(" ppm");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print((int)temperature);
  lcd.print(" C");
  lcd.setCursor(0, 2);
  lcd.print("Hum: ");
  lcd.print((int)humidity);
  lcd.print(" %");

  // 准备滚动显示的内容
  char displayMessage[128];
  snprintf(displayMessage, sizeof(displayMessage), "CO2: %dppm Temp: %dC Hum: %d%%",
           (int)co2Concentration, (int)temperature, (int)humidity);

  // 在点阵 LED 上滚动显示数据
  matrix.displayText(displayMessage, PA_CENTER, 100, 2000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  while (!matrix.displayAnimate()) {
    // 等待滚动动画完成
  }
}
