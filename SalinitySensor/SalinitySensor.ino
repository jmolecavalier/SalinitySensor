// AUTHOR: Joshwa Moellenkamp
#include <dht.h>

dht DHT;

int DHT11_PIN   = 5; // PIN that will read the signal from the Tempurature Sensor
int salinityPin = 4; // PIN that will read the signal from the Salinity Sensor
int solenoidPin = 3; // PIN that will write a digital HIGH to power a solenoid

float salinityReading;   // Float that will hold the signal from the Salinity Sensor
float convertedSalinity; // Float that will hold the Salinity Sensor's reading in Voltage

// SET UP THE PRGOGRAM
void setup()
{
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Type,\tstatus,\tHumidity (%),\tTemperature (C)");
}

// CREATE THE FUNCTIONALITY LOOP
void loop()
{
  // TURN ON THE SOLENOID
  digitalWrite(solenoidPin, HIGH);
  
  // READ DATA FROM THE TEMPURATURE SENSOR
  // TEMP VARIABLE WAS ORIGINALLY CALLED chk
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
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

