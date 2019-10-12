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
#include "../inc/rdr_gpio_control.h"
#include "../../common/inc/rdr_utilities.h"

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
    int      status = LED_ERR_NONE;
    
	status = gpio_init();
	
    status += set_gpio_for_output(LED_RUNNING);
	status += set_gpio_for_output(LED_MONITORING);
	status += set_gpio_for_output(LED_TRIGGERED);
	
    if (status == GPIO_ERR_NONE) {
    	status += set_gpio_value(LED_RUNNING,LED_OFF);
        status += set_gpio_value(LED_MONITORING,LED_OFF);
        status += set_gpio_value(LED_TRIGGERED,LED_OFF);
	}
    if (status != GPIO_ERR_NONE) {
        status = LED_ERR_SETUP;
    };
	return status;
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
	int     status = LED_ERR_NONE;
    status = set_gpio_value(LED_RUNNING,state);
    if (status != GPIO_ERR_NONE) {
        status = LED_ERR_SET_LED_RUNNING;
    };
	return status;
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
    int     status = LED_ERR_NONE;
    status = set_gpio_value(LED_MONITORING,state);
    if (status != GPIO_ERR_NONE) {
        status = LED_ERR_SET_LED_MONITORING;
    };
	return status;
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
    int     status = LED_ERR_NONE;
    status = set_gpio_value(LED_TRIGGERED,state);
    if (status != GPIO_ERR_NONE) {
        status = LED_ERR_SET_LED_TRIGGERED;
    };
	return status;
}

int cycleLEDs(void)
{
    int status = LED_ERR_NONE;
	status = ledSetup();
    if (status != LED_ERR_NONE) {
        printf("CTRL - C to end loop\n");

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


        } while ((systemloop) && (status != LED_ERR_NONE));
    }
    if (status == LED_ERR_NONE) {
        printf("LED test completed\n");
    }
    else {
        printf("LED test failed\n");
    }
	return status;
};

