/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   freqTest.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 15 January 2019, 18:34
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

#include "../inc/freqTest.h"
#include "../../common/inc/gpio_control.h"
#include "../../common/inc/gpioFunctions.h"
#include "../../common/inc/utilities.h"

/*!
 * functions to select gpio pin
 * then read frequency and display it.
 
 */

int chooseGPIOPin(void) {

	int		chosen_pin = 0;			// the GPIO pin selected, zero if not chosen
	char	option;
	char	manual_no[5];
	
	printf("Please choose which GPIO Pin to measure\n");
	printf("1 - IF Out1\n");
	printf("2 - IF Out to Pi\n");
	printf("3 - Manual Entry\n");
	printf("e - Return to main menu\n");
	
	option = getchar();
	switch (option)	{
		case '1':
			chosen_pin = IF_OUT1;
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

void readFrequency(void) {
	
	int			measuring_pin;			// The GPIO pin to measure
	float		time_period = 0.00;		// The time between state changes
	time_t		currenttime, starttime;
	int			currentstate, newstate;				// the current GPIO state
	float		timeout = (float) MAX_WAIT_TIME;
	
	systemloop=true;
	
	setupGpioFunctions();
	
	// menu to choose GPIO pin to read
	measuring_pin = chooseGPIOPin();
	
	// loop to show frequency
	printf("CTRL - C to end loop\n");
	
	// read current state
	currentstate = read_gpio_value(measuring_pin);
	
    // load the current time into the starting time
    starttime = clock(); 

	do {
        currenttime = clock();
        //printf("%ld\n", currenttime);         // debug to check it ran for the right time
		newstate = read_gpio_value(measuring_pin);
		if ( newstate != currentstate) {
			// GPIO has changed state
			currentstate = newstate;
			//printf("DEBUG: GPIO has changed state\n");
			time_period = (float)(currenttime - starttime)/ CLOCKS_PER_SEC;		// Convert the number of ticks to the time
			printf("Frequency:%f\n", (1 / (time_period * 2)));
			starttime = clock();
		};
		if (currenttime > (starttime + (timeout * CLOCKS_PER_SEC))) {
			// timeout has been reached
			//printf("DEBUG: Timeout has been reached, starting again\n");
			printf(".\n");
			starttime = clock();			// reset the timeout clock
		};
	} while (systemloop);
	
	return;
};
