/* 
 * File:   gpioFunctions.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 18 January 2019, 22:14
 * 
 * Example header file for the functions required to manage the GPIO ports
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 */

#ifndef GPIOFUNCTIONS_H
#define GPIOFUNCTIONS_H

// The various GPIO Pins that can be read

/* Pin Explanation
 * IF_OUT_DIGITAL   This is to be used when reading signals digitally. There are a number of routines that read frequency from the board, 
 *                  this is what this pin is used for.
 *                  My understanding is that the output from the sensor is fed through the IF amplifier and then ‘digitised’ bytes the 
 *                  comparator shown on the PI Connector wiring diagram. This comparator forces the signal to be either 3V3 or 0V above 
 *                  a certain value. Key change from V1 boards is that the centre signal is approx 1.7V (mid point between 3v3 and 0v). 
 *                  There is no gain control on this pin.
 * 
 * IF_OUT_PGA       This is the output from the gain control fed to a pin for diagnostics. Not really to be used for anything else on 
 *                  the Pi.
 *                  It could be used digitally, but there is no limiting and the centre point is not set to mid range
 * 
 * IF_OUT_TO_PI     This is also to be used to read signals digitally, but POST gain control. It can be used to read frequency.
 *                  This works the same as if_out_digital with regard to voltages and conversion of the signal from analogue to digital, 
 *                  except it is fed from the gain control chip.
 * 
 * SAMPLE_HOLD        Needs to be set LOW for use.
 */

//New Configuration for production boards
#define     IF_OUT_DIGITAL      4       // No gain digital signal
#define     IF_OUT_PGA          27      // Was IF_OUT1 - Diagnostics, don't use
#define     IF_OUT_TO_PI        22      // Was IF_OUT_TO_PI - Digital signal with gain control
#define     SAMPLE_HOLD         17


#define		MAX_WAIT_TIME		2		// The maximum time allowed to register a GPIO state time in seconds.
#define		FREQ_DEBOUNCE_TIME	500		// The time in microseconds to wait for the check time




/*!**************************************************************************
 * Overview:  Set the GPIO pins ready for use
 *  
 * Description: This method sets up the GPIO pins for input and output
 *				Sets IF_OUT1 and IF_OUT_TO_PI for input
 *				Sets SAMPLE_HOLD for output
 *
 * Parameters:
 * param[in]	none
 *
 * return		0       : successful
 *			
 *****************************************************************************/
int setupGpioFunctions(void);

/*!**************************************************************************
 * Overview:  Set the Sample & Hold pin to running state
 *  
 * Description: This method sets up the Sample & Hold pin low so that it
 *				It is in running state
 *
 * Parameters:
 * param[in]	??		: none
 *
 * return		0      : successful
 *****************************************************************************/
int setSampleHoldForRun(void);

/*!**************************************************************************
 * Overview:  Set the Sample & Hold pin to HOLD state
 *  
 * Description: This method sets up the Sample & Hold pin high so that it
 *				It is in HOLD state
 *
 * Parameters:
 * param[in]	??		: none
 *
 * return		0      : successful
 *****************************************************************************/
int setSampleHoldForHold(void);


/*!**************************************************************************
 * Overview: Function to return the frequency from the GPIO pins
 *  
 * Description: This method only uses half the cycle and no debounce, but is
 *				similar to readFullFrequency below.
 *				Requires setupGpioFunctions() & setSampleHoldForRun() to be run 
 *				first
 * Parameters:
 * param[out]   frequency       : A float of the frequency measured
 * param[in]	measuring_pin	: the pin to be used.
 *
 * return		status       : 0 = success
 *****************************************************************************/
int returnRawFrequency(float *frequency, int measuring_pin);

/*!**************************************************************************
 * Overview: Function to return the frequency from the GPIO pins
 *  
 * Description: This method waits for the whole cycle to be competed before 
 *				returning the frequency.
 *				Requires setupGpioFunctions() & setSampleHoldForRun() to be run 
 *				first
 *
 * Parameters:
 * param[out]   frequency       : A float of the frequency measured
 * param[in]	measuring_pin	: the pin to be used.
 *
 * return		status       : 0 = success
 *****************************************************************************/
int returnFullFrequency(float *frequency, int measuring_pin);


#endif /* GPIOFUNCTIONS_H */

