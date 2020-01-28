 /* 
 * File:   gainFunctions.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 12 January 2019, 21:03
 * 
 * Example header file to provide the functions to set the gain, including comms
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
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
  * Example value, setting gain of 20
  * 
  *     76543210
  *     00000101    = 0x05
  * 
  */

#ifndef GAINFUNCTIONS_H
#define GAINFUNCTIONS_H

#include "rdr_spi_comms.h"

#define	qtyGainValues		11		//The number of values in the gainValues structure


// This is also slightly different, creates a gainValuesDef

typedef struct GAIN_DEFINITION {
	char	description[10];
	int		value;
    int     gain;
} gainValuesDef;


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
//gainValuesDef gainValues[qtyGainValues] = {

//gainValuesDef gainValues[] = {
///*! Gain Settings for G3:G0
// *  gainValues is a 2 dimensional array that contains the setting and corresponding gain value
//					G3:G0		GAIN (V/V)		SLEW RATE (V/μs)	SMALL-SIGNAL BANDWIDTH (MHz)*/
//	{"GAIN_1",		0b0000, 	1},					//2.90				2.15
//	{"GAIN_10",		0b0001,     10},				//8.99				2.40
//	{"GAIN_20",		0b0010,     20},				//8.70				1.95
//	{"GAIN_30",		0b0011,     30},				//12.80				3.40
//	{"GAIN_40",		0b0100,     40},				//12.50				2.15
//	{"GAIN_60",		0b0101,     60},				//13.31				2.60
//	{"GAIN_80",		0b0110,     80},				//12.15				1.91
//	{"GAIN_120",	0b0111,     120},				//18.53				2.30
//	{"GAIN_157",	0b1000,     157},				//16.49				1.78
//	{"GAIN_VCC",	0b1001,     0.2},  //(VCC = 5V)	2.86				1.95
//                                  //0.25 (VCC = 3.3V)
//	{"GAIN_1X",		0b1010,     1},					//2.90				2.15
//};


#define	SHUTDOWN_MODE		0b0		// Set to normal mode, change this to 1 for low power mode
#define	MEASURING_MODE		0b0		// Set to normal operation, if set to 1, inputs shorted
#define	REGISTER_SELECTION	0b1		// Set to 1 for gain register, 0 is for Vos Trim Register

#define DEFAULT_GAIN_VALUE	0b0001	// Default value for the gain setting



/*!***************************************************************************
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

/*!***************************************************************************
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
CommsRetCode setGainControl(int gain_setting);


/*!***************************************************************************
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
CommsRetCode gainSPiEnd(void);

/*!***************************************************************************
 * Overview:  Sets the Gain Control to default value
 *  
 * This method using the SPi comms to send the required data byte to set the
 * gain control to the default value (DEFAULT_GAIN_VALUE) as defined above
 *
 * Gain Register setting is described above
 *
 * param[in]	nothing   : 
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
void setGainDefaultValue(void);

#endif /* GAINFUNCTIONS_H */
