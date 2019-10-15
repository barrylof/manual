# IOT Manual

## We are trying to make Herbie
Herbie is a smart device that reads the humidity in the soil of your plants. When you've just watered your plans push the button to define the ideal humidity. Once it drops below 30% of it's ideal humidity. Herbie will communicate that your plant(s) are thirsty. Not only will it show you by light and sound but it will also  make an event in your Google calendar to remind you to water your plant(s).
We are making Herbie with an ESP32 Computer

Note: This is an experiment and might not be as good as you wish


## What do we need?

Software stuff:
* The 'fastled' library in arduino (tools-> Manage libraries-> search for fastled by 'Garcia' and install)
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
