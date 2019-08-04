/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   adcTest.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 12 January 2019, 08:55
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

