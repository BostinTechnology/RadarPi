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
#include "../inc/systemSettings.h"
#include "../inc/ledTest.h"
#include "../inc/adcTest.h"
#include "../inc/gainTest.h"
#include "../../common/inc/utilities.h"



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
	printf("s - Test Sample & Hold Function\n");
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
	
    do {
        printf("Please select command (h for help) -> ");

        option = getchar();
        getchar();  // have to press enter and this consumes the enter character


        switch (option)
        {
            case 'f':
                /* Run Full Test Routine */

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
				setGainValue();
				break;

            case 'q':
                /* Read Frequency */
				
				break;

            case 's':
                /* Test Sample & Hold Function */
				
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
                printf("Unrecognised command!\n");
				break;
		
       }
       fflush (stdout) ;
    } while(option != 'e');
    
    return 0;
}

