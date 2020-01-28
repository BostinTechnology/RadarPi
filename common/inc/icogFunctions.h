/* 
 * File:   icogFunctions.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 26 January 2020, 10:39
 * 
 * Example code for the light iCog
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */


#ifndef ICOGFUNCTIONS_H
#define ICOGFUNCTIONS_H

/*****************************************************************************
 * Overview: 
 * <short description>
 *
 * param[in/out] <name> : <function> 
 *
 * return status meanings         
 *          0 : success
 *          1 : <error description>
 *****************************************************************************/

/*!***************************************************************************
 * Overview:  Initialises the I2C port for the iCog
 *  
 * This method using the bcm2835 library to set the required settings to set the
 * SPi port for the iCog Control chip
 *
 * param[in/out] in : binary value require for the desired gain 
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
int icogI2CInitialisation (void);

/*!***************************************************************************
 * Overview:  Ends the I2C port for the iCog  Control
 *  
 * This method releases the I2C port for the iCog
 *
 * param[in/out] ?? : nothing 
 *
 * return none   : nothing
 *****************************************************************************
 */
int icogI2CEnd(void);



#endif /* ICOGFUNCTIONS_H */

