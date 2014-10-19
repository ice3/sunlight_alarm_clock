sunlight_alarm_clock
====================

A sunlight simulator for an arduino, with a RGB led strip. 



# Bill of Material

 * An arduino or atmega 328p flashed with arduino bootloader
 * Some led strip, the project was done useing a 12V RGB led strip
 * Some transistor to drive the led power
 * A real time clock

# Software
 
 * Arduino makefile (command line tool chain to compile and flash arduino)
 * Python with pyserial

# Aim of the project 

Light is important to wake you up correctly, when winter is coming, we usually wake up before the sun is shinning. So we use an arduino to fake the sunlight. 

The project thus use some RGB led to have the color we want and a Real Time Clock to start the light at the interesting time of the day. 

The final step of the project is to use an android app sniffing the alarm clock time to communicate with the arduino by bluetooth and get rid of the RTC.

# Calibration of the color

We can change the RGB led color using 3 PWM, but on low cost hardware we don't know the light emiting power of each color.

You can use the simple calibration light python and arduino files to try by yourself. 

The arduino program only listen for R,G,B values on it's serial port and the python program shows 3 sliders to set the value of each color channel. Change the sliders values until you get the same luminosity on each color. 
