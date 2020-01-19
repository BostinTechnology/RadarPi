/* 
 * File:   mainTestProgram.c
 * 
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 08 December 2018, 19:15
 * 
 * Example code for testing the manufacturing of the Radar Pi
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */
 
 /*!****************************************************************************
  * Test Program Requirements - Defined 10/01/20
  * 
  * Test Routine
  *     Test the LEDS, cycle through each to confirm functionality              DONE
  *         CTRL-C to continue with test
  *     For each gain value, display the readings below
  *         Light Sensor Value, ADC Output, Digital Frequency, Gain Setting
  *         Flash the LED to indicate Gain change
  *     	CTRL-C to move to next part of the test
  *     Write to and read from the E2PROMS
  *         The one on the Light Sensor
  *         The one on the HAT
  *         Auto Move to next step
  *     Range Test
  *         For each gain value, flash LED When Sensed
  *         CTRL-C to move to the next part of the test
  * 
  * Need to capture data for each test and write it to a file with identifier
  * 
  ******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "../inc/utilities.h"
#include "../inc/mainTestProgram.h"
#include "../../common/inc/radar.h"

void splashScreen(void) {
    printf("\n***********************************************\n");
    printf("*             Bostin Technology               *\n");
    printf("*                                             *\n");
    printf("*                  Radar Pi                   *\n");
    printf("*                                             *\n");
    printf("*          Production Test Routine            *\n");
    printf("*                                             *\n");
    printf("*        for more info www.cognIoT.eu         *\n");
    printf("***********************************************\n");
    return;
}

void helpScreen(void) {
        printf(" \n\n");
        printf("**************************************************************************\n");
        printf("Available commands: -\n\n");
        printf("f - Run Full Test Routine\n");
        printf("l - LED Test\n");
        printf("2 - E2PROM Test\n");
        printf("d - Display readings Test\n");
        printf("r - Range Test\n");
        printf("h - Display the help screen\n");
        printf("e - Exit program \n");
        printf("\n");
        return;
}

void fullTestRoutine(void) {
    printf("To Be implemented\n");
    
    return;
    
}

void cycleLEDs(void) {

    int status = LED_ERR_NONE;
    char        option[2];
    
    systemloop = true;
	status = ledSetup();
    if (status == LED_ERR_NONE) {
        printf("CTRL - C to end loop\n");
        controlTriggeredLED(LED_OFF);
        controlRunningLED(LED_OFF);
        controlMonitoringLED(LED_OFF);

        do {
            printf("Running LED\n");
            status += controlTriggeredLED(LED_OFF);
            status += controlRunningLED(LED_ON);
            usleep(LED_TEST_SPEED);

            printf("Monitoring LED\n");
            status += controlRunningLED(LED_OFF);
            status += controlMonitoringLED(LED_ON);
            usleep(LED_TEST_SPEED);

            printf("Triggered LED\n");
            status += controlMonitoringLED(LED_OFF);
            status += controlTriggeredLED(LED_ON);
            usleep(LED_TEST_SPEED);


        } while ((systemloop) && (status == LED_ERR_NONE));
    }
    if (status == LED_ERR_NONE) {
        printf("Did all three LEDs work correctly (y/n)? -> ");

        option[0] = getchar();
        getchar();  // have to press enter and this consumes the enter character
        if (strncmp(option,"y",1) == 0) {
            printf("LED test passed\n");
        }
        else {
            printf("LED test FAILED\n");
        }            
        controlTriggeredLED(LED_OFF);
        controlRunningLED(LED_OFF);
        controlMonitoringLED(LED_OFF);
    }
    else {
        printf("LED test FAILED\n");
    }
	return;
};


void e2promTest(void) {
    printf("To Be implemented\n");
    
    return;
    
}

void displayReadingsTest(void) {
    printf("To Be implemented\n");
    
    return;
    
}

void rangeTest(void) {
    printf("To Be implemented\n");
    
    return;
    
}

int main(int argc, char** argv) {

    char option;                        // Used for menu choices

    // setup the interrupt handling
    sigSetup();

    splashScreen();

    // main menu
    helpScreen();

    //set the default gain
    setGainDefaultValue();

    do {
        printf("Please select command (h for help) -> ");

        option = getchar();
        getchar();  // have to press enter and this consumes the enter character

        switch (option)
        {
            case 'f':
                /* Run Full Test Routine */
                fullTestRoutine();
                break;
            case 'l':
                /* LED Test */
                cycleLEDs();
                break;

            case '2':
                /* E2PROM Test */
                e2promTest();
                break;

            case 'd':
                /* Display readings Test */
                displayReadingsTest();
                break;

            case 'r':
                /* Range Test */
                rangeTest();
                break;

            case 'h':
                /* Display the help screen */
                helpScreen();
                break;

            case 'e':
                printf("Exiting.......\n");
                option = 'e';
                break;

            default:
                printf("Unrecognised command!:>%c<\n", option);
                break;
                
       }
       fflush (stdin) ;
        printf("\n");
    } while(option != 'e');
    
    return 0;
}

