/* 
 * File:   radar.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 25 September 2019, 21:01
 * 
 * Example code for radar pi
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
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/radar.h"


int versionInfo(char *version) {
    
    char    ver[] =  "0.1.0";

    strcat(version, ver);
    
    return EXIT_SUCCESS;
}