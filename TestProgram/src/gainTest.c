/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   gainTest.c
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 12 January 2019, 22:56
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
//#include "../inc/gainTest.h"
#include "../../common/inc/gainFunctions.h"


void setGainValue(void) {
	
	int				i;
	char			option[5];
	int				choice;
	CommsRetCode	ret;
	
	ret = gainSPiInitialisation();
	
	if (ret != ERR_NONE) {
		return;
	}
	
	printf("Choose the Gain Setting desired:\n\n");
	printf("Choice	Gain Value\n");
	for(i=0; i < qtyGainValues; i++) {
		printf("%d	-	%s\n", i, gainValues[i].description);
	};
	printf("99	-	return to main menu\n");
	do {
		fgets(option, 5, stdin);
		//getchar();			//consumes the extra enter - not sure this is needed
		choice = atoi (option);
		//printf("DEBUG: Choice Entered:%d\n", choice);
		if (choice < 0) strcpy(option, "\0"); //option[0]="\0";			//Set option back to an empty string
		else if (choice >= 0 && choice <= qtyGainValues) {
			//printf("DEBUG: Setting Gain Control of %d\n", gainValues[choice].value);
			setGainControl(gainValues[choice].value);
			printf("Gain has been set\n\n");
		}
	} while (choice != 99);
	
	
	return;
};
