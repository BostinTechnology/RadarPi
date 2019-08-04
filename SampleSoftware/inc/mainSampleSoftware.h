/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   mainSampleSoftware.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 10 February 2019, 20:33
 */

#ifndef MAINSAMPLESOFTWARE_H
#define MAINSAMPLESOFTWARE_H

#define		FREQUENCY_TRIGGER		100		// Frequency
#define		VOLTAGE_TRIGGER			2.1		// volts
#define		TRIGGER_TIMEOUT			1.5		// Timeout for how long to leave the triggered LED on.

/*!**************************************************************************
 * Overview:  Display the Bostin Technology introduction screen
 *  
 * Description: This method displays the splash screen
 *
 * Parameters:
 * param[in/out] ?? : None 
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
void splashScreen(void);

/*!**************************************************************************
 * Overview:  Display the help screen and menu options
 *  
 * Description: This method displays the menu options screen
 *
 * Parameters:
 * param[in/out] ?? : None 
 *
 * return NOTHING         : No response
 *****************************************************************************/
void helpScreen(void);

/*!**************************************************************************
 * Overview: Provide a filtered view of the signal coming in
 *  
 * Description: Flashes the LEDs and displays CLEAR / DETECTED if above a 
 *				frequency threshold for frequency on IFOUT TO PI through 
 *				some de-glitching software.
 *				Gain set to default.
 *				Holds the LED if detected for a short period
 *
 * Parameters:
 * param[in/out] ?? : None 
 *
 * return NOTHING         : No response
 *****************************************************************************/
void digitalDetectionFiltered(void);

/*!**************************************************************************
 * Overview: Provide a raw view of the signal coming in 
 *  
 * Description: Flashes the LEDs and displays CLEAR / DETECTED if above a 
 *				frequency threshold for frequency on IFOUT TO PI. 
 *				Gain set to default.
 *
 * Parameters:
 * param[in/out] ?? : None 
 *
 * return NOTHING         : No response
 *****************************************************************************/
void digitalDetectionRaw(void);

/*!**************************************************************************
 * Overview: Display the ADC output.
 *  
 * Description: Read and display the ADC output, using levels to trigger the
 *				LEDs when exceeded.
 *				
 *
 * Parameters:
 * param[in/out] ?? : None 
 *
 * return NOTHING         : No response
 *****************************************************************************/
void adcMeasurement(void);


#endif /* MAINSAMPLESOFTWARE_H */

/*
 * Comsumer Software
 * 
 * Routines that show detection of an object
 *		STILL			LED 'LED_MONITORING'
 *		MOVEMENT		LED 'LED_TRIGGERED'
 * 
 * on IFOUT_TO_PI
 * 
 * 2 choices, raw or filtered
 * - in raw, when the frequency exceeds limit, the LED is flashed
 * - in filtered, it has to be for a period / time period
 * 
 * -------------
 * Default set gain to 10
 * 
 * -------------
 * Graph the output of the ADC over user movement
 * 
 * -------------
 * Change gain setting
 * 
 */