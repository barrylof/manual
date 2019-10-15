# IOT Manual

## We are trying to make Herbie
Herbie is a smart device that reads the humidity in the soil of your plants. When you've just watered your plans push the button to define the ideal humidity. Once it drops below 30% of it's ideal humidity. Herbie will communicate that your plant(s) are thirsty. Not only will it show you by light and sound but it will also  make an event in your Google calendar to remind you to water your plant(s).
We are making Herbie with an ESP32 Computer

Note: This is an experiment and might not be as good as you wish, it's my first time working with an ESP32 board


## What do we need?

Software stuff:
* The 'fastled' library in arduino (tools-> Manage libraries-> search 'fastled' by 'Garcia' and install)
* Adafruit_IO library (Also to find in tools->Manage libraries)
* Adafruit_IO account (Make sure to get your username and key)
* Zapier
* Any account that you synchronized your google calendar with

Hardware stuff:
* A button
* A piezo buzzer (for audio)
* A humidity sensor
* Ledstrip ( I'm using a WS2811 - with 10 ledlights on it)
* Infrared moving sensor
* ESP32

## Setting up (3 steps)

1. Make sure to download the Fastled Library developed by Garcia. Open arduino go to Tool->Manage libraries and type 'fastled' and install the latest version. We need this in order to make the ledstrip work on the ESP32 (NEOpixel won't work with it, at least not with me).
Do the same for the 'arduino_IO' library (this enables us to use example sketches we need to send data to adafruit & zapier)
![](https://github.com/barrylof/manual/blob/master/images/Library1-01.png)

2. [Make an account on Zapier.com](https://zapier.com/app/dashboard)
3. [Make an account on Adafruit.com](https://www.adafruit.com/)
