// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.

/************************** Configuration ***********************************/

// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"
#include "esp32-hal-adc.h"
#include <FastLED.h>
#define DATA_PIN     4
#define BRIGHTNESS  64
#define NUM_LEDS    10
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int vochtSensorpin = 1; //Select the entry on your ESP32 for the humiditysensor
int vochtWaarde = 0; // variable to save the data of the humiditysensor
int ingesteld;  // variable to determine the ideal amount of humidity in the plant pot

/************************ Example Starts Here *******************************/
// set up the 'analog' feed
AdafruitIO_Feed *analog = io.feed("Level");

void setup() {
//This let's us manipulate the color of the ledstrip    
FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  
  Serial.begin(115200);
     // wait for serial monitor to open
  while(! Serial);
  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  }

void loop() {

  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  // Adafruit IO is rate limited for publishing, so a delay is required in
  // between feed->save events. In this example, we will wait three seconds
  // (1000 milliseconds == 1 second) during each loop.
  delay(3000);
  
//  Serial.println(teller1); 

// this variable reads the button sensor from port 9 on your ESP32
int knopWaarde = digitalRead (9);  

Serial.println(knopWaarde);

//This variable reads the analog sensor data from port 1 on your ESP32
vochtWaarde = analogRead(vochtSensorpin); 
//uncomment the codeline below (and uncomment the second last codeline in this sketch) to check if it works when you don't have a button. Led should appear blue and NOT send data to adafruit when vochtwaarde is between 110-1000, and ledstrip will appear red and send data to adafruit when vochtWaarde is below 110.
//vochtWaarde = 110;
Serial.print("Vochtigheid aarde is "); Serial.println(vochtWaarde);


//hieronder standaard licht uit wanneer niks is ingesteld // here the lights are off when not
for(int i = 0 ; i< NUM_LEDS; i++) {
    leds[i] = CRGB::Black;}
  FastLED.show();

// Below is the state when the button is pushed to set ideal humidity state, ideal state being 100% humidity
if (knopWaarde == 0){
ingesteld = vochtWaarde;

// below empty state: when there is no humidity detected which is below 10 - leds will be off as there is no humidity detected
if (ingesteld < 10){
  vochtWaarde =0;
  for(int i = 0 ; i< NUM_LEDS; i++) {
    leds[i] = CRGB::Black;}
  FastLED.show();  
}

// below is when there is humidity detected which is above 10 - ledstrip will color blue (feedback) as we just set an ideal humidity value above 10
else if (ingesteld >10){
  for(int i = 0 ; i< NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;}
  FastLED.show();
  
}
}

//below you find the state when the button is not pushed in
else if (knopWaarde == 1){
//below you see the formula that says if the humidity drops below 10% of the ideal humidity, the ledstrip will color red indicating the plant is in need of water, we send this data to adafruit
   if (vochtWaarde < ingesteld/100*10){
for(int i = 0 ; i< NUM_LEDS; i++) {
    leds[i] = CRGB::Green;} //somehow sayin green makes the led go red
  FastLED.show();
  Serial.print("sending -> ");
  Serial.println(vochtWaarde);
  analog->save(vochtWaarde); //we send the data to adafruit here, which will make zapier create a Google Calendar event to water my plant in the evening
  
}

//below here another empty state for when the button is not pushed anymore and there is no humidity detected, leds go off
else if (ingesteld < 10){
 for(int i = 0 ; i< NUM_LEDS; i++) {
    leds[i] = CRGB::Black;}
  FastLED.show();
 }
  
  else if (ingesteld > ingesteld/100*10){
  //below you see the formula that says if the humidity still has the ideal value (between 10-100%, the ledstrip will color blue indicating the plant is ok, we send this data to adafruit
for(int i = 0 ; i< NUM_LEDS; i++) {
    leds[i] = CRGB::Blue;
    }
  FastLED.show();
   
}
}
ingesteld = 1000;
delay (50);
}
