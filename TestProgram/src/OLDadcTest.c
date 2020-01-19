/* 
 * File:   adcTest.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 12 January 2019, 08:55
 * 
 * Example code to support the test program with its ADC tests
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "../inc/adcTest.h"
#include "../../common/inc/rdr_utilities.h"
#include "../../common/inc/adcFunctions.h"



int cycleADCReadings(void)
{
	float adc_value;
    int     status;
    
	systemloop=true;				//reset the loop to true to start
	
	adcSPiInitialisation();

	
	printf("Reading ADC Values\n");
	printf("CTRL - C to end loop\n");

	do {
		status = readVoltage(&adc_value);
        if (status == EXIT_SUCCESS) {
    		printf("ADC Readings:%f\n", adc_value);
        	usleep(ADC_READING_TEST_SPEED);
        }
        else {
            systemloop = false;
        }
		
	} while (systemloop);

	printf("ADC test completed\n");
	
	adcSPiEnd();
	
	return 0;
}

