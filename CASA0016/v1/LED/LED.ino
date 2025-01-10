#include <MD_MAX72xx.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4
#define DATA_PIN 6
#define CLK_PIN 7
#define CS_PIN 5

MD_MAX72XX matrix = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

void setup() {
  matrix.begin();                            
  matrix.control(MD_MAX72XX::INTENSITY, 8); 
  matrix.clear();                            

  displayHeart();  
}

void loop() {

}


void displayHeart() {
  
  byte heartPattern[4][8] = {
    {0b01100110, 0b11111111, 0b11111111, 0b11111111, 0b01111110, 0b00111100, 0b00011000, 0b00000000},  
    {0b01100110, 0b11111111, 0b11111111, 0b11111111, 0b01111110, 0b00111100, 0b00011000, 0b00000000},  
    {0b01100110, 0b11111111, 0b11111111, 0b11111111, 0b01111110, 0b00111100, 0b00011000, 0b00000000},  
    {0b01100110, 0b11111111, 0b11111111, 0b11111111, 0b01111110, 0b00111100, 0b00011000, 0b00000000}   
  };


  for (int module = 0; module < MAX_DEVICES; module++) {
    for (int row = 0; row < 8; row++) {
      matrix.setRow(module, row, heartPattern[module][row]);
    }
  }
}
