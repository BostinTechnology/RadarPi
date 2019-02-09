/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   freqTest.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 15 January 2019, 18:34
 */

#ifndef FREQTEST_H
#define FREQTEST_H

#define		MAX_WAIT_TIME		3		// The maximum time allowed to register a GPIO state time in seconds.
#define		FREQ_DEBOUNCE_TIME	500		// The time in microseconds to wait for the check time



/*!**************************************************************************
 * Overview: Function to read the frequency from the GPIO pins
 *  
 * Description: This method first calls the menu choice and then measures the
 *				time and displays the frequency determined.
 *				Note: The reading is only half the time period, which is then
 *				multiplied to give a frequency reading
 *
 * Parameters:
 * param[in]	none	: 
 *
 * return		0       : nothing
 *****************************************************************************/
void readHalfFrequency(void);

/*!**************************************************************************
 * Overview: Function to read the frequency from the GPIO pins
 *  
 * Description: This method first calls the menu choice and then measures the
 *				time and displays the frequency determined.
 *				Note: The method waits for the whole cycle to be competed before 
 *				returning the frequency.
 *
 * Parameters:
 * param[in]	none	: 
 *
 * return		0       : nothing
 *****************************************************************************/
void readFullFrequency(void);

/*!**************************************************************************
 * Overview: Menu function for user selection of the GPIO pin
 *  
 * Description: This method provides the user with a menu of choice to choose
 *				which GPIO pin is to be measured
 *
 * Parameters:
 * param[in]	none	: 
 *
 * return		gpio_pin    : GPIO pin
 *				0			: zero if no pin selected
 *****************************************************************************/
int chooseGPIOPin (void);


#endif /* FREQTEST_H */

