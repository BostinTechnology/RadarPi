/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mainTestProgram.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 08 December 2018, 19:15
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "../inc/mainTestProgram.h"
#include "../inc/adcTest.h"
#include "../../common/inc/ledControl.h"
#include "../../common/inc/utilities.h"
#include "../../common/inc/gainFunctions.h"
#include "../../common/inc/gpioFunctions.h"
#include "../../common/inc/adcFunctions.h"
#include "../../common/inc/gpio_control.h"

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
	
	int testgainvalues[4][2] = { {0b0000, 1}, {0b0001, 10}, {0b0100, 40}, {0b1000, 157}	};
	
	printf("Ensure the input is set to %dHz and press enter to start", INPUT_FREQUENCY);
	getchar();
	
	setupGpioFunctions();
	
	//printf("DEBUG: starting test\n");
	starttime = clock();
	do {
		
		freq = returnFullFrequency(IF_OUT_TO_PI);
		printf("Frequency Read:%f\n", freq);
		if (((freq + (freq * FREQ_TOLERANCE)) < INPUT_FREQUENCY) &&
				((freq - (freq * FREQ_TOLERANCE)) > INPUT_FREQUENCY)) {
			test_passed = true;
			printf("'\n\nFrequency read is within tolerance\n");
		}
		
	} while ((test_passed == false) && (systemloop));
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
			measured_v = readVoltage();
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

