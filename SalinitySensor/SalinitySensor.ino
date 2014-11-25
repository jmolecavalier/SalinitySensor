#include <dht.h>

//
//    FILE: dht11_test.ino
//  AUTHOR: Rob Tillaart
// VERSION: 0.1.00
// PURPOSE: DHT library test sketch for DHT11 && Arduino
//     URL:
//
// Released to the public domain
//

#include <dht.h>

dht DHT;

int DHT11_PIN   = 5;
int salinityPin = 4;
int solenoidPin = 3; 

float salinityReading;
float convertedSalinity;

void setup()
{
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

void loop()
{
  // TURN ON THE SOLENOID
  digitalWrite(solenoidPin, HIGH);
  
  
  
  // READ DATA FROM THE TEMPURATURE SENSOR
  // TEMP VARIABLE WAS ORIGINALLY CALLED chk
  int temp = DHT.read11(DHT11_PIN);
  switch (temp)
  {
    case DHTLIB_OK:  
                Serial.print("OK,\t"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.print("Checksum error,\t"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.print("Time out error,\t"); 
                break;
    default: 
                Serial.print("Unknown error,\t"); 
                break;
  }
  // READ DATA FROM THE SALINITY SENSOR
  salinityReading = analogRead(salinityPin);  
  // CONVERT THIS DATA TO A VOLTAGE
  convertedSalinity = (salinityReading / 1023.0) * 5;
  // DISPLAY DATA
  Serial.print(DHT.humidity, 1);
  Serial.print(",\t");
  Serial.print(DHT.temperature, 1);
  Serial.print(",\t");
  Serial.print(convertedSalinity);
  Serial.println(" V,");
  delay(2000);
}

