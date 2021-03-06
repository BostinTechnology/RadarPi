/* 
 * File:   newfile.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 21 September 2019, 10:19
 * 
 * Example code for setting the gain control via a menu choice
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */

 /**********************************************************************
  * Development Notes
  *
  * This is a write-only interface, no data is returned
  *
  * Initial Comms by bringing CS low, clock in on the rising edge
  * Requires Clock Polarity (CPOL) = 0 & Clock Phase (CPHA) = 0
  *     MAX Clock Frequency is 5MHz
  *
  * CS Pin is connected to CE1
  *
  * Data is written LSB First
  * 
  * Format for the Gain Register
  *
  * D7   D6   D5   D4  D3  D2  D1  D0
  * SHDN MEAS  X   G3  G2  G1  G0  SEL=1 
  *
  * SHDN is set to 0 for normal operation
  * MEAS is set to 0 for normal operation
  * G3-0 are set to 0b0001 for a gain of 10
  * SEL is set to 1 for Gain Register
  * 
  */


/*
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <bcm2835.h>        // hardware definition library file
#include <time.h>           // to enable time functions

#include "../../common/inc/radar.h"

// Creates a dataset that includes a voltage float value and a time based time value
struct readings {
    int     element;
    float   voltage;
    time_t  readtime;
} ;

/*!
 *****************************************************************************
 * Overview:  Display the Bostin Technology introduction screen
 *  
 * This method displays the splash screen
 *
 * param[in/out] ?? : None 
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
int splashscreen(void)
{
    printf("\n***********************************************\n");
    printf("*             Bostin Technology               *\n");
    printf("*                                             *\n");
    printf("*                  RadarPi                    *\n");
    printf("*           Gain Control Setting              *\n");
    printf("*                                             *\n");
    printf("*        for more info www.cognIoT.eu         *\n");
    printf("***********************************************\n");
    return (0);
}



/******************************************************************************
 *
 * Main Entry function
 *
 * ***************************************************************************/

int main(int argc, char** argv) {

    int chosen = 0;
    
    // main menu

    printf(" \n\n");
    printf("**************************************************************************\n");
    printf("Setting Gain Control \n\n");

    do {
        chosen = selectGainValueMenu();
    
    } while (chosen != 99);
    
    return 0;
}
