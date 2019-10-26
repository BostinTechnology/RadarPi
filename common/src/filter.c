 /* File:   filter.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 15 September, 2019
 * 
 * Example code to perform software filtering
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 */
#include "../inc/filter.h"


#define NZEROS 4
#define NPOLES 4


static float xv[NZEROS+1], yv[NPOLES+1];

void	init_filter (void)
{
	int	count;

	for (count = 0; count < NZEROS + 1; count++)
	{
		xv[count] = 0;
	}
	
	for (count = 0; count < NPOLES + 1; count++)
	{
		yv[count] = 0;
	}
	
}

short highpass_filter (short next_sample)
{ 
	xv[0] = xv[1]; xv[1] = xv[2]; 
	xv[2] = (float) next_sample;
	yv[0] = yv[1]; yv[1] = yv[2]; 
	
	yv[2] = (xv[0] + xv[2]) - xv[1] - xv[1]
		+ ( -0.8752145483 * yv[0]) + (  1.8668922797 * yv[1]);
  
	return (short) yv[2];
}

short notch_filter_100 (short next_sample)
{ 
	xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4]; 
  xv[4] = next_sample;
  yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4]; 
  yv[4] =   (xv[0] + xv[4]) -   3.8743815898 * (xv[1] + xv[3]) +   5.7527081759 * xv[2]
                     + ( -0.9858833621 * yv[0]) + (  3.8332644592 * yv[1])
                     + ( -5.7119092296 * yv[2]) + (  3.8606110802 * yv[3]);
        
	return (short) yv[4];
}

short notch_filter_120 (short next_sample)
{ 
	xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4]; 
  xv[4] = next_sample;
  yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4]; 
	yv[4] =   (xv[0] + xv[4]) -   3.8195064311 * (xv[1] + xv[3]) +   5.6471573442 * xv[2]
                     + ( -0.9858833621 * yv[0]) + (  3.7789716667 * yv[1])
                     + ( -5.6071060574 * yv[2]) + (  3.8059309614 * yv[3]);
        
	return (short) yv[4];
}

