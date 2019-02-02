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



int setupGpioFunctions(void) {
	
	gpio_init();
	
	set_gpio_for_input(IF_OUT1);
	set_gpio_for_input(IF_OUT_TO_PI);
	set_gpio_for_output(SAMPLE_HOLD);

	return 0;
};

void setSampleHoldForRun(void) {
	
	set_gpio_value(SAMPLE_HOLD,0);
	return;
};

void setSampleHoldForHold(void) {
	
	set_gpio_value(SAMPLE_HOLD,1);
	return;
}

