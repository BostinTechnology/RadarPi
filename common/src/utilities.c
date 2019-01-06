/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utilities.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 08 December 2018, 21:15
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>

volatile int systemloop=true;

void waitTimer(float duration)
{
    time_t currenttime, endtime;

    // load the current time into the counter
    currenttime = clock();
    endtime = currenttime + (duration * CLOCKS_PER_SEC);
    
    do {
        currenttime = clock();
    } while (currenttime < endtime);
	
	return;
}


void sigHandler(int sig)
{
	printf("Got Signal %d\n",sig);
	switch (sig){
		case SIGHUP:
			// Sig HUP, Do a reload
			printf("Sig: Got SIGHUP\n");
			break;
		case SIGINT: // 2
			// Interrupt (Ctrl c From command line) - Graceful exit
			printf("Sig: Got SIGINT - Ending Routine\n");
			systemloop=false;
			break;
		case 15:
			// TERM
			printf("Sig: Got SIGTERM\n");
			break;
		case 16:
			// USR1
			printf("Sig: Got SIGUSR1\n");
			break;
		case 17:
			// USR2
			printf("Sig: Got SIGUSR2\n");
			break;
		default:
			// other interrupt
			printf("Got un-handled interrupt\n");
			break;
			
	}
	return;
}


void sigSetup(void)
{
	signal(SIGHUP,sigHandler);
	signal(SIGTERM,sigHandler);
	signal(SIGUSR1,sigHandler);
	signal(SIGUSR2,sigHandler);

	signal(SIGQUIT,sigHandler);
	signal(SIGINT,sigHandler);
	signal(SIGKILL,sigHandler);
	return;
}
