# IOT Manual

## We are trying to make Herbie
Herbie is a smart device that reads the humidity in the soil of your plants. When you've just watered your plans push the button to define the ideal humidity. Once it drops below 30% of it's ideal humidity. Herbie will communicate that your plant(s) are thirsty. Not only will it show you by light but it will also  make an event in your Google calendar to remind you to water your plant(s).
We are making Herbie with an ESP32 Computer

Note: This is an experiment and might not be as good as you wish, it's my first time working with an ESP32 board in arduino


## What do we need?

Software stuff:
* Arduino
* The 'fastled' library in arduino (tools-> Manage libraries-> search 'fastled' by 'Garcia' and install)
* Adafruit_IO library (Also to find in tools->Manage libraries)
* Adafruit_IO account (Make sure to get your username and key)
* Zapier account
* Any account that you synchronized your google calendar with

Hardware stuff:
* A button
* A humidity sensor
* Ledstrip ( I'm using a WS2811 - with 10 ledlights on it)
* ESP32

## Let's go!

### Setting up (4 steps)

1. Make sure to download the Fastled Library developed by Garcia. Open arduino go to Tool->Manage libraries and type 'fastled' and install the latest version. We need this in order to make the ledstrip work on the ESP32 (NEOpixel won't work with it, at least not with me).
Do the same for the 'arduino_IO' library (this enables us to use example sketches we need to send data to adafruit & zapier)
![](https://github.com/barrylof/manual/blob/master/images/Library1-01.png)

2. [Make an account on Zapier.com](https://zapier.com/app/dashboard)
3. [Make an account on Adafruit.com](https://www.adafruit.com/)
4. Make new dashboard at [adafruit IO](https://io.adafruit.com) and Create new 'linechart' block/feed (I named it 'Level')

### Start coding

First things first, we need to use an exaple provided by the adafruit_IO library. The example we are looking for is the top one called 'adafruitio_00_publish'. Go to files->examples and search Adafruit IO Arduino. See below
![](https://github.com/barrylof/manual/blob/master/images/examplepubleish-01.png)


Now it's time to include the fastled library, fastled provides us to use simple code to light up the ledstrip. 
This code is what I standard use to make ledstrip work. 
Insert:
```C
#include <FastLED.h>
#define DATA_PIN     4
#define BRIGHTNESS  64
#define NUM_LEDS    10
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
```
Now let's make sure the rest of our inputs and outputs are defined in arduino as well. (make sure that this step's and the previous step's code is written before the `void setup(){}` code  

```C
int vochtSensorpin = 1; //Select the entry on your ESP32 for the humiditysensor
int vochtWaarde = 0; // variable to save the data of the humiditysensor
int ingesteld;  // variable to determine the ideal amount of humidity in the plant pot
```
Make sure you set up your Adafruit feed - We will send our humidity data to adafruit
```C // set up the 'analog' feed
AdafruitIO_Feed *analog = io.feed("Level");
```
And delete the following code
```C
// this int will hold the current count for our sketch
int count = 0;

// set up the 'counter' feed
AdafruitIO_Feed *counter = io.feed("counter");
```
Now let's make the ` void setup(){}` complete by adding this line of code that let's us manipulate the ledlight to our wishes 
```C
       FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
```
We don't need to alter anything else here.

Now we are going to fill the ```void loop(){}```. I provided all the code with comments that tell what each chunk of code executes and what it's purpose is. Copy and paste the following code in the loop section

```C
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
//**uncomment the codeline below (and uncomment the second last codeline in this sketch marked with two**) to check if it works when you don't have a button. Led should appear blue and NOT send data to adafruit when vochtwaarde is between 110-1000, and ledstrip will appear red and send data to adafruit when vochtWaarde is below 110.
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
//**uncomment the line below along for the check i indicated earlier in this sketch. Marked with two**
//ingesteld = 1000;
delay (50);
```
Now there are two more steps to do before the code will work properly. 
These are:
1. configure your wifi and adafruit connection correctly (let's us send data from the ESP32 to adafruit)
2. Connect zapier to the correct feed



