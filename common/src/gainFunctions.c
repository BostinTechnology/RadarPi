/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "../inc/gainFunctions.h"


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
	CommsRetCode    ret;
    
    //printf("DEBUG: Into settings Gain Control\n");

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

    return;

};

