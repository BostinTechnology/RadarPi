
 /******************************************************************************
  *
  * Example software provided by Bostin Technology Ltd
  * 
  * Reads and decodes the analogue signals received for the Radar module
  *
  * This software comes with no warrently and is provided as a demo application
  * for use with the Bostin Technology RadarPi
  *
  * For more information    www.Cogniot.eu
  *
  ******************************************************************************/


/*
******************************************************************************
* TYPE Definitions
******************************************************************************
*/

typedef uint16_t      RetCode;          /* Standard Return Code type from function. */


/*
******************************************************************************
* Enumerations
******************************************************************************
*/

enum {
    ERR_NONE                              =  0, /*!< no error occurred */

};

/*!
 *****************************************************************************
 * Overview:  Read the values from the analogue port continually
 *  
 * This method reads the values from the analogue port for the radar values and
 * displays them on the screen
 *
 * param[in/out] ?? : None 
 *
 * return NOTHING         : No response
 *****************************************************************************
 */
void readValuesContinously(void);
