/* 
 * File:   icogFunctions.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 26 January 2020, 10:40
 * 
 * Example code for reading and setting data for the light iCog
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */



int icogI2CInitialisation (void) {
    
	I2CInitialisation (	BCM2835_SPI_CLOCK_DIVIDER_4096, 
						BCM2835_SPI_MODE0, 
						BCM2835_SPI_BIT_ORDER_LSBFIRST, 
						BCM2835_SPI_CS1);
	
	return I2C_ERR_NONE;
};

}

int icogI2CEnd(void) {
    
}