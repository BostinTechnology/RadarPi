/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gpioFunctions.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 18 January 2019, 22:14
 */

#ifndef GPIOFUNCTIONS_H
#define GPIOFUNCTIONS_H

// The various GPIO Pins that can be read

#define		IF_OUT1				27	// The GPIO pin used for the frequency input, was 4 originally and also tried 11
#define		IF_OUT_TO_PI		22
#define		SAMPLE_HOLD			17	// 




/*!**************************************************************************
 * Overview:  Set the GPIO pins ready for use
 *  
 * Description: This method sets up the GPIO pins for input and output
 *				Sets IF_OUT1 and IF_OUT_TO_PI for input
 *				Sets SAMPLE_HOLD for output
 *
 * Parameters:
 * param[in]	pin		: gpio pin to monitor
 *		[in]	timeout	: float of the maximum time to wait
 *
 * return		0       : no time
 *				float	: duration
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
 * return		??      : nothing
 *****************************************************************************/
void setSampleHoldForRun(void);

#endif /* GPIOFUNCTIONS_H */

