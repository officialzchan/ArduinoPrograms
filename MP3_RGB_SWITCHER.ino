//Install Adafruit_NeoPixel through Tools -> Manage Libraries
//Download DFRobotDFPlayerMini from https://github.com/DFRobot/DFRobotDFPlayerMini and copy the DFRobotDFPlayerMini-1.0.3
//to Documents/Arduino/Libraries
#include <Adafruit_NeoPixel.h>
#include <DFRobotDFPlayerMini.h>
#include "Arduino.h"
#include "SoftwareSerial.h"


//Defines button state
# define ACTIVATED LOW
//Pin the Button is wired to
int buttonNext = 2;
//Keeps track on the state of the RGB strip
boolean lightsOn = false;
//Pin the rgb is wired to
#define PIN 9
//How many LEDs there are
#define NUMPIXELS 16

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Creates the Serial and DFPlayer objects
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;


//Setup code--------------------------------------------------------------
void setup(){
  mySoftwareSerial.begin(9600);

  //Gets rid of the speaker "popping" noise on startup. Found on Arduino Forums
  myDFPlayer.begin(mySoftwareSerial, true, false);

  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  //Set volume 0-30
  myDFPlayer.volume(15); 

  //Sets up the button modes
  pinMode(buttonNext, INPUT);
  digitalWrite(buttonNext,HIGH);
  //Instantiates pixels object
  pixels.begin();
}
//--------------------------------------------------------------------------



//Code that runs constantly-------------------------------------------------
void loop(){
 //Looks for a button press
  if (digitalRead(buttonNext) == ACTIVATED){
    /Plays next soundtrack and cycles light state
    myDFPlayer.next();
    cycleLights();
    delay(1000);
  }                     
}
//--------------------------------------------------------------------------



//Turns the LEDS on/off-----------------------------------------------------
void cycleLights(){
  //If the lights are on
  if (lightsOn) {
    //Turn the lights off 
    pixels.clear();
    lightsOn = false;
  }
  //If the lights are off
  else{
    // For each pixel...
    for(int i=0; i<NUMPIXELS; i++) { 
      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      // Here we're using a moderately bright green color:
      pixels.setPixelColor(i, pixels.Color(0, 150, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }
    lightsOn = true;
  }
}
//----------------------------------------------------------------------------
