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
#define LED_PIN     2
#define BRIGHTNESS  64
#define NUM_LEDS    10
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
```
Now let's make sure the rest of our inputs and outputs are defined in arduino as well. (make sure that this step's and the previous step's code is written before the `void setup(){}` code  

```C
#include <elapsedMillis.h>
elapsedMillis teller1;
elapsedMillis teller2; 

int piezoPin = D8;
int vochtSensorpin = A0; //Select the entry on your ESP32 of the humiditysensor
int vochtWaarde =0; // variable to save the data of the humiditysensor
int ingesteld;  // variable to determine the ideal amount of humidity in the plant pot
```
Make sure you set up your Adafruit feed - We will send our humidity data to adafruit
```C // set up the 'analog' feed
AdafruitIO_Feed *analog = io.feed("Level");
```
And delete ```C
// this int will hold the current count for our sketch
int count = 0;

// set up the 'counter' feed
AdafruitIO_Feed *counter = io.feed("counter");
```



