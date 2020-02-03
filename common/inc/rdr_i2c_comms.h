/* 
 * File:   rdr_i2c_comms.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 26 January 2020, 10:45
 * 
 * Example code for control of the i2c bus for the radar Pi
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */


#ifndef RDR_I2C_COMMS_H
#define RDR_I2C_COMMS_H

#include <stdio.h>
#include <stdint.h>

#define     I2C_COMMS_PORT                      "/dev/i2c-2"        this will nbeed to be changed as there are 2 buses to write / read with


#define    I2C_ERR_NONE                         0 /*! No error occurred */
#define    I2C_ERR_INITIALISATION               1 /*! Unable to initialise the I2C comms */
#define    I2C_ERR_COMMS                        2 /*! Communications failure has occurred */
#define    I2C_ERR_PARAMETERS                   3 /*! Incorrect parameters provided to the function */
#define    I2C_ERR_WRITE                        4 /*! Incorrect parameters provided to the function */


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
 * Overview:  Setup the i2C for comms
 *  
 * Utilising the ioctl libraries, setup the I2C port for use, see comments 
 * above for information or ioctl
 *
 * param[out]	i2cbus          : I2C Bus identifier
 *
 * return I2C_ERR_NONE              : No error
 * return I2C_ERR_INITILISATION     : Initialisation Error
 ******************************************************************************/
int I2CInitialisation(int *i2cbus, int address);

/*!***************************************************************************
 * Overview:  Close the I2C comms port
 *  
 * Utilising the xxxxx libraries, close the I2C port and return the pins to 
 * the default state.
 * 
 * param[in]  i2cbus : The bus to be closed
 *
 * return I2C_ERR_NONE              : No error
 * return I2C_ERR_INITILISATION     : Initialisation Error
 * return I2C_ERR_COMMS             : Comms failure
 ******************************************************************************/
int I2CEnd(void);

/*!***************************************************************************
 * Overview:  Perform a I2C comms transmit and receive
 *  
 * Utilising the xxxxx libraries, perform a transmit and receive of data provided.
 * Assumption is the transmit and receive buffers are the same length as defined in
 * the parameters provided
 * 
 * param[in]  ??        : 
 *
 * return I2C_ERR_NONE        : No error
 ******************************************************************************/
int I2CTranscieve(int *i2cbus, int *SPitxBuf, int *SPirxBuf, int SPibufLen);

/*!***************************************************************************
 * Overview:  Perform a I2C comms read only
 *  
 * Utilising the xxxxx libraries, perform a read of the device only.
 * Assumption is the receive buffer is of sufficient size
 * 
 * param[in]  *i2cbus   : The bus that has been opened for use
 * param[in]  startAddr : The first address to read
 * param[out] *i2crxBuf : A pointer to the data that has been received
 * param[in]  i2cbufLen : The length of the expected buffer
 *
 * return I2C_ERR_NONE              : No error
 *      Due to the process used, it doesn't return anything else.
 *****************************************************************************/
int I2CRead(int *i2cbus, int startAddr, int *i2crxBuf, int i2cbufLen);

/*!***************************************************************************
 * Overview:  Perform a I2C comms write only
 *  
 * Utilising the xxxxx libraries, perform a transmit of data provided.
 * Data of length i2cbufLen will be read from the i2ctxBuf register and sent
 * on the i2c port provided i2cbus
 * 
 * param[in]  *i2cbus   : The bus that has been opened for use
 * param[in]  startAddr : The first address to be written to  
 * param[out] *i2ctxBuf : The data that has been received
 * param[in]  i2cbufLen : The length of the data to be sent buffer
 *
 * return I2C_ERR_NONE              : No error
 * return I2C_ERR_COMMS             : Comms failure
 *****************************************************************************/
int I2CWrite(int *i2cbus, int startAddr, int *i2ctxBuf, int i2cbufLen);


#endif /* RDR_I2C_COMMS_H */

