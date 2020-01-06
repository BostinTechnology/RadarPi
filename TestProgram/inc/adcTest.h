/* 
 * File:   adcTest.h
 * 
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 12 January 2019, 08:55
 * 
 * Example code for to support the test program with its ADC tests
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */

#ifndef ADCTEST_H
#define ADCTEST_H

#define		ADC_READING_TEST_SPEED		100			// the delay between ADC readings in uS



/*!**************************************************************************
 * Overview:  Read the ADC Values continuously
 *  
 * Description: This method displays the current reading from the ADC
 *
 * Parameters:
 * param[in] none : 
 *
 * return 0         : no error
 *****************************************************************************
 */

int cycleADCReadings(void);

#endif /* ADCTEST_H */

