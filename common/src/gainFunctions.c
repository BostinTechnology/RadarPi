 /* 
 * File:   gainFunctions.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 12 January 2019, 21:03
 * 
 * Example code to provide the functions to set the gain, including comms
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/gainFunctions.h"

struct GAIN_DEFINITION gainValues[qtyGainValues] = {
/*! Gain Settings for G3:G0
 *  gainValues is a 2 dimensional array that contains the setting and corresponding gain value
					G3:G0		GAIN (V/V)		SLEW RATE (V/μs)	SMALL-SIGNAL BANDWIDTH (MHz)*/
	{"GAIN_1",		0b0000, 	1},					//2.90				2.15
	{"GAIN_10",		0b0001,     10},				//8.99				2.40
	{"GAIN_20",		0b0010,     20},				//8.70				1.95
	{"GAIN_30",		0b0011,     30},				//12.80				3.40
	{"GAIN_40",		0b0100,     40},				//12.50				2.15
	{"GAIN_60",		0b0101,     60},				//13.31				2.60
	{"GAIN_80",		0b0110,     80},				//12.15				1.91
	{"GAIN_120",	0b0111,     120},				//18.53				2.30
	{"GAIN_157",	0b1000,     157},				//16.49				1.78
	{"GAIN_VCC",	0b1001,     0.2},  //(VCC = 5V)	2.86				1.95
                                  //0.25 (VCC = 3.3V)
	{"GAIN_1X",		0b1010,     1},					//2.90				2.15
};


CommsRetCode gainSPiInitialisation (void) {
	SPiInitialisation (	BCM2835_SPI_CLOCK_DIVIDER_4096, 
						BCM2835_SPI_MODE0, 
						BCM2835_SPI_BIT_ORDER_LSBFIRST, 
						BCM2835_SPI_CS1);
	
	return SPI_ERR_NONE;
};


CommsRetCode gainSPiEnd(void) {
	
	CommsRetCode	ret;
	
	ret = SPiEnd();
	
	if (ret != SPI_ERR_NONE){
		//printf("DEBUG: Error releasing SPi Port");
	}
	
	return ret;
};

CommsRetCode setGainControl(int gain_setting) {

    uint8_t         msgLen = 1;               // The length of the message 
    uint8_t         txBuf[msgLen];     // The outgoing message
	CommsRetCode	ret;
    
    //printf("DEBUG: Into settings Gain Control:%d\n", gain_setting);

	txBuf[0] = 0x00;				//set it initially before modification
	// Set the required values for txBuf based on values set in h file and passed in
	// Bit 7 - is shutdown mode
	txBuf[0] = txBuf[0] + (SHUTDOWN_MODE << 8);
	// Bit 6 - is measuring mode
	txBuf[0] = txBuf[0] + (MEASURING_MODE << 7);
	// Bit 5 is unused
	// Bits 4 to 1 are gain setting
	txBuf[0] = txBuf[0] + (gain_setting << 1);
	//Bit 0 - register selection
	txBuf[0] = txBuf[0] + (REGISTER_SELECTION);
	
    ret = SPiTransmit( txBuf, msgLen);
	
	if (ret!= SPI_ERR_NONE) {
		printf("DEBUG: Response from setGainControl SPiTransmit:%d", ret);
	}
    return ret;

};

//ToDo: This function should be in the setting gain program 
void selectGainValueMenu(void) {
	
	int				i;
	char			option[5];
	int				choice;
	CommsRetCode	ret;
	
	ret = gainSPiInitialisation();
	
	if (ret != SPI_ERR_NONE) {
		return;
	}
	
	printf("Choose the Gain Setting desired:\n\n");
	printf("Choice	Gain Value\n");
	for(i=0; i < qtyGainValues; i++) {
		printf("%d	-	%s\n", i, gainValues[i].description);
	};
	printf("99	-	return to main menu\n");
	do {
		fgets(option, 5, stdin);
		//getchar();			//consumes the extra enter - not sure this is needed
		choice = atoi (option);
		//printf("DEBUG: Choice Entered:%d\n", choice);
		if (choice < 0) strcpy(option, "\0"); //option[0]="\0";			//Set option back to an empty string
		else if (choice >= 0 && choice <= qtyGainValues) {
			//printf("DEBUG: Setting Gain Control of %d\n", gainValues[choice].value);
			ret = setGainControl(gainValues[choice].value);
			printf("Gain has been set\n\n");
			choice = 99;				// exit the loop now the gain has been set
		}
	} while (choice != 99);
	
	ret = gainSPiEnd();
	return;
};

//ToDo: Maybe this should also be in the setting gain control
void setGainDefaultValue(void) {

	CommsRetCode	ret;
	
	ret = gainSPiInitialisation();
	
	if (ret != SPI_ERR_NONE) {
		return;
	}
	
	setGainControl(DEFAULT_GAIN_VALUE);
	
	gainSPiEnd();
};

