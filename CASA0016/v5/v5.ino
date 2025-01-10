#include <Wire.h>
#include <Adafruit_SGP40.h>
#include <SensirionI2cScd30.h>

Adafruit_SGP40 sgp;


SensirionI2cScd30 scd30;



bool sensorConnected = false; 


void setup() {

  Serial.begin(115200);
  Wire.begin();


  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");


  if (!sgp.begin()) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SGP40 Error!");
    Serial.println("Failed to initialize SGP40!");
    while (1);
  }
  Serial.println("SGP40 Ready!");



  scd30.begin(Wire, SCD30_I2C_ADDR_61); 
  scd30.startPeriodicMeasurement(0);
  Serial.println("SCD30 Ready!");


}

void loop() {

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


  uint16_t rawVoc = sgp.measureRaw(temp, hum);
  int32_t vocIndex = sgp.measureVocIndex(temp, hum);

  Serial.print("Raw VOC: ");
  Serial.print(rawVoc);
  Serial.print(" | VOC Index: ");
  Serial.println(vocIndex);

  delay(100);
}
