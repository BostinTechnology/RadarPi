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
#include <wiringPi.h>
#include <wiringPiI2C.h>

#include    "../inc/rdr_i2c_comms.h"


int I2CInitialisation(int *i2cbus, int address) {
    int file;
    
    printf("Into I2C Initilisation, address:%x\n", address);
    wiringPiSetup();
    printf(".\n");
    file = wiringPiI2CSetup(address);
    
    printf("response:%d\n", file);
    if (file < 0) {                 //error is -1
        printf("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        return I2C_ERR_INITIALISATION;
    }

    printf(".\n");
    //need to make i2c bus equal to the file parameter above!
    *i2cbus = file;
            
    return I2C_ERR_NONE;
};

int I2CEnd(void) {
    
    // No action required.
    return I2C_ERR_NONE;
};

int I2CTranscieve(int *i2cbus, int *i2ctxBuf, int *i2crxBuf, int i2cbufLen) {
    printf("To Be Implementerd\n");
    return 0;
    
};

int I2CByteRead(int *i2cbus, int startAddr, int *i2crxBuf) {
    
    printf("Into I2C Read\n");
    printf("Bus:%d, Address:%d\n", *i2cbus, startAddr);
    
    // This line doesn't work
    *i2crxBuf = wiringPiI2CReadReg8(*i2cbus, startAddr);
    
    // Trying this to see if I can figure it out, but it also doesn't work
    //*i2crxBuf = 4;
    printf("...\n");
    
    return I2C_ERR_NONE;
};

int I2CByteWrite(int *i2cbus, int startAddr, int i2ctxBuf, int i2cbufLen) {
    
    printf("Into I2C Write\n");
    printf("Bus:%d, Address:%d Data to Write:%x\n", *i2cbus, startAddr, *i2ctxBuf);
    
    int     status = I2C_ERR_NONE;
    
    status = wiringPiI2CWriteReg8(*i2cbus, startAddr, i2ctxBuf;
    if (status != 0) {
        printf("Error Occurred, status: %d\n", status);
        status = I2C_ERR_WRITE;
    }
    
    return status;
};



