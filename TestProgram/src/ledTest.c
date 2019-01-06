/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ledRoutines.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 06 January 2019, 10:27
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../inc/ledTest.h"
#include "../../common/inc/ledControl.h"
#include "../../common/inc/utilities.h"

/*!**************************************************************************
 * Overview:  Cycle through the LEDs to test them
 *  
 * Description: This method turns each LED on and off in a timed cycle
 *				Requires CTRL - C to exit
 *
 * Parameters:
 * param[in] none : 
 *
 * return 0         : no error
 *****************************************************************************
 */

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
}

