# RadarPi

## Overview
**RadarPi** is a Raspberry Pi add on board that provides capability for a Radar module and a light
sensor. These can be used in many applications including wildlife monitoring, movement detection and
many others.

For further information refer to [Bostin Technology](https://www.bostintechnology.com)


This repository consists of a set of library functions that enable any user to interact with
the hardware on the **RadarPi** board, plus a number of sample applications to help. Below is a
breakdown of each of the various repositories. 

By default, when the repository is compiled, executables are in the */build* directory.

Due to the low level communications used, all the applications need to be run using elevated privileges.

## Licence
This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.

## How To Use
When building your own applications, include radar.h in your application to access the libraries.

When compiling it, you need to also include the following in your makefile:-
    ```
    LIBS -lbcm2835 -lm -lwiringPi
    ```

When building the visual application, you would also need to include:-
    ```
    GTKLIB =`pkg-config --cflags --libs gtk+-3.0`
    ```


## common
Contained within this folder are a number of functions to access the various parts of the **RadarPi**

Any file that begins with `rdr` are not normally required to be used as they are helper functions
for the other header files.

All the other header files can be included or used individually, but we would recommend that you use
radar.h instead. the naming convention is such that it is fairly obvious what they are used for. Each
function is further described within the associated H file. As part of our software standards, we
attempt to do the following
- have all functions return a status
- any other return value is handled as a pointer

As can be seen below, this function returns an Int as status, but also requires 2 parameters, a float
pointer to put the result in ([out]) but also which pin to use for measuring purposes.
```
/*!**************************************************************************
 * Overview: Function to return the frequency from the GPIO pins
 *  
 * Description: This method only uses half the cycle and no debounce, but is
 *				similar to readFullFrequency below.
 *				Requires setupGpioFunctions() & setSampleHoldForRun() to be run 
 *				first
 * Parameters:
 * param[out]   frequency       : A float of the frequency measured
 * param[in]	measuring_pin	: the pin to be used.
 *
 * return		status       : 0 = success
 *****************************************************************************/
int returnRawFrequency(float *frequency, int measuring_pin);
```

## radarVisual
A GUI based application that utilises teh GTK and Cairo libaries to provide a visual solution

## testProgram
A program that is used to validate the manufacturing of the boards

## sampleSoftware
Some simple routines that demonstrate some of the functionality of the **RadarPi**

## gainControl
A small program that sets the gain values of the gain device.
Note: The gain chip does *not* respond to commands, hence it is therefore write only

## digitalDetection
Uses various additional libraries to capture and then graph data from the digital signals

## analogueMeasurement
Using various additional libraries to capture and then graph data from the ADC


**Warning**
All the software within this github repository is still in development and as issues are found or
new functionality added, the repository will be amended.
At present, not all the software has been fully tested.

