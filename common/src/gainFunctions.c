/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "../inc/gainFunctions.h"

struct GAIN_DEFINITION gainValues[qtyGainValues] = {
	{"GAIN_1",		0b0000},	//1					2.90				2.15
	{"GAIN_10",		0b0001},	//10				8.99				2.40
	{"GAIN_20",		0b0010},	//20				8.70				1.95
	{"GAIN_30",		0b0011},	//30				12.80				3.40
	{"GAIN_40",		0b0100},	//40				12.50				2.15
	{"GAIN_60",		0b0101},	//60				13.31				2.60
	{"GAIN_80",		0b0110},	//80				12.15				1.91
	{"GAIN_120",	0b0111},	//120				18.53				2.30
	{"GAIN_157",	0b1000},	//157				16.49				1.78
	{"GAIN_VCC",	0b1001},	//0.2  (VCC = 5V)	2.86				1.95
								//0.25 (VCC = 3.3V)
	{"GAIN_1X",		0b1010},	//1					2.90				2.15
};


CommsRetCode gainSPiInitialisation (void) {
	SPiInitialisation (	BCM2835_SPI_CLOCK_DIVIDER_4096, 
						BCM2835_SPI_MODE0, 
						BCM2835_SPI_BIT_ORDER_LSBFIRST, 
						BCM2835_SPI_CS1);
	
	return ERR_NONE;
};
	
void setGainControl(int gain_setting) {

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
	//printf("DEBUG: Response from setGainControl SPiTransmit:%d", ret);
    return;

};

