/* 
 * File:   mainTestProgram.c
 * 
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 08 December 2018, 19:15
 * 
 * Example code for testing the manufacturing of the Radar Pi
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */
 
 /*!****************************************************************************
  * Test Program Requirements - Defined 10/01/20
  * 
  * Test Routine
  *     Test the LEDS, cycle through each to confirm functionality              DONE
  *         CTRL-C to continue with test
  *     For each gain value, display the readings below
  *         Light Sensor Value, ADC Output, Digital Frequency, Gain Setting
  *         Flash the LED to indicate Gain change
  *     	CTRL-C to move to next part of the test
  *     Write to and read from the E2PROMS
  *         The one on the Light Sensor
  *         The one on the HAT
  *         Auto Move to next step
  *     Range Test
  *         For each gain value, flash LED When Sensed
  *         CTRL-C to move to the next part of the test
  *         Set gain to maximum, flash LED when detection
  *             LED1 flash when any activity
  *             LED2 flash above threshold
  * 
  * Need to capture data for each test and write it to a file with identifier
  * 
  ******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#include "../inc/utilities.h"
#include "../inc/fileHandling.h"
#include "../inc/mainTestProgram.h"
#include "../../common/inc/radar.h"

void splashScreen(void) {
    printf("\n***********************************************\n");
    printf("*             Bostin Technology               *\n");
    printf("*                                             *\n");
    printf("*                  Radar Pi                   *\n");
    printf("*                                             *\n");
    printf("*          Production Test Routine            *\n");
    printf("*                                             *\n");
    printf("*        for more info www.cognIoT.eu         *\n");
    printf("***********************************************\n");
    return;
}

void helpScreen(void) {
        printf(" \n\n");
        printf("**************************************************************************\n");
        printf("Available commands: -\n\n");
        printf("f - Run Full Test Routine\n");
        printf("l - LED Test\n");
        printf("2 - E2PROM Test\n");
        printf("i - Light iCog Test\n");
        printf("d - Display readings Test\n");
        printf("r - Range Test\n");
        printf("h - Display the help screen\n");
        printf("e - Exit program \n");
        printf("\n");
        return;
}

void fullTestRoutine(void) {
    printf("To Be implemented\n");
    FILE    *ptr_testfile;
    char    testfilename[MAX_FILE_LENGTH];
    int         status;
    
    status = 0;
    
    strcpy(testfilename, "RadarPi");
    
    status = openTestResultsFile(&ptr_testfile, testfilename);

    
    if (status == 0) {
        // Add Tests into here
        status = addTestResultToFile(&ptr_testfile, testfilename);
    }
        

    if (status == 0) {
        status = closeTestResultsFile(&ptr_testfile);
    }
    
    return;
    
}

void cycleLEDs(void) {

    int status = LED_ERR_NONE;
    char        option[2];
    
    systemloop = true;
	status = ledSetup();
    if (status == LED_ERR_NONE) {
        printf("CTRL - C to end loop\n");
        controlTriggeredLED(LED_OFF);
        controlRunningLED(LED_OFF);
        controlMonitoringLED(LED_OFF);

        do {
            printf("Running LED\n");
            status += controlTriggeredLED(LED_OFF);
            status += controlRunningLED(LED_ON);
            usleep(LED_TEST_SPEED);

            printf("Monitoring LED\n");
            status += controlRunningLED(LED_OFF);
            status += controlMonitoringLED(LED_ON);
            usleep(LED_TEST_SPEED);

            printf("Triggered LED\n");
            status += controlMonitoringLED(LED_OFF);
            status += controlTriggeredLED(LED_ON);
            usleep(LED_TEST_SPEED);


        } while ((systemloop) && (status == LED_ERR_NONE));
    }
    if (status == LED_ERR_NONE) {
        printf("Did all three LEDs work correctly (y/n)? -> ");

        option[0] = getchar();
        getchar();  // have to press enter and this consumes the enter character
        if (strncmp(option,"y",1) == 0) {
            printf("LED test passed\n");
        }
        else {
            printf("LED test FAILED\n");
        }            
        controlTriggeredLED(LED_OFF);
        controlRunningLED(LED_OFF);
        controlMonitoringLED(LED_OFF);
    }
    else {
        printf("LED test FAILED\n");
    }
	return;
};


void e2promTest(void) {
    printf("To Be implemented\n");
    
    return;
    
}

// Routine added to provide testing
int lightReading(float *reading) {
    printf("Not Yet completed, in progress\n");
    
    *reading = 0.12;
    return 0;
}

void displayReadingsTest(void) {
    // Light Sensor Value, ADC Output, Digital Frequency, Gain Setting
    int         status;
    float       light = 0.0, adc = 0.0, digital = 0.0;
    int         gaincount = 0, qtygainreadings = 4;
    int         testgainvalues[4][2] = { {0b0000, 1}, {0b0001, 10}, {0b0100, 40}, {0b1000, 157}	};
    time_t	    currenttime, starttime;
    
    systemloop = true;
    printf("Display Readings Test\n");
    
    printf("CTRL - C to end loop\n");
    starttime = clock();
    status = gainSPiInitialisation();
    status += setGainControl(testgainvalues[gaincount][0]);
    status += gainSPiEnd();

    do {

        status += lightReading(&light);
        status += readVoltage(&adc);
        status += returnFullFrequency(&digital, IF_OUT_DIGITAL); //IF_OUT_TO_PI);
        printf("\rLight:%10.3f  ADC:%10.6f  Digital:%11.6f  Gain:%3d", light, adc, digital, testgainvalues[gaincount][1]);
        fflush(stdout);     // Test if this line is required or if the \n above works

        currenttime = clock();
        if (currenttime > (starttime + (TEST_TIMEOUT * CLOCKS_PER_SEC))) {
            gaincount++;
            if (gaincount >= qtygainreadings) {
                gaincount = 0;
            }
            status += adcSPiEnd();
            status += gainSPiInitialisation();
            status += setGainControl(testgainvalues[gaincount][0]);
            status += gainSPiEnd();
            status += adcSPiInitialisation();
        
            starttime = clock();
        }

    } while ((systemloop) && (status == ERROR_NONE));
    return;
    
}

void rangeTest(void) {
    // For a set of gain values, measure the voltage for different distances
    // Loop for the gain values
    //  measure the adc and if above threshold, flash the led 
    // ADC Output, Digital Frequency, Gain Setting
    int         status;
    float       adc = 0.0, digital = 0.0;
    int         gaincount = 0, qtygainreadings = 4;
    int         rangecount = 0, qtyrangevalues = 4;
    int         testgainvalues[4][2] = {{0b0000, 1}, {0b0001, 10}, {0b0100, 40}, {0b1000, 157}};
    float       distadcfreq[4][3] = {{0.5,2.3, 500}, {1,2.5, 500}, {5,2.5, 500}, {10, 2.5, 500} };     //Distance <> adc <> frequency values
    time_t	    currenttime, starttime;
    bool        testpassed;
    
    systemloop = true;
    
    printf("CTRL - C to end loop\n");

    if (ledSetup()) {
        controlRunningLED(LED_OFF);
        controlMonitoringLED(LED_OFF);
        controlTriggeredLED(LED_OFF);
    }
    else {
        printf("Unable to control LEDs, test aborted\n");
        return;
    }
    do {
        // Turn the LEDs on for the start of the loop
        status += controlRunningLED(LED_ON);
        status += controlMonitoringLED(LED_ON);
        // Set the various settings
        status += adcSPiEnd();
        status += gainSPiInitialisation();
        status += setGainControl(testgainvalues[gaincount][0]);
        status += gainSPiEnd();
        status += adcSPiInitialisation();
        
        // Sit in inner loop waiting for trigger.
        starttime = clock();
        testpassed = false;
        do {
            status += readVoltage(&adc);
            status += returnFullFrequency(&digital, IF_OUT_DIGITAL); //IF_OUT_TO_PI);

            printf("\rDistance:%4.0f  ADC:%10.6f  Digital:%11.6f  Gain:%3d", 
                    distadcfreq[rangecount][0], adc, digital, testgainvalues[gaincount][1]);
            fflush(stdout);     // Test if this line is required or if the \n above works
            
            // Validate the results
            if (adc > distadcfreq[rangecount][1]) {
                printf("triggered ADC");
                controlMonitoringLED(LED_OFF);
                controlTriggeredLED(LED_ON);
                usleep(250);
                controlMonitoringLED(LED_ON);
                controlTriggeredLED(LED_OFF);
                testpassed = true;
            };
            if (digital > distadcfreq[rangecount][2]) {
                printf("triggered Frequency");
                controlMonitoringLED(LED_OFF);
                controlTriggeredLED(LED_ON);
                usleep(250);
                controlMonitoringLED(LED_ON);
                controlTriggeredLED(LED_OFF);
                testpassed = true;
            };
            currenttime = clock();
        } while ((testpassed == false) || (currenttime < (starttime + (TEST_TIMEOUT * CLOCKS_PER_SEC))));
        
        printf("\nNext gain value\n\n");

        gaincount++;
        if (gaincount >= qtygainreadings) {
            printf("Cycling back round, starting again\n");
            printf("CTRL - C to end test");
            gaincount = 0;
        }
        if (testpassed) {
            rangecount ++;
            if (rangecount >= qtyrangevalues) {
                printf("Cycling back round, starting again\n");
                printf("CTRL - C to end test");
                rangecount = 0;
            }
            testpassed = false;
        }
        
    } while ((systemloop) && (status == ERROR_NONE));

    return;
    
}

void debugtest() {
    // Routine to test new functionality as it is added
    
    FILE    *ptr_testfile;
    char    testfilename[15];
    int         status;
    
    status = 0;
    
    strcpy(testfilename, "testfilename");
    
    status = openTestResultsFile(&ptr_testfile, testfilename);
    printf("Status after opening file:%d\n", status);
    
    if (status == 0) {
        status = addTestResultToFile(&ptr_testfile, testfilename);
    }
    printf("Status after adding results to the file:%d\n", status);
        

    if (status == 0) {
        status = closeTestResultsFile(&ptr_testfile);
    }
    printf("Status after closing the file:%d\n", status);
    
    return;
}

void icogTest() {
    
    int     i2cbus = 0;
    int     status;
    float   luxvalue = 0.0;
    int     adcvalues[4] = {ICOG_SET_ADC_4,ICOG_SET_ADC_8,ICOG_SET_ADC_12,ICOG_SET_ADC_16};
    int     fsrvalues[4] = {ICOG_SET_FSR_1K,ICOG_SET_FSR_4K,ICOG_SET_FSR_16K,ICOG_SET_FSR_64K};
    int     adccount = 0;
    int     fsrcount = 0;
    int     luxcount = 0;
    float   luxaverage = 0.0;
    float   luxvalues[4][4];
    int     adcmodes[4] = {ICOG_ADC_MODE_2_4, ICOG_ADC_MODE_2_8, ICOG_ADC_MODE_2_12, ICOG_ADC_MODE_2_16};
    
    printf("reading . . . \n");
    status = icogI2CInitialisation (&i2cbus);
    if (status != ICOG_EXIT_SUCCESS) {
        printf("Failed to initialise iCog, please check.\n");
        return;
    };

    do {
        //printf("Set ADC Resolution");
        status = icogSetADCResolution(&i2cbus, adcvalues[adccount]);
        if (status != ICOG_EXIT_SUCCESS) {
            printf("Failed to set ADC RESOLUTION of iCog, please check.\n");
            return;
        };
        do {
            
            //printf("Set FSR Range\n");
            status = icogSetFSRRange(&i2cbus, fsrvalues[fsrcount]);
            if (status != ICOG_EXIT_SUCCESS) {
                printf("Failed to set FSR Range of iCog, please check.\n");
                return;
            };

            //printf("Setting ALS Sensor\n");
            status= icogSetALSContinuousMode(&i2cbus);
            if (status != ICOG_EXIT_SUCCESS) {
                printf("Failed to set ALS mode of iCog, please check.\n");
                return;
            };

            luxcount = 0;
            luxaverage = 0.0;
            do {
                
                //printf("Reading Lux Value\n");
                status = icogCalculateLux(&i2cbus, &luxvalue);
                if (status != ICOG_EXIT_SUCCESS) {
                    printf("Failed to read LUX value of iCog, please check.\n");
                    return;
                }
                else {
                    //printf("Lux Value:%f\n", luxvalue);
                    luxaverage += luxvalue;
                }
                luxcount ++;
            } while (luxcount < 5);
            luxaverage = luxaverage / 5;
            luxvalues[fsrcount][adccount] = luxaverage;
            //printf("Lux Average:%f\n", luxaverage);

            //printf("Turning Off Sensor\n");
            status= icogTurnOffSensor(&i2cbus);
            if (status != ICOG_EXIT_SUCCESS) {
                printf("Failed to turn off iCog, please check.\n");
                return;
            };
            fsrcount ++;

        } while (fsrcount < 4);
        fsrcount = 0;
        adccount ++;

    } while (adccount <4);
    status = icogI2CEnd();
    if (status != ICOG_EXIT_SUCCESS) {
        printf("Failed to end comms with the iCog, please check.\n");
        return;
    };

    printf("R E S U L T S\n");
    printf("=============\n");
    adccount = 0;
    fsrcount = 0;
    printf("ADC \\ FSR | %11d | %11d | %11d | %11d\n", ICOG_FSR_READING_1K, ICOG_FSR_READING_4K, ICOG_FSR_READING_16K, ICOG_FSR_READING_64K); 
    do {
        printf("    %5d ", adcmodes[adccount]);
        do {
            printf("\ %11f ", luxvalues[fsrcount][adccount]);
            fsrcount ++;
        } while (fsrcount < 4);
        fsrcount = 0;
        printf("\n");
        adccount ++;
    } while (adccount < 4);
    return;    
}

int main(int argc, char** argv) {

    char option;                        // Used for menu choices


    // setup the interrupt handling
    sigSetup();
    setupGpioFunctions();

    splashScreen();

    // main menu
    helpScreen();

    //set the default gain
    setGainDefaultValue();

    do {
        printf("Please select command (h for help) -> ");

        option = getchar();
        getchar();  // have to press enter and this consumes the enter character

        switch (option)
        {
            case 'f':
                /* Run Full Test Routine */
                fullTestRoutine();
                break;
            case 'l':
                /* LED Test */
                cycleLEDs();
                break;

            case '2':
                /* E2PROM Test */
                e2promTest();
                break;

            case 'i':
                /* E2PROM Test */
                icogTest();
                break;

            case 'd':
                /* Display readings Test */
                displayReadingsTest();
                break;

            case 'r':
                /* Range Test */
                rangeTest();
                break;

            case 'h':
                /* Display the help screen */
                helpScreen();
                break;

            case 'e':
                printf("Exiting.......\n");
                option = 'e';
                break;
            
            case 'x':
                printf("Debug Bit.......\n");
                debugtest();
                break;
            

            default:
                printf("Unrecognised command!:>%c<\n", option);
                break;
                
       }
       fflush (stdin) ;
        printf("\n");
    } while(option != 'e');
    
    return 0;
}

