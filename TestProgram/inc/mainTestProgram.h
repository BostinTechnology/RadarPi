/* 
 * File:   mainTestProgram.h
 * 
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 10 February 2019, 17:41
 * 
 * Example code for testing the manufacturing of the Radar Pi
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */

#ifndef MAINTESTPROGRAM_H
#define MAINTESTPROGRAM_H

#define		INPUT_FREQUENCY			103		// Frequency in Hz
#define		FREQ_TOLERANCE			0.05	// percentage of error allowed
#define		TEST_TIMEOUT			5		// seconds to run each test for
#define		INPUT_VOLTAGE			2.1		// Input voltage on Volts
#define		VOLT_TOLERANCE			0.05	// percentage of error allowed

/*!**************************************************************************
 * Overview:  Display the Bostin Technology introduction screen
 *  
 * Description: This method displays the splash screen
 *
 * Parameters:
 * param[in/out] ?? : None 
 *
 * return NOTHING         : No response
 *****************************************************************************/
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

/*!****************************************************************************
 * Overview:  The Main Entry routine containing the menu 
 *  
 * Description: This method displays the menu options and manages the user entry
 *
 * Parameters:
 * param[in/out] ??     : None 
 *
 * return exit code     : 0 when complete, error code otherwise
 * ***************************************************************************/
int main(int argc, char** argv);

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
 ******************************************************************************/
void cycleLEDs(void);					// cycle through the leds to test them


#endif /* MAINTESTPROGRAM_H */

