/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <bcm2835.h>        // hardware definition library file
#include "../inc/adcFunctions.h"


CommsRetCode adcSPiInitialisation(void) {
	SPiInitialisation(	BCM2835_SPI_CLOCK_DIVIDER_4096, 
						BCM2835_SPI_MODE3, 
						BCM2835_SPI_BIT_ORDER_MSBFIRST,
						BCM2835_SPI_CS0);
	
	return ERR_NONE;
};

float readVoltage(void) {
    uint8_t         msgLen = 3;               // The length of the message 
    uint8_t         txBuf[msgLen];            // The outgoing message
    uint8_t         rxBuf[msgLen];            // The reply from the A-D
    float           reading=0.00;             // The output value
    float           supply_voltage = 3.3;     // SUpply voltage for the A-D
    uint16_t        fsd_range=4096;           // Maximum value from A-D (12 bits)
	CommsRetCode	ret;
    
    //printf("DEBUG: Into read Voltage\n");

    txBuf[0] = 0x01; //0b00000001 - 001                  // Start Bit
    // For Custard Pi 2    txBuf[1] = 0xF0; //0b11110000 - 240                  // Remainder of message to send  
    txBuf[1] = 0xB0; //0b10110000 -                   // Remainder of message to send  
    txBuf[2] = 0x00; //0b00000000 - 000                  // Dummy to get MCP3202 to send return data    

    ret = SPiTranscieve( txBuf, rxBuf, msgLen);

	if (ret != ERR_NONE){
		return 0.0;
	}
    /* For debug purposes
	uint8_t i;
    printf("DEBUG:Response:");
    for (i=0; i < msgLen; i++)
    {
        printf("%02x", rxBuf[i]);
    }
    printf("\n");
    //*/

    /* Shift the bits to the correct location
     * the first byte back is ignored as it only there for comms
     * the second byte is the MSByte (lower 4 bits anyway, rest are zero)
     * the third byte is the LSByte
     * */
    
    reading = ((rxBuf[1] & 0x0f) << 8)  + rxBuf[2];
    //printf("DEBUG: Reading after merge:%fs\n", reading);

    // Formula for calculation      Digital Output Code = 4096 * Vin
    //                                                    ----------
    //                                                       Vdd
    reading = reading * (supply_voltage / fsd_range);

    //printf("DEBUG: Voltage being returned:%f\n", reading);

    return reading;
};
