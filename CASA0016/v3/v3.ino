#include <Wire.h>
#include <MiCS6814-I2C.h>  

MiCS6814 sensor;  
bool sensorConnected = false;  

void setup() {
  Serial.begin(115200);
  while (!Serial);  
  Serial.println("Initializing MiCS6814...");


  sensorConnected = sensor.begin(0x19);
  if (sensorConnected) {
    Serial.println("Connected to MiCS-6814 sensor.");
    sensor.powerOn(); 
    Serial.println("Sensor powered on.");
    Serial.println("CO\tNO2\tNH3\tC3H8\tC4H10\tCH4\tH2\tC2H5OH");  
  } else {
    Serial.println("Failed to initialize MiCS-6814 sensor. Check connections.");
    while (1);  
  }
}

void loop() {
  if (sensorConnected) {

    Serial.print(sensor.measureCO());     
    Serial.print("\t");
    Serial.print(sensor.measureNO2());     
    Serial.print("\t");
    Serial.print(sensor.measureNH3());    
    Serial.print("\t");
    Serial.print(sensor.measureC3H8());    
    Serial.print("\t");
    Serial.print(sensor.measureC4H10());   
    Serial.print("\t");
    Serial.print(sensor.measureCH4());     
    Serial.print("\t");
    Serial.print(sensor.measureH2());      
    Serial.print("\t");
    Serial.println(sensor.measureC2H5OH()); 
  } else {
    Serial.println("Sensor not connected.");
  }

  delay(1000);  
}
