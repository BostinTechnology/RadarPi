 /* File:   filter.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 15 September, 2019
 * 
 * Example header file to perform software filtering
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 */



short   highpass_filter (short next_sample);
short   notch_filter_100 (short next_sample);
short   notch_filter_120 (short next_sample);
void	init_filter (void);




