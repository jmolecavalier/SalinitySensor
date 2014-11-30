// AUTHOR: Joshwa Moellenkamp

// Include the library dependency for the humidity/tempurature sensor
#include <dht.h>
// Include the library dependency for the servo
#include <Servo.h> 

dht DHT;

// Digital Pins
int DHT11_PIN   = 6; // PIN that will read the signal from the Tempurature Sensor
int mixingPin   = 3; // PIN that will write a digital LOW to trigger the relay and turn on the mixing fan
int solenoidPin = 5; // PIN that will write a digital LOW to trigger the relay and turn on the solenoid

// Analog Pins
int salinityPin = 5; // PIN that will read the signal from the Salinity Sensor

// Setup method for the program.
void setup()
{
  Serial.begin(9600);
  // Set the pin mode for the mixingPin to be an output.
  pinMode(mixingPin, OUTPUT);
  // Print the headers for the serial monitor.
  Serial.println("Humidity (%)\tTempurature (C)\t\tSalinity (V)");
  // Call the dumpReservoir() method.
  dumpReservoir();
  // Call the mix() method to agitate the mixture.
  mix();
  // Call the dumpBeads() method to add the beads.
  dumpBeads();
}

// Dump the solution for a variable amount of time to get the desired solution. 
void dumpReservoir()
{
  Serial.println("dumpReservoir() function entered");
  // TODO: FLIP THIS FOR ACTUAL USE.
  digitalWrite(solenoidPin, HIGH);
  delay(5000);
  // TODO: FLIP THIS FOR ACTUAL USE.
  digitalWrite(solenoidPin, LOW);

}

// Method that will turn on the mixer. 
// Set the delay() instruction to determine how long it will be left on.
void mix()
{
  // Turn on the relay.
  digitalWrite(mixingPin, LOW); 
  
  // The following line will determine how long the mixer will run.
  delay(10000);
  
  // Turn off the relay.
  digitalWrite(mixingPin, HIGH);
}

// Dump the beads from the hopper.
// Set the delay() instruction to determine how long it will be left on.
void dumpBeads()
{
  Serial.println("dumpBeads() function entered");

}

// Check the salinity and ambient data readings every 2 seconds
void loop()
{   
  // Read data from the tempurature sensor, save the information in variable 'chk'.
  int chk = DHT.read11(DHT11_PIN);
  
  // Read analog input from the salinity sensor, save the reading to variable 'salinityReading'.
  float salinityReading = analogRead(salinityPin);  
  // Convert this reading to a voltage
  float convertedSalinity = (salinityReading / 1023.0) * 5;
  
  
  // TODO: GET THE SALINITY READINGS HERE
  
  
  // Write out the collected data to the serial monitor.
  Serial.print(DHT.humidity, 1);
  Serial.print("\t\t");
  Serial.print(DHT.temperature, 1);
  Serial.print("\t\t\t");
  Serial.print(convertedSalinity);
  Serial.println(" V");
  delay(2000);
}

