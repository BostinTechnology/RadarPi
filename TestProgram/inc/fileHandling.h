/* 
 * File:   fileHandling.h
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

#ifndef FILEHANDLING_H
#define FILEHANDLING_H

#include <stdio.h>
 
#define         DATA_DIRECTORY      "testfiles/"
#define         MAX_FILE_LENGTH     20
#define         MIN_FILE_LENGTH     5 


#define         FILE_OPERATION_SUCCESS      0
#define         ERR_FILE_WRONG_LENGTH       1
#define         ERR_UNABLE_TO_OPEN_FILE     2
#define         ERR_FILE_EXISTS             3
#define         ERR_UNABLE_TO_WRITE_TO_FILE 4
#define         ERR_UNABLE_TO_CLOSE_FILE    5
#define         ERR_UABLE_TO_CREATE_FILE    6


/*!**************************************************************************
 * Overview:  Check if the file exists and return the status
 *  
 * Description: Given the filename, check if the file exists
 *
 * Parameters:
 * param[in] filename : The name of the file INCLUDING path
 *
 * return  status     : 0 - file DOESN'T exist ok
 *                    : 1 - file exists  
 ****************************************************************************/
int checkIfFileExists(char *filename);

/*!**************************************************************************
 * Overview:  Open the file and return the pointer
 *  
 * Description: Open the file, add the header info and return the file pointer.
 *              Automatically adds date / time to record to the filename
 *              and within the file as part of the header
 *
 * Parameters:
 * param[in] fpointer : The pointer to be used for the file handler
 *      [in] filename : A char string of the filename
 *
 * return  status     : 0 - opened ok
 *****************************************************************************/
int openTestResultsFile(FILE **fpointer, char *filename);

/*!**************************************************************************
 * Overview:  Add the header information into the file
 *  
 * Description: With the file already open, add the header info and return
 *              fiel success
 *
 * Parameters:
 * param[in] fpointer : The pointer to be used for the file handler
 *
 * return  status     : 0 - data added
 *****************************************************************************/
int addFileHeaderInfo(FILE **fpointer);;

/*!**************************************************************************
 * Overview:  Add a test result to the file and return the status
 *  
 * Description: Given the test data, add it to the results file
 *
 * Parameters:
 * param[in] fpointer : The pointer to be used for the file handler
 *      [in] testdata : A char string of the data to add
 *
 * return  status     : 0 - return ok
 ****************************************************************************/
int addTestResultToFile(FILE **fpointer, char *testdata);

/*!**************************************************************************
 * Overview:  Close the file and return the status
 *  
 * Description: Add the footer details, Close the file and return the status.
 *              Automatically adds date / time at the end of the test
 *
 * Parameters:
 * param[in] fpointer : The pointer to be used for the file handler
 *
 * return  status     : 0 - closed ok
 *****************************************************************************/
int closeTestResultsFile(FILE **fpointer);


#endif /* FILEHANDLING_H */
