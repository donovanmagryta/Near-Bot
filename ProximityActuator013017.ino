// Proximity Actuator by Donovan Magryta 1/20/2017

//Shopping list: 
//NodeMCU ESP8266 Lolin V3 microcontroller: http://www.gearbest.com/transmitters-receivers-module/pp_366523.html?wid=21
//SG90 Servo Motor: http://www.gearbest.com/power/pp_235842.html?wid=21
//USB Power Bank or USB wall adapter. I bought a super thin portable power bank at the Five Below store for $5 US Dollars, but you could buy one pretty much anywhere.


//BEFORE YOU START:
//1. If you haven't already downloaded the Arduino IDE, get it for free (donation optional) at: https://www.arduino.cc/en/Main/Software
//2. open the Arduino IDE (if you aren't reading this in the Arduino IDE already!)...
//3. Go to files and click on the preference in the Arduino IDE...
//4. copy the below code in the Additional boards Manager:
//http://arduino.esp8266.com/stable/package_esp8266com_index.json
//5. click OK to close the preference tab...
//6. Go to tools and board, and then select board manager...
//7. Navigate to esp8266 by esp8266 community and install the software for Arduino...
//8. You may need to download and install the CH340 driver if you are unable to get the NodeMCU talking with your Arduino IDE: https://www.wemos.cc/downloads
//Once all the above process been completed we are read to program our esp8266 NodeMCU microcontroller with the Arduino IDE.

//You may find it important to figure out which NodeMCU version you have. Heres a comparison guide: http://frightanic.com/iot/comparison-of-esp8266-nodemcu-development-boards/
// NodeMCU v1 pinout diagram: http://cdn.frightanic.com/blog/wp-content/uploads/2015/09/esp8266-nodemcu-dev-kit-v1-pins.png
// NodeMCU v2 pinout diagram: http://cdn.frightanic.com/blog/wp-content/uploads/2015/09/esp8266-nodemcu-dev-kit-v2-pins.png
// NodeMCU v3 pinout diagram: http://cdn.frightanic.com/blog/wp-content/uploads/2015/09/esp8266-nodemcu-dev-kit-v3-pins.jpg

//Explanation of the rigs: 
//Made from NodeMCU ESP8266 microcontroller, battery or USB power supply, and SG90 Servo
//You can use a 2nd unmodified esp8266 module as a beacon hotspot AP instead of using a smartphone.


// Note lines start with  two forward slashes, and are ignored by the computers. Notes are just for us humans!
#include <ESP8266WiFi.h>
#include <SPI.h> //May be needed for serial printing.
#include <Servo.h> //Servo library
#define D0 16 //Defines pins to make assigning pins easier.
#define D1 5 // I2C Bus SCL (clock)
#define D2 4 // I2C Bus SDA (data)
#define D3 0
#define D4 2 // Same as "LED_BUILTIN", but inverted logic
#define D5 14 // SPI Bus SCK (clock)
#define D6 12 // SPI Bus MISO 
#define D7 13 // SPI Bus MOSI
#define D8 15 // SPI Bus SS (CS)
#define D9 3 // RX0 (Serial console)
#define D10 1 // TX0 (Serial console)
Servo myservo; //Create a servo object named myservo
//Phone or additional ESP8266 module set to hotspot AP mode:
const char* ssid = "ProxBeacon"; //Put your phone or beacon hotspot name inside the quotes
const char* password = "12345678910"; //Put your hotspot password inside the quotes

void setup(){
     Serial.begin(115200); //sets serial baud rate so the microcontroller can talk to the serial print interface in the Arduino IDE - You may need to change it to 9600 instead!
     myservo.attach(D0);  // attaches the servo on pin D0 aka GPIO16 to the servo object
     myservo.write(20); //moves servo arm to 10 degrees rotation 
     Serial.println("Locked");  //output the the serial monitor the word "Locked" 
     WiFi.mode(WIFI_STA); //Sets wifi to Station mode
     WiFi.begin(ssid, password); //Connects to hotspot beacon
} 

 void loop() { //The loop runs over and over again rapidly
    
    if (WiFi.status() != WL_CONNECTED) { //If wifi is NOT connected, do the following...
    Serial.println("Couldn't get a wifi connection");
    myservo.write(20); //Moves servo arm to 10 degrees 
    Serial.println("Locked");
    
    } 
  else { //If WiFi IS connected, then do the following...

  long rssi = WiFi.RSSI(); //Creates a variable named rssi and assign it to the function that returns the signal strength reading of the hotspot beacon
  Serial.print(rssi); //outputs the rssi reading to the serial monitor
   
  if (rssi > -50 && rssi < -5) { //If signal strength is stronger than -30, and weaker than -5. then do the following... 
   myservo.write(55); //Rotate servo arm to 55 degrees
   Serial.println("Unlocked");
   }
   
  else { //If the above conditions aren't met then do the following...
   myservo.write(20); //Rotates servo arm back to 10 degrees.
   Serial.println("Locked");
   }
  }
 }

