/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rdr_utilities.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 08 December 2018, 21:15
 */

#ifndef RDR_UTILITIES_H
#define RDR_UTILITIES_H

extern volatile int systemloop;

// function
void waitTimer(float duration);				//wait for the given time (float)
void sigHandler(int sig);
void sigSetup(void);

#endif /* RDR_UTILITIES_H */

