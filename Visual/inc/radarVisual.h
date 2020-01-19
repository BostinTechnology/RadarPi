/* 
 * File:   radarVisual.h
 * 
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 13 April 2019, 16:14
 * 
 * Example code for providing a full GUI interface to read and configure
 * the Radar PI
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
 */

#ifndef RFIDVISUAL_H
#define RFIDVISUAL_H

#include <stdbool.h>
#include "../inc/linkedList.h"
#include <gtk-3.0/gtk/gtk.h>
#include "../../common/inc/radar.h"


struct app_widgets {
    // All the widgets on the Glade form go into here
    GtkWidget       *w_canvas_graph;
    GtkWidget       *w_btn_startstop;    
    GtkWidget       *w_btn_set_gain;
    GtkWidget       *w_scale_gainctrl;
    GtkWidget       *w_radbut_op_to_pi;
    GtkWidget       *w_radbut_digital;
    GtkWidget       *w_radbut_adc;
    GtkAdjustment   *w_adj_gainctrl;
    GtkAdjustment   *w_adj_dataspeed;
    GtkAdjustment   *w_adj_refreshspeed;
    GtkSpinButton   *w_spn_dataspeed;
    GtkSpinButton   *w_spn_refreshspeed;
    GtkWidget       *w_txt_mode_info;
    GtkWidget       *w_txt_gain_setting;
    GtkWidget       *w_txt_status;
    GtkWidget       *w_lbl_user_message;
    // Plus other variables I want to use
    bool            running;                    // When true, gathers data to show in the graph
    int             gain_value;                 // The gain value from the slider
    // also the SPI connection
    int             SPiconn;
    Linkedlist      list;
    int             debug;
} ;

/* Debug levels in use
 * 0 = No Debug
 * 1 = All Messages
 * 2 = Error messages only
 * 3 = Program failures only
 */
#define     DEBUG0  0
#define     DEBUG1  1
#define     DEBUG2  2
#define     DEBUG3  3

// Used by Cairo draw.
#define ZOOM_X  100.0
#define ZOOM_Y  100.0

#define GAIN_RANGE     

//Timers for the application refresh / data collection - all in mS
#define DEFAULT_SCREEN_REFRESH_TIMER    333
#define DEFAULT_DATA_REFRESH_TIMER      333

#define MAX_VOLTAGE             3.3
#define MIN_VOLTAGE             0.0

//ToDo: improve the commentary for the functions


// 
void on_main_application_window_destroy() ;


#endif /* RFIDVISUAL_H */

