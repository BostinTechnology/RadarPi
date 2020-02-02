/* 
 * File:   rdr_i2c_comms.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 26 January 2020, 10:46
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

#include <unistd.h>				//Needed for I2C port
#include <fcntl.h>				//Needed for I2C port
#include <sys/ioctl.h>			//Needed for I2C port
#include <linux/i2c-dev.h>		//Needed for I2C port
//Wiring Pi libraries
#include <wiringpi.h>
#include <wiringPiI2C.h>

#include    "../inc/rdr_i2c_comms.h"


int I2CInitialisation(uint8_t *i2cbus, int address) {
    int file;
    
    //wiringPiSetup();
    file = wiringPiI2CSetup(address);

    if (file < 0) {                 //error is -1
        printf("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        return I2C_ERR_INITIALISATION;
    }

    //need to make i2c bus equal to the file parameter above!
    i2cbus = file;
            
    return I2C_ERR_NONE;
};

int I2CEnd(void) {
    
    // No action required.
    return I2C_ERR_NONE;
};

int I2CTranscieve(uint8_t *i2cbus, uint8_t *SPitxBuf, uint8_t *SPirxBuf, uint8_t SPibufLen) {
    
    
};

int I2CRead(uint8_t *i2cbus, uint8_t startAddr, uint8_t *i2crxBuf, uint8_t i2cbufLen) {
    
    int     counter = 0;
    
    do {
        i2crxBuf[counter] = wiringPiI2CReadReg8(i2cbus, (startAddr + counter));
        counter ++;
    } while (counter < i2cbufLen);
    
    return I2C_ERR_NONE;
};

int I2CWrite(uint8_t *i2cbus, uint8_t startAddr, uint8_t *i2ctxBuf, uint8_t i2cbufLen) {
    
    int     status = I2C_ERR_NONE;
    int     counter = 0;
    
    do {
        status = wiringPiI2CWriteReg8(i2cbus, startAddr, i2ctxBuf[counter]);
        if (status != 0) {
            printf("Error Occurred, status: %d\n", status);
            status = I2C_ERR_WRITE;
            break;
        }
        counter ++;
    } while (counter < i2cbufLen);
    
    return status;
};



