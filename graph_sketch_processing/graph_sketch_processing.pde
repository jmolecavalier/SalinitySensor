  import processing.serial.*;
 
 // Variables
 Serial myPort;   // The serial port
 int xPos = 1;    // Horizontal position of the graph  
 long startTime = System.currentTimeMillis(); 
 long stopTime;   // How long the program will run before stopping
 PrintWriter saveFile;
 
 void setup () {
   // Set up stopTime.
   stopTime = System.currentTimeMillis() + 30000;  
   // Set the window size.
   size(400, 300);                                     
   String COM = Serial.list()[1];
   
   // Get the arduino port.
   myPort = new Serial(this, COM, 9600);  
   // Things will happen until the newline character is identified.
   myPort.bufferUntil('\n');  
   
   // Initialize the file to write out to  .
   saveFile = createWriter("results.csv"); 
   // Print the headings for the file.
   saveFile.print("Time, Humidity, , Temperature, , Salinity\n"); 
   background(0);         
 }
 
 void draw () {
   // All drawing of the graph happens in serialEvent()
   if (System.currentTimeMillis() > stopTime) {  //Check if we are past our stop time
     saveFile.close();                           //Close file
     exit();                                     //Close program
   }
 }
 
 void serialEvent (Serial myPort) {
   // Get the string from the serial port
   String inString = myPort.readStringUntil('\n');
   // Print it out to Proccessing's data monitor
   System.out.println(inString);
   
   if (inString != null) {   
     String data[] = new String[3];
     data = split(inString, ' ');   //Split up the data by ' '
     
     // Write out the current time to the desired file
     saveFile.print(System.currentTimeMillis() - startTime);
     saveFile.print(", ");
     
     // Print the humidity, tempurature, and salinity
     for (int i = 0; i < data.length; i++){
       saveFile.print(data[i]);
       if (i < data.length - 1) {
         saveFile.print(",");
       }
     }
     
     // Convert to a float and map to the screen height:
     float inByte = float(data[2]); 
     inByte = map(inByte, 0, 100, 0, height);
     
     // Draw the line:
     stroke(127,34,255);
     line(xPos, height, xPos, height - inByte);
     
     // At the edge of the screen, go back to the beginning:
     if (xPos >= width) {
       xPos = 0;
       background(0); 
     } 
     else {
       xPos++;    //Increment the horizontal position
     }
   } 
 }
