/* 
 * File:   utilities.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 08 December 2018, 21:15
 * 
 * Example header file for the general utilities required
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 */

#ifndef UTILITIES_H
#define UTILITIES_H

extern volatile int systemloop;

// function
void waitTimer(float duration);				//wait for the given time (float)
void sigHandler(int sig);
void sigSetup(void);

#endif /* UTILITIES_H */

