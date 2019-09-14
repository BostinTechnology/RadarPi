 /* 
 * File:   gainFunctions.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 12 January 2019, 21:03
 */

 /**********************************************************************
  * Development Notes
  *
  * This is a write-only interface, no data is returned
  *
  * Initial Comms by bringing CS low, clock in on the rising edge
  * Requires Clock Polarity (CPOL) = 0 & Clock Phase (CPHA) = 0
  *     MAX Clock Frequency is 5MHz
  *
  * CS Pin is connected to CE1
  *
  * Data is written LSB First
  * 
  * Format for the Gain Register
  *
  * D7   D6   D5   D4  D3  D2  D1  D0
  * SHDN MEAS  X   G3  G2  G1  G0  SEL=1 
  *
  * SHDN is set to 0 for normal operation
  * MEAS is set to 0 for normal operation
  * G3-0 are set to 0b0001 for a gain of 10
  * SEL is set to 1 for Gain Register
  * 
  */

#ifndef GAINFUNCTIONS_H
#define GAINFUNCTIONS_H

#include "spi_comms.h"

#define	qtyGainValues		11		//The number of values in the gainValues structure

struct GAIN_DEFINITION {
	char	description[10];
	int		value;
    int     gain;
} gainValues[qtyGainValues];


/* First in this file, create a 
 * typedef struct structurename
 * {
 *      blah blah
 * } nameoftypedef
 * 
 * 
 * then later in the file I can use a definition of values
 * 
 * nameoftypedef variablename [] = 
 *  { x,y,z with values in it
 *      etc
 *  }
 ]*/

#define	SHUTDOWN_MODE		0b0		// Set to normal mode, change this to 1 for low power mode
#define	MEASURING_MODE		0b0		// Set to normal operation, if set to 1, inputs shorted
#define	REGISTER_SELECTION	0b1		// Set to 1 for gain register, 0 is for Vos Trim Register

#define DEFAULT_GAIN_VALUE	0b0001	// Default value for the gain setting



/*!
 *****************************************************************************
 * Overview:  Initialises the SPI port for the Gain Control
 *  
 * This method using the bcm2835 library to set the required settings to set the
 * SPi port for the Gain Control chip
 *
 * param[in/out] in : binary value require for the desired gain 
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
CommsRetCode gainSPiInitialisation (void);

/*!
 *****************************************************************************
 * Overview:  Sets the Gain Control to the given value
 *  
 * This method using the SPi comms to send the required data byte to set the
 * gain control to the supplied setting
 *
 * Gain Register setting is described above
 *
 * param[in]	gain_setting : binary value require for the desired gain for bits g3:g0
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
void setGainControl(int gain_setting);


/*!
 *****************************************************************************
 * Overview:  Allows the user to select the gain value to set
 *  
 * This method allows the user to select the predefined gain values before
 * then using setGainControl to set it.
 *
 * Gain Register setting is described above
 *
 * param[in]	gain_setting : binary value require for the desired gain for bits g3:g0
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
void selectGainValueMenu(void);

/*!
 *****************************************************************************
 * Overview:  Ends the SPI port for the ADC chip Control
 *  
 * This method releases the SPi port for the ADC chip
 *
 * param[in/out] ?? : nothing 
 *
 * return none   : nothing
 *****************************************************************************
 */
void gainSPiEnd(void);

/*!
 *****************************************************************************
 * Overview:  Sets the Gain Control to default value
 *  
 * This method using the SPi comms to send the required data byte to set the
 * gain control to the default value
 *
 * Gain Register setting is described above
 *
 * param[in]	gain_setting : binary value require for the desired gain for bits g3:g0
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
void setGainDefaultValue(void);

#endif /* GAINFUNCTIONS_H */
