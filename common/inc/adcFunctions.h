 /* File:   adcFunctions.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 12 January 2019, 08:50
 * 
 * Example header file for the ADC comms setup and returning the voltage
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 */

/**********************************************************************
  * Development Notes
  *
  * Use leading zero's to get the required number of bits
  *
  * Initial Comms by bringing CS low, clock out on falling edge, data in on the rising edge
  * 
  *     If it is low, it must be brought high and then low to work
  * Format of message to MCP3202
  *     Start Bit               Set to 1
  *     Sgl / Diff bit          Set to 1 for Single Ended
  *     Odd / Sign Bit          Set to 0 as using Channel 0
  *     MSBF                    Set to 1 to as only output MSB first
  *
  * Format of response from MCP3202
  *     Null Bit
  *     B11                 Bits B11 - 8 are in the lower half of the first byte returned
  *     B10
  *     ....                Bits B7 - 0 are in the second byte received
  *     B1
  *     B0
  *
  *     After this further clocks will just output zero's
  *
  * Comms method
  *     0. CS Low
  *     1. Send 0b00000001      Just the start bit as byte 1
  *     2. Send 0b10100000      The message bits above
  *         This will return 8 bits, the last 4 contain the upper half of the reply
  *     3. Send 0b00000000      This is ignoted by the MCP3202
  *         The response is the lower 8 bits of the reply
  *
  *     Merge the upper 4 bits (AND with 0b00001111 << 4) and the lower half together
  *     4. CS High
  *
  * Conversion of the response
  *     voltage read = (value received * 3.3) / 4096
  */

/*************************************************************************/


#ifndef ADCFUNCTIONS_H
#define ADCFUNCTIONS_H


#include "rdr_spi_comms.h"

// The list below is the failure modes possible
#define     ADC_EXIT_SUCCESS        0
#define     ADC_NO_RESPONSE         1
#define     ADC_SETUP_ERROR         2
/*
 *****************************************************************************
 * Overview:  Read the voltage from the ADC chip Control
 *  
 * This method using the bcm2835 library to read the value from the ADC chip
 * and convert it to a real voltage reading
 *
 * param[out] reading   : the value of the adc port 
 *
 * return status        : success / failure status
 *****************************************************************************
 */
int readVoltage(float *reading);

/*!
 *****************************************************************************
 * Overview:  Initialises the SPI port for the ADC chip Control
 *  
 * This method configures the SPi port for the ADC chip
 *
 * param[in/out] ?? : nothing 
 *
 * return status   : failure mode or success
 *****************************************************************************
 */
int adcSPiInitialisation(void);

/*!
 *****************************************************************************
 * Overview:  Ends the SPI port for the ADC chip Control
 *  
 * This method releases the SPi port for the ADC chip
 *
 * param[in/out] ?? : nothing 
 *
 * return status   : failure mode or success
 *****************************************************************************
 */
int adcSPiEnd(void);

#endif /* ADCFUNCTIONS_H */

