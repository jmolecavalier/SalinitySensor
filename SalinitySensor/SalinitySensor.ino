// AUTHOR: Joshwa Moellenkamp
#include <dht.h>

dht DHT;

// Digital Pins
int DHT11_PIN   = 0; // PIN that will read the signal from the Tempurature Sensor
int mixingPin   = 1; // PIN that will write a digital HIGH to turn on the mixing fan

// Analog Pins
int salinityPin = 5; // PIN that will read the signal from the Salinity Sensor

int k = 0;

float salinityReading;   // Float that will hold the signal from the Salinity Sensor
float convertedSalinity; // Float that will hold the Salinity Sensor's reading in Voltage

// SET UP THE PROGRAM
void setup()
{
  Serial.begin(9600);
  Serial.println("Humidity (%)\tTempurature (C)\t\tSalinity (V)");
  pinMode(mixingPin, OUTPUT);
}

int mix()
{
 analogWrite(mixingPin, 255); 
 delay(10000);
 analogWrite(mixingPin, 0);
 return 1;
}

// CREATE THE FUNCTIONALITY LOOP
void loop()
{ 
  // READ DATA FROM THE TEMPURATURE SENSOR
  // TEMP VARIABLE WAS ORIGINALLY CALLED chk
  int chk = DHT.read11(DHT11_PIN);
  
  // READ DATA FROM THE SALINITY SENSOR
  salinityReading = analogRead(salinityPin);  
  // CONVERT THIS DATA TO A VOLTAGE
  convertedSalinity = (salinityReading / 1023.0) * 5;
  
  // DISPLAY DATA
  Serial.print(DHT.humidity, 1);
  Serial.print("\t\t");
  Serial.print(DHT.temperature, 1);
  Serial.print("\t\t\t");
  Serial.print(convertedSalinity);
  Serial.println(" V");
  delay(2000);
}

