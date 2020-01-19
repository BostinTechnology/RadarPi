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
  * Screen Output to be
  * 	Light Sensor Value, ADC Output, Digital Frequency, Gain Setting
  * 
  * Test Routine
  *     Test the LEDS, cycle through each to confirm functionality
  *         CTRL-C to continue with test
  * 	For each gain value, display the readings above for 5 seconds
  * 		CTRL-C to move to next part of the test
  * 	Write to and read from the E2PROMS
  * 		The one on the Light Sensor
  * 		The one on the HAT
  * 	Range Test
  *         For each gain value, flash LED When Sensed
  *         CTRL-C to move to the next part of the test
  * 
  ******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../inc/adcTest.h"
#include "../inc/utilities.h"
#include "../inc/mainTestProgram.h"
#include "../../common/inc/radar.h"


/*!**************************************************************************
 * Overview: Menu function for user selection of the GPIO pin
 *  
 * Description: This method provides the user with a menu of choice to choose
 *				which GPIO pin is to be measured
 *
 * Parameters:
 * param[in]	none	: 
 *
 * return		gpio_pin    : GPIO pin
 *				0			: zero if no pin selected
 *****************************************************************************/

int chooseGPIOPin(void) {

	int		chosen_pin = 0;			// the GPIO pin selected, zero if not chosen
	char	option;
	char	manual_no[5];
	
	printf("Please choose which GPIO Pin to measure\n");
	printf("1 - Digital Signal\n");
	printf("2 - O/P to Pi (with Gain)\n");
	printf("3 - Manual Entry\n");
	printf("e - Return to main menu\n");
	
	option = getchar();
	switch (option)	{
		case '1':
			chosen_pin = IF_OUT_DIGITAL;
			break;
		case '2':
			chosen_pin = IF_OUT_TO_PI;
			break;
		case '3':
			printf("Please enter the GPIO number:\n");
			fgets(manual_no, 5, stdin);
			chosen_pin = atoi(manual_no);
			break;
		case 'e':
			chosen_pin=0;
			break;
	};
	return chosen_pin;
};



//ToDo: Need to change this routine so that it calls other functions and not the low level ones.


/*!**************************************************************************
 * Overview: Function to read the frequency from the GPIO pins
 *  
 * Description: This method first calls the menu choice and then measures the
 *				time and displays the frequency determined.
 *				Note: The method waits for the whole cycle to be competed before 
 *				returning the frequency.
 *
 * Parameters:
 * param[in]	none	: 
 *
 * return		0       : nothing
 *****************************************************************************/
void readFullFrequency(void) {
	
	int			measuring_pin;			// The GPIO pin to measure
	float		frequency = 0.00;		// The time between state changes
	
	systemloop=true;
	
	setupGpioFunctions();
	
	setSampleHoldForRun();
	
	// menu to choose GPIO pin to read
	measuring_pin = chooseGPIOPin();
	
	// loop to show frequency
	printf("CTRL - C to end loop (Full Freq)\n");
	

	do {
        frequency = returnFullFrequency(&frequency, measuring_pin);
					
        printf("Frequency:%f\n", frequency);

	} while (systemloop);
	
	printf("Frequency Measuring completed.\n");
	
	return;
};




/*!**************************************************************************
 * Overview:  Perform the full test routine
 *  
 * Description: This method runs through the full test cycle
 * 
 *		Feed in a fixed signal into the radar pins and perform the following
 *		tests.
 *			Check frequency matches what is input.
 * 
 *			Check peak voltage via ADC also 
 *			repeat with different gain values, 1, 10, 80 and 157
 *
 * Parameters:
 * param[in/out] ?? : None 
 *
 * return NOTHING         : No response
 *****************************************************************************/
