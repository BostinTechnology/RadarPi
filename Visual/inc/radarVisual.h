/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   rfidVisual.h
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 13 April 2019, 16:14
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
    GtkWidget       *w_radbut_raw;
    GtkWidget       *w_radbut_digital;
    GtkWidget       *w_radbut_adc;
    GtkAdjustment   *w_adj_gainctrl;
    GtkWidget       *w_txt_mode_info;
    GtkWidget       *w_txt_gain_setting;
    GtkWidget       *w_txt_status;
    // Plus other variables I want to use
    bool            running;                    // When true, gathers data to show in the graph
    int             gain_value;                 // The gain value from the slider
    // also the SPI connection
    int             SPiconn;
    Linkedlist      list;
} ;

// Used by Cairo draw.
#define ZOOM_X  100.0
#define ZOOM_Y  100.0

#define GAIN_RANGE     

//Timers for the application refresh / data collection - all in mS
#define SCREEN_REFRESH_TIMER    333
#define DATA_REFRESH_TIMER      333

#define MAX_VOLTAGE             3.3
#define MIN_VOLTAGE             0.0

//ToDo: improve the commentary for the functions


int open_serial_port(struct app_widgets *widget);

// calls the library and gets the version info
void on_main_application_window_destroy() ;


#endif /* RFIDVISUAL_H */

