/* 
 * File:   mainSampleSoftware.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 10 February 2019, 20:32
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "../inc/mainSampleSoftware.h"
#include "../../common/inc/ledControl.h"
#include "../../common/inc/gainFunctions.h"
#include "../../common/inc/gpioFunctions.h"
#include "../../common/inc/utilities.h"
#include "../../common/inc/adcFunctions.h"

/*!**************************************************************************
 * Overview:  Display the Bostin Technology introduction screen
 *  
 * Description: This method displays the splash screen
 *
 * Parameters:
 * param[in/out] ?? : None 
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
void splashScreen(void)
{
    printf("\n***********************************************\n");
    printf("*             Bostin Technology               *\n");
    printf("*                                             *\n");
    printf("*                  Radar Pi                   *\n");
	printf("*                                             *\n");
    printf("*           Sample User Software              *\n");
    printf("*                                             *\n");
    printf("*        for more info www.cognIoT.eu         *\n");
    printf("***********************************************\n");
	usleep(1000000);
    return;
};

void helpScreen(void)
{
	printf(" \n\n");
	printf("**************************************************************************\n");
	printf("Available commands: -\n\n");
	printf("d - Digital Detection (Filtered)\n");
	printf("D - Digital Detection (Raw)\n");
	printf("c - ADC measurement\n");
	printf("h - Display the help screen\n");
	printf("e - Exit program \n");
	printf("\n");
	return;
};

void digitalDetectionFiltered(void) {
	
	float	freq;
	time_t	trigger_time, trigger_timeout;
	
	trigger_timeout = (TRIGGER_TIMEOUT * CLOCKS_PER_SEC);
	systemloop = true;
	
	printf("Running Detection Filtered mode\n");
	printf("CTRL - C to exit");
	// In a loop, using systemloop to exit
	do {
		// Read the whole frequency, using the deglitch s/w it and then report it
		freq = returnFullFrequency(IF_OUT_TO_PI);

		// If over a threshold, turn the LED on, recording the on time
		if (freq > FREQUENCY_TRIGGER) {
			// frequency threshold has been exceeded, set trigger time.
			trigger_time = clock();
			printf("Triggered\n");
			if (trigger_time == 0 ) {
				// we are not currently triggered, so turn the light on
				controlTriggeredLED(LED_ON);
				controlRunningLED(LED_OFF);
			}
			else {
				// currently triggered, flash the LEDs off then on
				controlTriggeredLED(LED_OFF);
				controlRunningLED(LED_ON);
				usleep(50000);
				controlTriggeredLED(LED_ON);
				controlRunningLED(LED_OFF);			
			}
		};

		// After a period, turn off the LED
		if (clock() > (trigger_time + trigger_timeout)) {
			// timeout has now been exceeded
			printf("Monitoring\n");
			controlTriggeredLED(LED_OFF);
			controlRunningLED(LED_ON);
			trigger_time = 0;
		};
	} while (systemloop);
	//
};

void digitalDetectionRaw(void) {
	float	freq;

	systemloop = true;
	
	printf("Running Detection Filtered mode\n");
	printf("CTRL - C to exit");
	// In a loop, using systemloop to exit
	do {
		// Read the whole frequency, using the deglitch s/w it and then report it
		freq = returnFullFrequency(IF_OUT_TO_PI);

		// If over a threshold, turn the LED on, recording the on time
		if (freq > FREQUENCY_TRIGGER) {
			// frequency threshold has been exceeded, set trigger time.
			printf("Triggered\n");
			// Triggered, so turn the light on
			controlTriggeredLED(LED_ON);
			controlRunningLED(LED_OFF);
		} 
		else {
			printf("Monitoring\n");
			controlTriggeredLED(LED_OFF);
			controlRunningLED(LED_ON);
		};
	} while (systemloop);
	//	
};

void adcMeasurement(void) {
		
	float	volts;
	time_t	trigger_time, trigger_timeout;
	
	trigger_timeout = (TRIGGER_TIMEOUT * CLOCKS_PER_SEC);
	systemloop = true;
	
	printf("Running ADC Measurement Filtered mode\n");
	// setup comms for the ADC chip
	adcSPiInitialisation();
	printf("CTRL - C to exit");
	// In a loop, using systemloop to exit
	do {
		// Read the voltage and then report it
		volts = readVoltage();

		// If over a threshold, turn the LED on, recording the on time
		if (volts > VOLTAGE_TRIGGER) {
			// frequency threshold has been exceeded, set trigger time.
			trigger_time = clock();
			printf("Triggered\n");
			if (trigger_time == 0 ) {
				// we are not currently triggered, so turn the light on
				controlTriggeredLED(LED_ON);
				controlRunningLED(LED_OFF);
			}
			else {
				// currently triggered, flash the LEDs off then on
				controlTriggeredLED(LED_OFF);
				controlRunningLED(LED_ON);
				usleep(50000);
				controlTriggeredLED(LED_ON);
				controlRunningLED(LED_OFF);			
			}
		};

		// After a period, turn off the LED
		if (clock() > (trigger_time + trigger_timeout)) {
			// timeout has now been exceeded
			printf("Monitoring\n");
			controlTriggeredLED(LED_OFF);
			controlRunningLED(LED_ON);
			trigger_time = 0;
		};
	} while (systemloop);
	//
	adcSPiEnd();
};

int main(int argc, char** argv) {
	char option;                        // Used for menu choices

	// setup the interrupt handling
	sigSetup();
	setupGpioFunctions();
		
	splashScreen();
	
    // main menu
	helpScreen();
	
	//set the default gain
	setGainDefaultValue();
	
	// Set the Sample and Hold pin for running
	setSampleHoldForRun();
	
    do {
        printf("Please select command (h for help) -> ");

        option = getchar();
        getchar();  // have to press enter and this consumes the enter character


        switch (option)
        {
            case 'd':
                /* Run Full Test Routine */
				digitalDetectionFiltered();
                break;

            case 'D':
                /* Full Test Routine Continuously on a loop */
				digitalDetectionRaw();
				break;

            case 'c':
                /* Test the LEDs */
				adcMeasurement();
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
	
	return (EXIT_SUCCESS);
}

