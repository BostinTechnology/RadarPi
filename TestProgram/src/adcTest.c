/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include "../inc/adcTest.h"
#include "../../common/inc/utilities.h"
#include "../../common/inc/adcFunctions.h"


int cycleADCReadings(void)
{
	float adc_value;

	systemloop=true;				//reset the loop to true to start
	
	adcSPiInitialisation();

	
	printf("Reading ADC Values\n");
	printf("CTRL - C to end loop\n");

	do {
		adc_value = readVoltage();
		printf("ADC Readings:%f\n", adc_value);
		usleep(ADC_READING_TEST_SPEED);
		
	} while (systemloop);

	printf("ADC test completed\n");
	
	adcSPiEnd();
	
	return 0;
}

