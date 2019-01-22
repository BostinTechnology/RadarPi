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
#include "../inc/gpio_control.h"

/*!
 * need functions to read each of the gpio pins and return when they change state
 * 
 * Also need to drive the sample and hold pin
 */

float measureGpioDuration(int pin_no, float timeout) {
	
	time_t		currenttime, starttime;
	int			currentstate;				// the current GPIO state
	int			changed = false;
	float		duration = 0.00;			// how long it was till the state changed
	

	printf("DEBUG: Measuring the GPIO Duration\n");
	
	// read current state
	currentstate = read_gpio_value(pin_no);
	
    // load the current time into the counter
    currenttime = clock();

    starttime = currenttime; 
	
	// monitor in loop till timeout or change in state
    do {
        currenttime = clock();
        //printf("%ld\n", currenttime);         // debug to check it ran for the right time
		if (read_gpio_value(pin_no) != currentstate) {
			// GPIO has changed state
			printf("DEBUG: GPIO has changed state, exiting\n");
			changed = true;
			duration = (float)((currenttime - starttime)/ CLOCKS_PER_SEC);		// Convert the number of ticks to the time
		};
		if (currenttime < (starttime + (timeout * CLOCKS_PER_SEC))) {
			// timeout has been reached
			printf("DEBUG: Timeout has been reached, exiting\n");
			changed = true;
		}
    } while (changed == false);
	
	return duration;
};


int setupGpioFunctions(void) {
	
	gpio_init();
	
	set_gpio_for_input(IF_OUT1);
	set_gpio_for_input(IF_OUT_TO_PI);
	set_gpio_for_output(SAMPLE_HOLD);

	return 0;
};

