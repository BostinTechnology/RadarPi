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

#include    "../inc/rdr_i2c_comms.h"


int I2CInitialisation(uint8_t *i2cbus) {
    int file;
    if ((file = open(I2C_COMMS_PORT, O_RDWR)) < 0) {
        /* ERROR HANDLING: you can check errno to see what went wrong */
        printf("Failed to open the i2c bus\n");
        return I2C_ERR_INITIALISATION;
    }
    
    if (ioctl(file, I2C_SLAVE, ICOG_ADDRESS) < 0) {         address will have to be passed in, depending on what is being written to!
        printf("Failed to acquire bus access and/or talk to slave.\n");
        /* ERROR HANDLING; you can check errno to see what went wrong */
        return I2C_ERR_INITIALISATION;
    }
    
    need to make i2cbus equal to the file parameter above!
            
    return I2C_ERR_NONE;
};

int I2CEnd(uint8_t *i2cbus) {
    
    
};

int I2CTranscieve(uint8_t *i2cbus, uint8_t *SPitxBuf, uint8_t *SPirxBuf, uint8_t SPibufLen) {
    
    
};

int I2CRead(uint8_t *i2cbus, uint8_t *i2crxBuf, uint8_t i2cbufLen) {
    
    convert this to look similar to the spi comms for checking and data setup
            
	//----- READ BYTES -----
	length = 4;			//<<< Number of bytes to read
	if (read(file_i2c, buffer, length) != length)		//read() returns the number of bytes actually read, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		//ERROR HANDLING: i2c transaction failed
		printf("Failed to read from the i2c bus.\n");
	}
	else
	{
		printf("Data read: %s\n", buffer);
	}

    transfer data into the right buffer
};


int I2CWrite(uint8_t *i2cbus, uint8_t *i2ctxBuf, uint8_t i2cbufLen) {
    
     convert this to look similar to the spi comms for checking and data setup

    transfer data into the buffers before sending
             
    	//----- WRITE BYTES -----
	buffer[0] = 0x01;
	buffer[1] = 0x02;
	length = 2;			//<<< Number of bytes to write
	if (write(file_i2c, buffer, length) != length)		//write() returns the number of bytes actually written, if it doesn't match then an error occurred (e.g. no response from the device)
	{
		/* ERROR HANDLING: i2c transaction failed */
		printf("Failed to write to the i2c bus.\n");
	}
    
    return correct status
};

