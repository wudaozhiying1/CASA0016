#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define DATA_PIN 6
#define CLK_PIN 7
#define CS_PIN 5

MD_MAX72XX matrix = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup() {
  matrix.begin();                            // 初始化 MAX7219
  matrix.control(MD_MAX72XX::INTENSITY, 8);  // 设置亮度（0-15）
  matrix.clear();                            // 清屏

  displayHeart();  // 显示心形图案
}

void loop() {
  // 心形图案保持显示
}

// 显示心形图案
void displayHeart() {
  // 定义 4 个模块的心形图案
  byte heartPattern[4][8] = {
    {0b01100110, 0b11111111, 0b11111111, 0b11111111, 0b01111110, 0b00111100, 0b00011000, 0b00000000},  // 第 1 块
    {0b01100110, 0b11111111, 0b11111111, 0b11111111, 0b01111110, 0b00111100, 0b00011000, 0b00000000},  // 第 2 块
    {0b01100110, 0b11111111, 0b11111111, 0b11111111, 0b01111110, 0b00111100, 0b00011000, 0b00000000},  // 第 3 块
    {0b01100110, 0b11111111, 0b11111111, 0b11111111, 0b01111110, 0b00111100, 0b00011000, 0b00000000}   // 第 4 块
  };

  // 将图案逐块显示到 4 个模块上
  for (int module = 0; module < MAX_DEVICES; module++) {
    for (int row = 0; row < 8; row++) {
      matrix.setRow(module, row, heartPattern[module][row]);
    }
  }
}
