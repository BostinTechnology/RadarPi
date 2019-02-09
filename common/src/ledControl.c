/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ledControl.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 08 December 2018, 20:44
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../inc/ledControl.h"
#include "../inc/gpio_control.h"
#include "../../common/inc/utilities.h"

/*!**************************************************************************
 * Overview:  Setup the LEDs for use and set them off
 *  
 * Description: This method first calls the GPIO setup and then configures
 *				the channels for output before setting them to off
 *
 * Parameters:
 * param[in/out] ?? : None 
 *
 * return 0         : no error
 *****************************************************************************
 */
int ledSetup(void)
{
	gpio_init();
	
	set_gpio_for_output(LED_RUNNING);
	set_gpio_for_output(LED_MONITORING);
	set_gpio_for_output(LED_TRIGGERED);
	
	set_gpio_value(LED_RUNNING,LED_OFF);
	set_gpio_value(LED_MONITORING,LED_OFF);
	set_gpio_value(LED_TRIGGERED,LED_OFF);
	
	return 0;
}

/*!**************************************************************************
 * Overview:  Control the Running LED, either on or off
 *  
 * Description: This method sets the running LED either on or off as requested
 *
 * Parameters:
 * param[in] state : LED_ON or LED_OFF
 *
 * return 0         : no error
 *****************************************************************************
 */

int controlRunningLED(int state)
{
	set_gpio_value(LED_RUNNING,state);
	return 0;
}


/*!**************************************************************************
 * Overview:  Control the Monitoring LED, either on or off
 *  
 * Description: This method sets the monitoring LED either on or off as requested
 *
 * Parameters:
 * param[in] state : LED_ON or LED_OFF
 *
 * return 0         : no error
 *****************************************************************************
 */

int controlMonitoringLED(int state)
{
	set_gpio_value(LED_MONITORING,state);
	return 0;
}

/*!**************************************************************************
 * Overview:  Control the Triggered LED, either on or off
 *  
 * Description: This method sets the triggered LED either on or off as requested
 *
 * Parameters:
 * param[in] state : LED_ON or LED_OFF
 *
 * return 0         : no error
 *****************************************************************************
 */

int controlTriggeredLED(int state)
{
	set_gpio_value(LED_TRIGGERED,state);
	return 0;
}

int cycleLEDs(void)
{

	ledSetup();
	printf("CTRL - C to end loop\n");

	do {
		printf("Running LED\n");
		controlTriggeredLED(LED_OFF);
		controlRunningLED(LED_ON);
		usleep(LED_TEST_SPEED);

		printf("Monitoring LED\n");
		controlRunningLED(LED_OFF);
		controlMonitoringLED(LED_ON);
		usleep(LED_TEST_SPEED);

		printf("Triggered LED\n");
		controlMonitoringLED(LED_OFF);
		controlTriggeredLED(LED_ON);
		usleep(LED_TEST_SPEED);
		
		
	} while (systemloop);

	printf("LED test completed\n");
	return 0;
};

