int analogPin = 5;     // potentiometer wiper (middle terminal) connected to analog pin 3

                       // outside leads to ground and +5V

int val = 0;           // variable to store the value read
float ppt = 0;



void setup()

{

  Serial.begin(9600);          //  setup serial

}



void loop()

{

  val = analogRead(analogPin);    // read the input pin
  ppt = ((val - 484) / 1023.0) * 16.3;
  Serial.print("Salinity is ");
  if(ppt < 0) {
    Serial.print("negligable");
  } else {
    Serial.print(ppt);
    Serial.print(" parts per thousand");
  }
  Serial.println(".");
  
  delay(2000);

}
