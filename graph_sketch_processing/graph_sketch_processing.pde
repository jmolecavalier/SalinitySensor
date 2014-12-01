/*
  Graphing sketch
 
  This program takes ASCII-encoded strings
  from the serial port at 9600 baud and graphs them. It expects values in the
  range 0 to 1023, followed by a newline, or newline and carriage return
  
 */
 
 import processing.serial.*;
 import beads.*;
 
 //VARIABLES
 //Filename of audio file to play when finished
 String finishAudioFileName = "C:\\Users\\Gunnar\\Documents\\Programming\\School-Projects\\EGEN\\Mini_Project_2\\graph_sketch_processing\\finish.mp3"; 
 Serial myPort;   // The serial port
 int xPos = 1;    // Horizontal position of the graph  
 long startTime = System.currentTimeMillis(); 
 long stopTime;   //Time in milliseconds the program will stop recording data 
 PrintWriter saveFile;
 
 void setup () {
   stopTime = System.currentTimeMillis() + 15000;  //Set up stopTime
   size(400, 300);                                //Set the window size      
   String COM = Serial.list()[1];
   myPort = new Serial(this, COM, 9600);  //First port in serial list is Arduino so we assign that to the SerialPort
   myPort.bufferUntil('\n');    //serialEvent() gets called @ a newline character
   saveFile = createWriter("data.csv"); //file to write out to
   saveFile.print("Time, Humidity, Temperature, Salinity\n"); 
   background(0);            //Set initial background
 }
 
 
 void draw () {
   // All drawing of the graph happens in serialEvent()
   if (System.currentTimeMillis() > stopTime) {  //Check if we are past our stop time
     playSound(finishAudioFileName);           //Play finishAudioFile
     saveFile.close();                           //Close file
     delay(7500);                                //Wait for audiofile to finish
     exit();                                     //Close program
   }
 }
 
 void serialEvent (Serial myPort) {
   String inString = myPort.readStringUntil('\n');  //Get the ASCII string:
   System.out.println(inString);
   if (inString != null) {   
     String data[] = new String[3];
     data = split(inString, ' ');   //Split up the data by ' '
     
     //Print time to file
     saveFile.print(System.currentTimeMillis() - startTime);
     saveFile.print(", ");
     
     //We will have 3 items, humidity (0), temp (1), ppt (2)
     //Print them to the file
     for (int i = 0; i < data.length; i++){
       saveFile.print(data[i]);
       if (i < data.length - 1) {
         saveFile.print(", ");
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
 
 // Function that plays the audio file specified in the parameter
 void playSound(String fileName) {
    AudioContext ac = new AudioContext();
    SamplePlayer player = new SamplePlayer(ac, SampleManager.sample(fileName));
    Gain g = new Gain(ac, 2, 0.2);
    g.addInput(player);
    ac.out.addInput(g);
    ac.start();
 }
