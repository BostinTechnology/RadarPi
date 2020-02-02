/* 
 * File:   radar.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 27 August 2019, 09:04
 * 
 * This is the main include file to be used by any external calling program
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 */

//ToDo: Update headers for all files based on new template.

#ifndef RADAR_H
#define RADAR_H

#include    "adcFunctions.h"
#include    "gainFunctions.h"
#include    "gpioFunctions.h"
#include    "ledControl.h"
#include    "filterFunctions.h"
#include    "rdr_gpio_control.h"
#include    "icogLs1Functions.h"


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

