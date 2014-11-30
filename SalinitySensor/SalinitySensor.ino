// AUTHOR: Joshwa Moellenkamp

// Include the library dependency for the humidity/tempurature sensor
#include <dht.h>
// Include the library dependency for the servo
#include <Servo.h> 

// Initialize the tempurature sensor.
dht DHT;

// Digital Pins
int DHT11_PIN   = 6; // PIN that will read the signal from the Tempurature Sensor
int solenoidPin = 5; // PIN that will write a digital LOW to trigger the relay and turn on the solenoid
int mixingPin   = 3; // PIN that will write a digital LOW to trigger the relay and turn on the mixing fan

// Analog Pins
int salinityPin = 5; // PIN that will read the signal from the Salinity Sensor

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// USER DECLARATIONS DETERMINING THE FUNCTIONALITY OF THE PROGRAM GO HERE ///////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
int reservoirTime = 4000; // The amount of time that the solenoid will open the reservoir for.
int mixTime       = 8000; // The amount of time that the mixing plate will spin for.
int hopperTime    = 4000; // The amount of time that the servo will leave the hopper open for.
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Setup method for the program.
void setup()
{
  Serial.begin(9600);
  
  // Set the pin mode for the relay pins.
  pinMode(mixingPin, OUTPUT);
  pinMode(solenoidPin, OUTPUT);
  
  // Behavior for the output pins will be random unless explicitly set here.
  digitalWrite(mixingPin, HIGH);
  digitalWrite(solenoidPin, HIGH);
  
  // Call the dumpReservoir() method.
  dumpReservoir();
  
  // Call the mix() method to agitate the mixture.
  mix();
  
  // Call the dumpBeads() method to add the beads.
  dumpBeads();
 
  // Print the headers for the serial monitor.
  Serial.println("Humidity (%)\tTempurature (C)\t\tSalinity (V)");
}

// Method that will dump the solution.
void dumpReservoir()
{
  Serial.print("Dumping reservoir for ");
  Serial.print(reservoirTime/1000);
  Serial.print(" seconds... ");
  
  // Activate the solenoid by grounding the input on the relay.
  digitalWrite(solenoidPin, LOW);
  
  // The following line will determine how long the solenoids will stay open.
  delay(reservoirTime);

  // Deactivate the solenoid as the process has been finished.
  digitalWrite(solenoidPin, HIGH);
  Serial.println("Finished.");
}

// Method that will turn on the mixer. 
void mix()
{
  Serial.print("Mixing solution for ");
  Serial.print(mixTime/1000);
  Serial.print(" seconds... ");
  
  // Turn on the relay.
  digitalWrite(mixingPin, LOW); 
  
  // The following line will determine how long the mixer will run.
  delay(mixTime);
  
  // Turn off the relay.
  digitalWrite(mixingPin, HIGH);
  Serial.println("Finished.");
}

// Method that will activate the bead hopper.
void dumpBeads()
{
  Serial.print("Opening bead hopper for ");
  Serial.print(hopperTime/1000);
  Serial.print(" seconds... ");
  
  Serial.println("Finished.");
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