void fullTestRoutine(void) {
	
	int		test_passed = false;
	float	freq = 0.00, test_voltage = 0.00;
	float	measured_v, max_v;
	time_t	currenttime, starttime;
	int		qtygainvalues = 4;
	//int		testgainvalues[qtygainvalues][2];
	int		test_counter;
    int     status;
	
	int testgainvalues[4][2] = { {0b0000, 1}, {0b0001, 10}, {0b0100, 40}, {0b1000, 157}	};
	
	printf("Ensure the input is set to %dHz and press enter to start", INPUT_FREQUENCY);
	getchar();
	
	setupGpioFunctions();
	
	//printf("DEBUG: starting test\n");
	starttime = clock();
	do {
		
		status = returnFullFrequency(&freq, IF_OUT_TO_PI);
		printf("Frequency Read:%f\n", freq);
		if (((freq + (freq * FREQ_TOLERANCE)) < INPUT_FREQUENCY) &&
				((freq - (freq * FREQ_TOLERANCE)) > INPUT_FREQUENCY)) {
			test_passed = true;
			printf("'\n\nFrequency read is within tolerance\n");
		}
		
	} while (((test_passed == false) && (systemloop)) || (status !=0));
	printf("Frequency test result:%d\n", test_passed);
	
	// ADC test
	test_counter = 0;
	test_passed = true;
	systemloop = true;
	do {
		// Set the gain to the initial value
		setGainControl(testgainvalues[test_counter][0]);

		// Run in a loop for a short time to measure the maximum voltage measured
		starttime = clock();
		do {
			status = readVoltage(&measured_v);
			if (measured_v > max_v) {
				max_v = measured_v;
				starttime = clock();
			}
			currenttime = clock();

		} while (currenttime < (starttime + (TEST_TIMEOUT * CLOCKS_PER_SEC)));
		printf("DEBUG: Max Voltage:%f\n", max_v);
		
		test_voltage = INPUT_VOLTAGE * testgainvalues[test_counter][1];
		if (test_voltage > 3.3) {
			// maximum returned value is 3v3.
			test_voltage = 3.3;
		}
		if (((max_v + (max_v * VOLT_TOLERANCE)) < test_voltage) &&
					((max_v - (max_v * VOLT_TOLERANCE)) > test_voltage)) {
			// this is within tolerance & therefore passed at this gain level
			test_passed = test_passed && true;
			printf("DEBUG: Phase passed\n");
		}
		else {
			// it is out of tolerance and therefore failed at this level.
			test_passed = test_passed && false;
			printf("DEBUG: Phase failed\n");
		};
		test_counter ++;
		
	} while ((test_counter < qtygainvalues) && (systemloop));
	printf("Gain Test Result:%d\n", test_passed);
	
};

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
    printf("*        for more info www.cognIoT.eu         *\n");
    printf("***********************************************\n");
    return;
}

/*!**************************************************************************
 * Overview:  Display the help screen and menu options
 *  
 * Description: This method displays the menu options screen
 *
 * Parameters:
 * param[in/out] ?? : None 
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
void helpScreen(void)
{
	printf(" \n\n");
	printf("**************************************************************************\n");
	printf("Available commands: -\n\n");
	printf("f - Run Full Test Routine\n");
	printf("c - Full Test Routine Continuously on a loop\n");
	printf("l - Test the LEDs\n");
	printf("a - Read ADC Output\n");
	printf("g - Set Gain Control\n");
	printf("q - Read Frequency\n");
	printf("h - Display the help screen\n");
	printf("e - Exit program \n");
	printf("\n");
	return;
}

/*!****************************************************************************
 * Overview:  The Main Entry routine containing the menu 
 *  
 * Description: This method displays the menu options and manages the user entry
 *
 * Parameters:
 * param[in/out] ?? : None 
 *
 * return exit code     : 0 when complete, error code otherwise
 * ***************************************************************************/

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

            case 'c':
                /* Full Test Routine Continuously on a loop */
				
				break;

            case 'l':
                /* Test the LEDs */
				cycleLEDs();
				break;

            case 'a':
                /* Read ADC Output */
				cycleADCReadings();
				break;

            case 'g':
                /* Set Gain Control */
				selectGainValueMenu();
				break;

            case 'q':
                /* Read Frequency */
				readFullFrequency();
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

