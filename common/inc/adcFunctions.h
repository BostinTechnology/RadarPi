/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   adcFunctions.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 12 January 2019, 08:50
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


#include "spi_comms.h"

/*!
 *****************************************************************************
 * Overview:  Read the voltage from the ADC chip Control
 *  
 * This method using the bcm2835 library to read the value from the ADC chip
 * and convert it to a real voltage reading
 *
 * param[in/out] ? : nothing 
 *
 * return float         : voltage reading
 *****************************************************************************
 */
float readVoltage(void);

/*!
 *****************************************************************************
 * Overview:  Initialises the SPI port for the ADC chip Control
 *  
 * This method using the bcm2835 library to set the required settings to set the
 * SPi port for the ADC chip
 *
 * param[in/out] ?? : nothing 
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
CommsRetCode adcSPiInitialisation(void);

#endif /* ADCFUNCTIONS_H */
