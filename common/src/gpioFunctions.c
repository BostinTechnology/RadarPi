/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include "../inc/gpioFunctions.h"
#include "../inc/rdr_gpio_control.h"



int setupGpioFunctions(void) {
	
	gpio_init();
	
	set_gpio_for_input(IF_OUT1);
	set_gpio_for_input(IF_OUT_TO_PI);
	set_gpio_for_output(SAMPLE_HOLD);

	return GPIO_ERR_NONE;
};

int setSampleHoldForRun(void) {
	
	set_gpio_value(SAMPLE_HOLD,0);
	return GPIO_ERR_NONE;
};

int setSampleHoldForHold(void) {
	
	set_gpio_value(SAMPLE_HOLD,1);
	return GPIO_ERR_NONE;
};

int returnRawFrequency(float *frequency, int measuring_pin) {
	
	float		time_period = 0.00;		// The time between state changes
	time_t		currenttime, starttime;
	int			currentstate, newstate;				// the current GPIO state
	float		timeout = (float) MAX_WAIT_TIME;
	int			completed = false;					// set to true when complete, either via timeout or trigger
    int         status;
	
	// read current state
	status = read_gpio_value(measuring_pin, &currentstate);
	
    // load the current time into the starting time
    starttime = clock(); 

	do {
        currenttime = clock();
        //printf("%ld\n", currenttime);         // debug to check it ran for the right time
		status = read_gpio_value(measuring_pin, &newstate);
		if ( newstate != currentstate) {
			// GPIO has changed state
			currentstate = newstate;
			//printf("DEBUG: GPIO has changed state\n");
			time_period = (float)(currenttime - starttime)/ CLOCKS_PER_SEC;		// Convert the number of ticks to the time
			*frequency = (1 / (time_period * 2));
			completed = true;
		};
		if (currenttime > (starttime + (timeout * CLOCKS_PER_SEC))) {
			// timeout has been reached
			//printf("DEBUG: Timeout has been reached, starting again\n");
			completed = true;
			*frequency = 0;
			starttime = clock();			// reset the timeout clock
		};
        if (status != GPIO_ERR_NONE) {
            *frequency = 0;
            completed = true;
        }
	} while (completed == false);
	
	return status;
};

int returnFullFrequency(float *frequency, int measuring_pin) {
	
	float		time_period = 0.00;		// The time between state changes
	//float		frequency = 0.00;
	time_t		currenttime, starttime, halftime;
	int			startstate, newstate;				// the current GPIO state
	float		timeout = (float) MAX_WAIT_TIME;
	int			halfcycledetected = false;					//flag to identify when the half cycle has been detected
	int			completed = false;					// set to true when complete, either via timeout or 
    int         status;
	
	//printf("DEBUG: returning Full Frequency\n");
	// read current state
	status = read_gpio_value(measuring_pin, &startstate);
	
    // load the current time into the starting time
    starttime = clock();
	halftime = 0;
	
	do {
        currenttime = clock();
        //printf("%ld\n", currenttime);         // debug to check it ran for the right time
		status = read_gpio_value(measuring_pin, &newstate);
		if ( newstate != startstate) {
			// GPIO has changed state
			usleep(FREQ_DEBOUNCE_TIME);
			status = read_gpio_value(measuring_pin, &newstate);
			if ( newstate != startstate) {
				// I've detected half a cycle after de-bounce
				//printf("DEBUG: GPIO has changed state\n");
				startstate = newstate;
				if (halfcycledetected) {
					// the state has now changed twice as i detected half a cycle beforehand
					time_period = (float)((currenttime - starttime) + halftime)/ CLOCKS_PER_SEC;		// Convert the number of ticks to the time
					*frequency = (1 / (time_period * 2));
					halfcycledetected = false;
					completed = true;
				}
				else {
					// the state has changed for the first time
					halftime = (currenttime - starttime);
					halfcycledetected = true;	
				}
				starttime = clock();				
			};
		};
		if (currenttime > (starttime + (timeout * CLOCKS_PER_SEC))) {
			// timeout has been reached
			//printf("DEBUG: Timeout has been reached\n");
			completed = true;
		};
        if (status != GPIO_ERR_NONE) {
            *frequency = 0;
            completed = true;
        }
	} while (completed == false);
	
	return status;
};
