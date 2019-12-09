 /* File:   filter.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 15 September, 2019
 * 
 * Example header file to perform software filtering to cater for interference
 * when capturing values
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 */


/*
 *****************************************************************************
 * Overview: Provides a hioh pass Filer.
 * It will require a number of values to be given before it starts to return
 * the filtered value. Until it has received enough values, it will return zero.
 *
 * param[in] next_sample : The next value to be added for filtering 
 *
 * return the filtered value (or zero until enough values processed)
 *****************************************************************************
 */
float   highpass_filter (float next_sample);

 /*
 *****************************************************************************
 * Overview: Provides a software Notch Filer for 100Hz.
 * It will require a number of values to be given before it starts to return
 * the filtered value. Until it has received enough values, it will return zero.
 *
 * param[in] next_sample : The next value to be added for filtering 
 *
 * return the filtered value (or zero until enough values processed)
 *****************************************************************************
 */
float   notch_filter_100 (float next_sample);

/*
 *****************************************************************************
 * Overview: Provides a software Notch Filer for 120Hz.
 * It will require a number of values to be given before it starts to return
 * the filtered value. Until it has received enough values, it will return zero.
 *
 * param[in] next_sample : The next value to be added for filtering 
 *
 * return the filtered value (or zero until enough values processed)
 *****************************************************************************
 */
float   notch_filter_120 (float next_sample);

/*
 *****************************************************************************
 * Overview: Initialises the software filtering.
 *
 * param[in/out] none 
 *
 * return - Nothing
 *****************************************************************************
 */
void	init_filter (void);




