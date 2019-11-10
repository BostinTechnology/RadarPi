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

//ToDo: Add some details about these PINS in here

#define		IF_OUT1				27	// The GPIO pin used for the frequency input, was 4 originally and also tried 11
#define		IF_OUT_TO_PI		22
#define		SAMPLE_HOLD			17	// 

#define		MAX_WAIT_TIME		3		// The maximum time allowed to register a GPIO state time in seconds.
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

