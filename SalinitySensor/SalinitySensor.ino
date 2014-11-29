// AUTHOR: Joshwa Moellenkamp
#include <dht.h>

dht DHT;

int DHT11_PIN   = 5; // PIN that will read the signal from the Tempurature Sensor (DIGITAL PIN!)
int salinityPin = 4; // PIN that will read the signal from the Salinity Sensor (ANALOG PIN!)
int solenoidPin = 3; // PIN that will write a digital HIGH to power a solenoid (ANALOG PIN!)
int mixingPin   = 2; // PIN that will write a digital HIGH to turn on the mixing fan (ANALOG PIN!)

float salinityReading;   // Float that will hold the signal from the Salinity Sensor
float convertedSalinity; // Float that will hold the Salinity Sensor's reading in Voltage

// SET UP THE PROGRAM
void setup()
{
  Serial.begin(9600);
  Serial.println("DHT TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT_LIB_VERSION);
  Serial.println();
  Serial.println("Humidity (%),\tTempurature (C),\tSalinity (V),\tValue for Graph");
  pinMode(mixingPin, OUTPUT);
}

void mix()
{
 analogWrite(mixingPin, 255); 
 delay(10000);
 analogWrite(mixingPin, 0);
 delay();
}

// CREATE THE FUNCTIONALITY LOOP
void loop()
{
  // TURN ON THE MIXER
  mix();
  
  // READ DATA FROM THE TEMPURATURE SENSOR
  // TEMP VARIABLE WAS ORIGINALLY CALLED chk
  int chk = DHT.read11(DHT11_PIN);
  
  // READ DATA FROM THE SALINITY SENSOR
  salinityReading = analogRead(salinityPin);  
  // CONVERT THIS DATA TO A VOLTAGE
  convertedSalinity = (salinityReading / 1023.0) * 5;
  
  // DISPLAY DATA
  Serial.print(DHT.humidity, 1);
  Serial.print(",\t\t");
  Serial.print(DHT.temperature, 1);
  Serial.print(",\t\t\t");
  Serial.print(convertedSalinity);
  Serial.print(" V,\t\t\t");
  Serial.println(salinityReading);
  delay(2000);
}

