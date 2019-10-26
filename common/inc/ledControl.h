/*
 * File:   ledControl.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 08 December 2018, 20:44
 *
 * Example header file for the functions required to control the onboard LEDS
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 */

#ifndef LEDCONTROL_H
#define LEDCONTROL_H

// LEDs
#define		LED_RUNNING					14
#define		LED_MONITORING				15
#define		LED_TRIGGERED				18	

#define		LED_ON						1
#define		LED_OFF						0

#define		LED_TEST_SPEED				500000			//The time each LED is left on in microseconds


#define     LED_ERR_NONE                0
#define     LED_ERR_SETUP               1
#define     LED_ERR_SET_LED_RUNNING      2
#define     LED_ERR_SET_LED_MONITORING  3
#define     LED_ERR_SET_LED_TRIGGERED   4


//functions
int ledSetup(void);					//Setup the channels for the LEDs
int controlRunningLED(int state);		//turn the Running LED on or off
int controlMonitoringLED(int state);		//turn the Monitoring LED on or off
int controlTriggeredLED(int state);		//turn the Triggered LED on or off

/*!**************************************************************************
 * Overview:  Cycle through the LEDs to test them
 *  
 * Description: This method turns each LED on and off in a timed cycle
 *				Requires CTRL - C to exit
 *
 * Parameters:
 * param[in] none : 
 *
 * return 0         : no error
 *****************************************************************************
 */

int cycleLEDs(void);					// cycle through the leds to test them

#endif /* LEDCONTROL_H */

