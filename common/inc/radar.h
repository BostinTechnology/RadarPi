/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   radar.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 27 August 2019, 09:04
 */

/*
 *  Structure
 *      functions include gpio_control & spi_comms (or ioctl_spi_comms) in their routines
 * 
 *      ALl functions are listed here
 */

//ToDo: Update headers for all files based on new template.

#ifndef RADAR_H
#define RADAR_H

#include    "adcFunctions.h"
#include    "gainFunctions.h"
#include    "gpioFunctions.h"
#include    "ledControl.h"
#include    "rdr_utilities.h"


/*! *****************************************************************************
 * Overview:  Return the software version
 *  
 * This method returns the current software version
 *
 * param[out]    version : string containing the full version size 
 *
 * return EXIT_SUCCESS         : success
 ******************************************************************************/
int versionInfo(char *version);

#endif /* RADAR_H */

