/* 
 * File:   icogLs1Functions.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 01 February 2020, 10:49
 * 
 * Example code for reading and setting data for the light iCog
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */

#include <stdio.h>
#include <time.h>

#include "../inc/rdr_i2c_comms.h"
#include "../inc/icog/Ls1Functions.h"


int icogI2CInitialisation (uint8_t *i2cbus) {
    
    int status = ICOG_EXIT_SUCCESS;
    int *fd = malloc (sizeof(int*));
    status = I2CInitialisation(fd, ICOG_ADDRESS);
    
    if (status != I2C_ERR_NONE) {
        status = ICOG_SETUP_ERROR;
    }
    
    return status;
};

int icogI2CEnd(void) {
    
    int     status;
    status = i2cEnd();
    
    return status;
};

int icogTurnOffSensor(uint8_t *i2cbus) {
    
    int     status;
    int     mask;
    int     shift;
    int     mode;
    int     towrite;
    int     *byte;
    
    mask = 0b11100000;
    shift = 5;
    mode = 0b000;
    
    status = I2CRead(i2cbus, COMMAND_I_REGISTER, byte, 1);
    printf("Command Register Before turning off (0x00):%x\n", byte);
    if (byte & mask) != (mode << shift) {
        // Modify the register to set bits 7 to 5= 0b000
        towrite = (byte & ~mask) | (mode << shift);
        printf("Byte to write to turn off %s\n", towrite);
        status = I2CWrite(i2cbus, COMMAND_I_REGISTER, (int*)towrite, 1);
        usleep(WAITTIME);
        status = I2CRead(i2cbus, COMMAND_I_REGISTER, byte, 1);
        printf("Command Register After turning off (0x00):%x\n", byte);
        if (byte & mask) == (mode << shift):
            printf("Sensor Turned on\n");
        else:
            printf("Sensor Turned off\n");
    } else {
        printf("Sensor already Turned on\n");
    }
    return;
};

int icogSetALSMode(void) {
    
};

int icogSetIRMode(void) {
    
};

int icogSetADCResolution(void) {
    
};

int icogReadDataRegisters(void) {
    
};

int icogReadADCClockCycles(void) {
    
};

int icogReadADCClockCycles(void) {
    
};

int icogReadSensorMode(void) {
    
};

int icogCalculateLux(void) {
    
};

