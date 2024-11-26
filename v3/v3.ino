#include <Wire.h>
#include <MiCS6814-I2C.h>  // 确保库已正确安装

MiCS6814 sensor;  // 使用默认构造函数创建 MiCS6814 对象
bool sensorConnected = false;  // 标志传感器是否连接成功

void setup() {
  Serial.begin(115200);
  while (!Serial);  // 等待串口连接
  Serial.println("Initializing MiCS6814...");

  // 初始化传感器，指定 I2C 地址为 0x19
  sensorConnected = sensor.begin(0x19);
  if (sensorConnected) {
    Serial.println("Connected to MiCS-6814 sensor.");
    sensor.powerOn();  // 启动传感器加热器
    Serial.println("Sensor powered on.");
    Serial.println("CO\tNO2\tNH3\tC3H8\tC4H10\tCH4\tH2\tC2H5OH");  // 打印标题
  } else {
    Serial.println("Failed to initialize MiCS-6814 sensor. Check connections.");
    while (1);  // 如果初始化失败，停止运行
  }
}

void loop() {
  if (sensorConnected) {
    // 读取气体浓度并打印到串口
    Serial.print(sensor.measureCO());      // 一氧化碳 (CO)
    Serial.print("\t");
    Serial.print(sensor.measureNO2());     // 二氧化氮 (NO2)
    Serial.print("\t");
    Serial.print(sensor.measureNH3());     // 氨气 (NH3)
    Serial.print("\t");
    Serial.print(sensor.measureC3H8());    // 丙烷 (C3H8)
    Serial.print("\t");
    Serial.print(sensor.measureC4H10());   // 丁烷 (C4H10)
    Serial.print("\t");
    Serial.print(sensor.measureCH4());     // 甲烷 (CH4)
    Serial.print("\t");
    Serial.print(sensor.measureH2());      // 氢气 (H2)
    Serial.print("\t");
    Serial.println(sensor.measureC2H5OH()); // 乙醇 (C2H5OH)
  } else {
    Serial.println("Sensor not connected.");
  }

  delay(1000);  // 每秒更新一次数据
}
