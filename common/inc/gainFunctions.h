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

struct GAIN_DEFINITION {
	char	description[10];
	int		value;
};
/*! Gain Settings for G3:G0
 *  gainValues is a 2 dimensional array that contains the setting and corresponding gain value
					G3:G0		//GAIN (V/V)		SLEW RATE (V/μs)	SMALL-SIGNAL BANDWIDTH (MHz)*/
struct GAIN_DEFINITION gainValues[] = {
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

#define	qtyGainValues		11		//The number of values in the gainValues structure

#define	SHUTDOWN_MODE		0b0		// Set to normal mode, change this to 1 for low power mode
#define	MEASURING_MODE		0b0		// Set to normal operation, if set to 1, inputs shorted
#define	REGISTER_SELECTION	0b1		// Set to 1 for gain register, 0 is for Vos Trim Register



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
 * Overview:  Sets the Gain Control to 10
 *  
 * This method using the SPi comms to send the required data byte to set the
 * gain control to 10
 *
 * Gain Register setting is described above
 *
 * param[in]	gain_setting : binary value require for the desired gain for bits g3:g0
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
void setGainControl(int gain_setting);

#endif /* GAINFUNCTIONS_H */