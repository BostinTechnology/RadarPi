/* 
 * File:   fileHandling.c
 * 
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 19 January 2020, 16:42
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

#include    <string.h>
#include    <stdbool.h>
#include    <time.h>
#include    <unistd.h>

#include    "../inc/fileHandling.h"

 
int checkIfFileExists(char *filename) {
     
    int     response;
    int     status;
    char    fullfilename[MAX_FILE_LENGTH+1];
    
    fullfilename[0]  = '\0';

    // Check if file already exists
    strcat(fullfilename, DATA_DIRECTORY);
    strcat(fullfilename, filename);
    response =  access(fullfilename, F_OK);
    if (response == 0) {
        // File exists and can be written to
        status = ERR_FILE_EXISTS;
    }
    else {
        status = FILE_OPERATION_SUCCESS;
    };
    
     // Return 0 = success
     return status;
};

int addFileHeaderInfo(FILE *fpointer) {
    
    int check = 0;
    time_t  now;
    struct tm *timenow = localtime(&now);

    printf("In add file header info\n");

    
    // Add Header Info
    check = fprintf(fpointer, "Radar Pi Test Results File\n");
    if (check != strlen("Radar Pi Test Results File\n")) {
        printf("Unable to write to file\n");
        return ERR_UNABLE_TO_WRITE_TO_FILE;
    };
    fprintf(fpointer, "==========================\n");
    fprintf(fpointer, "\n");
    fprintf(fpointer, "Date:%2d:%2d:%2d  ", timenow->tm_mday, timenow->tm_mon, timenow->tm_year);
    fprintf(fpointer, "Time:%2d:%2d:%2d\n", timenow->tm_hour, timenow->tm_min, timenow->tm_sec);
    fprintf(fpointer, "\n");
    
    printf("returning header info status:%d\n", FILE_OPERATION_SUCCESS);

    return FILE_OPERATION_SUCCESS;
};
 
int openTestResultsFile(FILE *fpointer, char *filename) {

    int     status = 0;
    char    fullfilename[MAX_FILE_LENGTH+1];
    
    fullfilename[0]  = '\0';

    // Check filename is within limits
    if ((strlen(filename) > MAX_FILE_LENGTH) && (strlen(filename) < MIN_FILE_LENGTH)) {
        printf("Filename invalid:%s", filename);
        return ERR_FILE_WRONG_LENGTH;
    };

    if (checkIfFileExists(filename)) {
        printf("File already exists, cannot continue\n");
        return ERR_FILE_EXISTS;
    };
        

    // Open File,once I've created the full name inc directory
    strcat(fullfilename, DATA_DIRECTORY);
    strcat(fullfilename, filename);
    fpointer = fopen(fullfilename, "w");
    if (fpointer == NULL) {
        printf("Failed to open the file %s for writing in directory %s\n", filename, DATA_DIRECTORY);
        printf("fp not null\n");
        return ERR_UNABLE_TO_OPEN_FILE;
    };
     
    // Add Header Info
    printf("adding header info\n");
    status += addFileHeaderInfo(fpointer);

    printf("returning:%d\n", status);
    
    // Return status
    return status;
    
};

int addTestResultToFile(FILE *fpointer, char *testdata) {
    
    int writeok = 0;

    // Attempt to write to file
    writeok = fprintf(fpointer, strcat(testdata, "\n"));
    
    // Check if it is successful, if not return error
    if (writeok != strlen(testdata)) {
        printf("Unable to write test datta to file : %s", testdata);
        return ERR_UNABLE_TO_WRITE_TO_FILE;
    };
    
    // Return status
    return FILE_OPERATION_SUCCESS;
};

int closeTestResultsFile(FILE *fpointer) {
    
    int closeok = 0;
    time_t  now;
    struct tm *timenow = localtime(&now);
    
    // Add Header Info
    closeok = fprintf(fpointer, "End of test cycle\n");
    if (closeok != strlen("End of test cycle\n")) {
        printf("Unable to close the file\n");
        return ERR_UNABLE_TO_WRITE_TO_FILE;
    };
    fprintf(fpointer, "==========================\n");
    fprintf(fpointer, "\n");
    fprintf(fpointer, "Date:%2d:%2d:%2d  ", timenow->tm_mday, timenow->tm_mon, timenow->tm_year);
    fprintf(fpointer, "Time:%2d:%2d:%2d\n", timenow->tm_hour, timenow->tm_min, timenow->tm_sec);
    fprintf(fpointer, "\n");

    // Close the file, if not return error
    closeok = fclose(fpointer);
    if (closeok != 0) {
        closeok = ERR_UNABLE_TO_CLOSE_FILE;
    };
    // Return status
    return closeok;
};
