Working with a ModeMCU

You need to install the NodeMCU extensions for Arduino IDE

# Electronics:

 * works with neopixels 
 * signal on d2 (pin 4)
 * use a level shifter for 3.3V -> 5V (for the neopixels)

# Code

Change the WiFi credentials on the WifiWebServer.ino

We use the Wifi webserver from the nodeMCU to handle the beginning and end of the simulation

URLs : 
 
* /: does nothing
* /runSimulation: 
    * seconds: the duration of the dawn simulator
    * nbLeds: the number of leds that are used for the simulation (should be less than 100)
* /stopSimulation: stop the simulation and turn off the lights 
* /infos: returns stats about the current simulation
* /config: used to set different values for the simulation
* testColor: canset the strip to a specific color
   * r: the red value
   * g: the green value
   * b: the blue value

