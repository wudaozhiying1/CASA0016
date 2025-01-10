#include <Wire.h>
#include <Adafruit_SGP40.h>
#include <SensirionI2cScd30.h>
#include <MD_MAX72xx.h>
#include <MD_Parola.h>


#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4    
#define DATA_PIN 26       
#define CLK_PIN 22        
#define CS_PIN 24         
MD_Parola matrix = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);


Adafruit_SGP40 sgp;


SensirionI2cScd30 scd30;

void setup() {
  Serial.begin(115200);
  Wire.begin();


  matrix.begin();
  matrix.setIntensity(5);  
  matrix.displayClear();


  sgp.begin();


  scd30.begin(Wire, SCD30_I2C_ADDR_61);
  scd30.startPeriodicMeasurement(0);
}

void loop() {
  float co2 = 0.0, temp = 0.0, hum = 0.0;
if (scd30.blockingReadMeasurementData(co2, temp, hum) != NO_ERROR) {
    Serial.println("reading SCD30 failed！");
  } else {
    Serial.print("SCD30 data: ");
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

  delay(2000); 


  uint16_t rawVoc = sgp.measureRaw(temp, hum);  
  int32_t vocIndex = sgp.measureVocIndex(temp, hum);
  Serial.print("SGP40 data: ");
  Serial.print("Raw VOC: ");
  Serial.print(rawVoc);
  Serial.print(", VOC Index: ");
  Serial.println(vocIndex);


  String sgp40Data = "Raw VOC: " + String(rawVoc) + " | VOC Index: " + String(vocIndex);
  displayOnMatrix(sgp40Data);

  delay(2000); 
}


void displayOnMatrix(String data) {
  matrix.displayClear();
  matrix.displayText(data.c_str(), PA_CENTER, 100, 2000, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  while (!matrix.displayAnimate());
}
