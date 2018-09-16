#!/usr/bin/env python3
"""
    This program provides a demo interface that is designed to show the capabilities
    of the Radar module

    This should be run using the Pi Display module

    
"""

from tkinter import *
from tkinter.ttk import *
from tkinter import messagebox
import logging
import logging.config
import dict_Logging
import threading
import random
import queue
import time
import sys
import RPi.GPIO as GPIO


import SystemSettings as SS

# Graph coordinates
#   50,10   _____________________
#           |..|..|..|..|..|..|..|
#           |..|..|..|..|..|..|..|      Each '|' is 20 pixels across
#           |..|..|..|..|..|..|..|      there are 30 vertical segments
#           |..|..|..|..|..|..|..|
#           |..|..|..|..|..|..|..|      Each '.' is 20 pixels down
#           |..|..|..|..|..|..|..|      there are 14 horizontal segments
#           |..|..|..|..|..|..|..|
#           |__|__|__|__|__|__|__| 650, 290
#
START_X = 50
START_Y = 10
END_X = 650
END_Y = 290
GRAPH_STEP = 20
START_LEGEND_Y = 5                  # Where the legend starts for the Y axis
CANVAS_MARGIN = 10                  # The border around the edge
CANVAS_WIDTH = (END_X) + (2 * CANVAS_MARGIN)      # Calculated Canvas width
CANVAS_HEIGHT = (END_Y) + (2 * CANVAS_MARGIN)     # Calculated canvas height

MAX_LENGTH = 100        # The maximum number of values to be displayed on the graph


class RadarDisplay(Frame):
    """
    Provide teh display part of the application. Data is passed to it from the
    main class below in the form of a queue
    """
    def __init__(self, master, queue, exit_command, refresh_command):
        self.log = logging.getLogger()
        self.log.debug("[Disp] cls_RadarDisplay initialised")
        Frame.__init__(self,master)
        self.master = master
        self.queue = queue
        self.exit_command = exit_command
        self.refresh_command = refresh_command

        self.log.info("[Disp] Starting Main Frame")
        
        self.trigger = StringVar()
        self.refresh_rate = IntVar()
        self.graph_max = IntVar()
        self.trigger_lvl = IntVar()
        
        # Removed as scale markers don't make sense with multiple lines
        self.y_max_scale_value = IntVar()
        self.y_min_scale_value = IntVar()
        
        self.running = False       # When true, data is being captured.
        self.refresh_rate.set(SS.DEFAULT_REFRESH_RATE)
        self.dataset = []           # The dataset being displayed and graphed
        for i in range(0,MAX_LENGTH):           # set all the values to zero to ensure full dataset used.
            self.dataset.append(0)
        self.trigger_lvl.set(SS.TRIGGER_LVL)
            
        self.trigger.set(SS.NOT_TRIGGERED)
        self.y_max_scale_value.set(SS.GRAPH_DEFAULT)
        self.y_min_scale_value.set(0)

        # Build the Triggering  frame
        trigger_frame = Frame(self)#, relief='ridge')
        self.trigger_lbl = Label(trigger_frame, textvariable=self.trigger, width=20, anchor="center") #, relief='sunken')
        self.trigger_lbl.grid(row=0, column=0)
        trigger_frame.grid(row=0, column=0, pady=10)

        # Build the Start Stop Frame
        startstop_frame = Frame(self)#, relief='ridge')
        self.startstop_button = Button(startstop_frame, text='Start/Stop', command=self.start_stop).grid(row=0, column=0, padx=20)
        startstop_frame.grid(row=0, column=1, padx=10)

        # Build the graph canvas picture
        graph_frame = Frame(self, relief='ridge')
        self.graph_canvas = Canvas(graph_frame, width=CANVAS_WIDTH, height=CANVAS_HEIGHT, background='#ffffff')
        self.graph_canvas.create_polygon(START_X,START_Y,END_X,START_Y,END_X,END_Y,START_X,END_Y, outline="green", fill="")
        for r in range(START_Y + GRAPH_STEP,END_Y,GRAPH_STEP):
            self.graph_canvas.create_line(START_X,r,END_X,r, fill="lightblue")
        for c in range(START_X + GRAPH_STEP,END_X,GRAPH_STEP):
            self.graph_canvas.create_line(c,START_Y,c,END_Y, fill="lightblue")

        # Graph axis labels
        x_max_label = Label(self.graph_canvas, text='Now') #, relief='sunken')
        x_max_label_window = self.graph_canvas.create_window(END_X-15, END_Y, anchor=NW, window=x_max_label)
        x_min_label = Label(self.graph_canvas, text='Oldest') #, relief='sunken')
        x_min_label_window = self.graph_canvas.create_window(START_X, END_Y, anchor=NW, window=x_min_label)
        # Removed as scale markers don't make sense with multiple lines
        y_max_label = Label(self.graph_canvas, textvariable=str(self.y_max_scale_value), width=5) #, relief='sunken')
        y_max_label_window = self.graph_canvas.create_window(START_LEGEND_Y, START_Y, anchor=NW, window=y_max_label)
        y_min_label = Label(self.graph_canvas, textvariable=str(self.y_min_scale_value), width=5) #, relief='sunken')
        y_min_label_window = self.graph_canvas.create_window(START_LEGEND_Y, END_Y-10, anchor=NW, window=y_min_label)
        
        self.graph_canvas.pack()
        graph_frame.grid(row=1, column=0)

        # Build the faster / slower frame
        fast_slow_frame = Frame(self)#, relief='ridge')
        self.graph_header_lbl = Label(fast_slow_frame, text="Graph Max", width=10, anchor="center") #, relief='sunken')
        self.graph_header_lbl.grid(row=0, column=0, padx=10)
        self.graph_units_lbl = Label(fast_slow_frame, text="(in Hz)", width=10, anchor="center") #, relief='sunken')
        self.graph_units_lbl.grid(row=1, column=0, padx=10)
        self.graph_value_lbl = Label(fast_slow_frame, textvariable=str(self.y_max_scale_value), width=10, anchor="center", relief='sunken')
        self.graph_value_lbl.grid(row=2, column=0, padx=10)
        self.graph_inc_button = Button(fast_slow_frame, text="INC", command=self.increase_max).grid(row=3, column=0)#, padx=10)
        self.graph_dec_button = Button(fast_slow_frame, text="DEC", command=self.decrease_max).grid(row=4, column=0)#, padx=10)
     
        self.refresh_header_lbl = Label(fast_slow_frame, text="Refresh Rate", width=10, anchor="center") #, relief='sunken'
        self.refresh_header_lbl.grid(row=6, column=0, padx=10)
        self.refresh_units_lbl = Label(fast_slow_frame, text="(in mS)", width=10, anchor="center") #, relief='sunken')
        self.refresh_units_lbl.grid(row=7, column=0, padx=10)
        self.refresh_value_lbl = Label(fast_slow_frame, relief='sunken', textvariable=str(self.refresh_rate), width=10, anchor="center")
        self.refresh_value_lbl.grid(row=8, column=0, padx=10)
        self.refresh_faster_button = Button(fast_slow_frame, text="INC", command=self.increase_speed).grid(row=9, column=0)#, padx=10)
        self.refresh_slower_button = Button(fast_slow_frame, text="DEC", command=self.decrease_speed).grid(row=10, column=0)#, padx=10)

        self.trigger_header_lbl = Label(fast_slow_frame, text="Trigger Lvl", width=10, anchor="center")
        self.trigger_header_lbl.grid(row=11, column=0, padx=10)
        self.trigger_units_lbl = Label(fast_slow_frame, text="(in Hz)", width=10, anchor="center")
        self.trigger_units_lbl.grid(row=12, column=0, padx=10)
        self.trigger_value_lbl = Label(fast_slow_frame, relief='sunken', textvariable=str(self.trigger_lvl), width=10, anchor="center")
        self.trigger_value_lbl.grid(row=13, column=0, padx=10)
        self.trigger_faster_button = Button(fast_slow_frame, text="INC", command=self.increase_trigger_lvl).grid(row=14, column=0)
        self.trigger_slower_button = Button(fast_slow_frame, text="DEC", command=self.decrease_trigger_lvl).grid(row=15, column=0)

        fast_slow_frame.grid(row=1, column=1)

        # Build the exit frame
        exit_frame = Frame(self) #,relief='ridge')
        self.exit_program = Button(exit_frame, text="Exit", command=self.exit_program).grid(row=0, column=1, padx=10)
        exit_frame.grid(row=2, column=1)

        # Put it all together on the screen
        self.pack(fill=BOTH, expand=NO)
        #self.after(100, self.main)      # was root.
        self.log.debug("[Disp] Main Frame Initialised")
        return

    def start_stop(self):
        """
        Toggle the start / stop functionality
        """
        self.log.debug("[DISP] Starting state of running:%s" % self.running)
        if self.running  == False:
            # If we get here and the program is not running, we need to reset it before starting
            self.log.debug("[DISP] Start Stop wasn't running so values are being reset:%s" % self.running)
            self.reset()
        self.running = not(self.running)
        self.log.debug("[DISP] Ending state of running:%s" % self.running)
        return

    def increase_trigger_lvl(self):
        """
        Increase the threshold for the trigger level
        """
        self.trigger_lvl.set(self.trigger_lvl.get() + SS.TRIGGER_INCREMENT)
        if self.trigger_lvl.get() > SS.MAX_TRIGGER_LVL:
            self.trigger_lvl.set(SS.MAX_TRIGGER_LVL)
        return

    def decrease_trigger_lvl(self):
        """
        Decrease the threshold for the trigger level
        """
        self.trigger_lvl.set(self.trigger_lvl.get() - SS.TRIGGER_INCREMENT)
        if self.trigger_lvl.get() < SS.MAX_TRIGGER_LVL:
            self.trigger_lvl.set(SS.MIN_TRIGGER_LVL)
        return
        
    def increase_speed(self):
        """
        Increase the reading speed
        """
        self.refresh_rate.set(self.refresh_rate.get() + SS.REFRESH_INCREMENT)
        if self.refresh_rate.get() > SS.MAX_REFRESH_RATE:
            self.refresh_rate.set(SS.MAX_REFRESH_RATE)
        self.refresh_command(self.refresh_rate.get())
        return

    def decrease_speed(self):
        """
        Decrease the reading speed
        """
        self.refresh_rate.set(self.refresh_rate.get() - SS.REFRESH_INCREMENT)
        if self.refresh_rate.get() < SS.MIN_REFRESH_RATE:
            self.refresh_rate.set(SS.MIN_REFRESH_RATE)
        self.refresh_command(self.refresh_rate.get())
        return

    def increase_max(self):
        """
        Increase the maximum graph value
        """
        self.y_max_scale_value.set(self.y_max_scale_value.get() + SS.GRAPH_INC)
        if self.y_max_scale_value.get() > SS.GRAPH_MAX:
            self.y_max_scale_value.set(SS.GRAPH_MAX)
        return

    def decrease_max(self):
        """
        Increase the maximum graph value
        """
        self.y_max_scale_value.set(self.y_max_scale_value.get() - SS.GRAPH_INC)
        if self.y_max_scale_value.get() < SS.GRAPH_MIN:
            self.y_max_scale_value.set(SS.GRAPH_MIN)
        
        return
    def reset(self):
        """
        Reset the valus back to the start for another dataset
        """
        self.dataset = []
        for i in range(0,MAX_LENGTH):           # set all the values to zero to ensure full dataset used.
            self.dataset.append(0)
        # Removed as scale markers don't make sense with multiple lines
        self.y_max_scale_value.set(SS.GRAPH_DEFAULT)
        self.y_min_scale_value.set(0)
        self.graph_canvas.delete('graphline')
        #clear the queue of data
#        self.queue.queue.clear()
        return

    def draw_graph(self,data_to_draw, line_no):
        """
        Draw the graph on the graph area
        Graph area is 0 - 20 sections wide, 0 - 13 high
        coord ranges 20 - END_X across, 20 - 280 up.
        """

        colours = ["red", "green", "blue", "cyan", "yellow", "magenta", "black", 'white']

        if line_no == 0:
            # If the line has been drawn before, delete it.
            if len(self.graph_canvas.find_withtag('graphline'))> 0:
                self.graph_canvas.delete('graphline')
        x_spacing = (END_X - START_X) / len(data_to_draw)       # Add 1 as

        # Auto graph scaling
#turned off
#        if self.y_max_scale_value.get() < max(data_to_draw):
#            self.y_max_scale_value.set(max(data_to_draw))
#        if self.y_min_scale_value.get() > min(data_to_draw):
#            self.y_min_scale_value.set(min(data_to_draw))

        # Set minimum for Y scale to zero
        self.y_min_scale_value.set(0)

        if (self.y_max_scale_value.get() - self.y_min_scale_value.get()) > 0:
            y_spacing = (END_Y - START_Y) / (self.y_max_scale_value.get() - self.y_min_scale_value.get())
        else:
            y_spacing = (END_Y - START_Y)
        self.log.debug("Spacing (x,y):%s,%s" % (x_spacing, y_spacing))
        self.log.debug("Y Max and min:%s,%s" % (self.y_max_scale_value.get(), self.y_min_scale_value.get()))
        start_line_x = START_X        # Set the starting point for the X axis
        start_line_y = END_Y - ((data_to_draw[0] - self.y_min_scale_value.get()) * y_spacing)
        for reading in data_to_draw[1:]:        # Start at the second reading as first one is starting point
            end_line_x = start_line_x + x_spacing
            end_line_y = END_Y - ((reading - self.y_min_scale_value.get()) * y_spacing)
            #print("END_Y:%s, reading:%s, end_line_y:%s" % (END_Y, reading, end_line_y))
            self.graph_line = self.graph_canvas.create_line(start_line_x,start_line_y,end_line_x,end_line_y, fill=colours[line_no], tags=('graphline'))
            start_line_x = end_line_x
            start_line_y = end_line_y
        #print(data_to_draw)
        return

    def draw_graph_no_max(self,data_to_draw, line_no):
        """
        Draw the graph on the graph area
        Graph area is 0 - 20 sections wide, 0 - 13 high
        coord ranges 20 - END_X across, 20 - 280 up.
        """

        colours = ["red", "green", "blue", "cyan", "yellow", "magenta", "black", 'white']

        if line_no == 0:
            # If the line has been drawn before, delete it.
            if len(self.graph_canvas.find_withtag('graphline'))> 0:
                self.graph_canvas.delete('graphline')
        x_spacing = (END_X - START_X) / len(data_to_draw)       # Add 1 as
        
        y_max = max(data_to_draw)
        y_max = y_max + (y_max * 0.1)       # Add 10% margin to the graph boundary
        y_min = min(data_to_draw)
        y_min = y_min - ( y_min * 0.1)      # Take 10% off the minimum for the graph boundary

        y_min = 0       # Test to see if stay s stable

        if (y_max - y_min) > 0:
            y_spacing = (END_Y - START_Y) / (y_max - y_min)
        else:
            y_spacing = (END_Y - START_Y)
        self.log.debug("Spacing (x,y):%s,%s" % (x_spacing, y_spacing))
        self.log.debug("Y Max and min:%s,%s" % (y_max, y_min))
        start_line_x = START_X        # Set the starting point for the X axis
        start_line_y = END_Y - ((data_to_draw[0] - y_min) * y_spacing)
        for reading in data_to_draw[1:]:        # Start at the second reading as first one is starting point
            end_line_x = start_line_x + x_spacing
            end_line_y = END_Y - ((reading - y_min) * y_spacing)
            #print("END_Y:%s, reading:%s, end_line_y:%s" % (END_Y, reading, end_line_y))
            self.graph_line = self.graph_canvas.create_line(start_line_x,start_line_y,end_line_x,end_line_y, fill=colours[line_no], tags=('graphline'))
            start_line_x = end_line_x
            start_line_y = end_line_y
        #print(data_to_draw)
        return
        
    def draw_graph_combined(self,data_to_draw, line_no):
        """
        Draw the graph on the graph area
        Graph area is 0 - 20 sections wide, 0 - 13 high
        coord ranges 20 - END_X across, 20 - 280 up.
        """
        # This has been kept as a copy of the graphing software that includes Y max and Y min values.
        # Removed as scale markers don't make sense with multiple lines
        colours = ["red", "green", "blue", "cyan", "yellow", "magenta", "black", 'white']

        if line_no == 0:
            if len(self.graph_canvas.find_withtag('graphline'))> 0:
                self.graph_canvas.delete('graphline')
        x_spacing = (END_X - START_X) / len(data_to_draw)       # Add 1 as
        if self.y_max_scale_value.get() < max(data_to_draw):
            self.y_max_scale_value.set(max(data_to_draw))
        if self.y_min_scale_value.get() > min(data_to_draw):
            self.y_min_scale_value.set(min(data_to_draw))

        if (self.y_max_scale_value.get() - self.y_min_scale_value.get()) > 0:
            y_spacing = (END_Y - START_Y) / (self.y_max_scale_value.get() - self.y_min_scale_value.get())
        else:
            y_spacing = (END_Y - START_Y)
        #print("y_spacing:%s" % y_spacing)
        start_line_x = START_X        # Set the starting point for the X axis
        start_line_y = END_Y - ((data_to_draw[0] - self.y_min_scale_value.get()) * y_spacing)
        for reading in data_to_draw[1:]:        # Start at the second reading as first one is starting point
            end_line_x = start_line_x + x_spacing
            end_line_y = END_Y - ((reading - self.y_min_scale_value.get()) * y_spacing)
            #print("END_Y:%s, reading:%s, end_line_y:%s" % (END_Y, reading, end_line_y))
            self.graph_line = self.graph_canvas.create_line(start_line_x,start_line_y,end_line_x,end_line_y, fill=colours[line_no], tags=('graphline'))
            start_line_x = end_line_x
            start_line_y = end_line_y

        return

    def exit_program(self):       # Needs to be moved to Data Capture
        # called form the capture button
        logging.debug("Exiting Program")
        self.running = False
        self.exit_command()
        return
   
    def update_data(self):
        """
        Takes the new values in from outside the class in the queue and 
        data is a list of values, the newest reading is last
        """
        new_reading = 0
        previous_reading = 0
        self.log.info("[Disp] Updating incoming data")
        freq = 0
        while self.queue.qsize():
            try:
                data = self.queue.get(0)
                #self.log.debug("[Disp] Incoming data to be added to feed:%s" % data)
                #self.dataset.append(data)
                freq = (1/(data*2))
                if freq > SS.GRAPH_MAX:
                    # The the maximum value is greater than the max allowed, set it to the min allowed as it was a rogue value
                    self.dataset.append(self.y_min_scale_value.get())
                else:
                    self.dataset.append(freq)         # Use frequency instead
            except Queue.Empty:
                # just on general principles, although we don't
                # expect this branch to be taken in this case
                pass
        if len(self.dataset) > MAX_LENGTH:
            self.log.debug("[Disp] Trimming the dataset:%s" % len(self.dataset))
            self.dataset = self.dataset[-MAX_LENGTH:]        # Trim the data to the last 100 readings max
        if len(self.dataset) > (SS.TRIGGER_MEASURE_QTY*2)+1:
            # If we now have enough data to estimate if it is being triggered
            # Compare the last dataset with the trigger level and trigger accordingly
            new_reading = int(max(self.dataset[-SS.TRIGGER_MEASURE_QTY:])) 
            if new_reading > self.trigger_lvl.get():
                self.trigger.set(SS.TRIGGERED + " (" + str(new_reading)+")")
            else:
                self.trigger.set(SS.NOT_TRIGGERED)
            self.log.debug("[Disp] Object trigger level is %s (new reading): %s" % (self.trigger.get(), new_reading))
        self.log.info("[Disp] Dataset after update and trim:%s" % self.dataset)
        return
        
    def main(self):
        """
        Called regularly to update values etc.
        """
        self.log.info("[Disp] Starting the main loop")
        if self.running:
            # Call this when running
            self.update_data()
            if len(self.dataset) > 0:
                self.draw_graph(self.dataset, 0)
        

class DataCapture:
    """
    Launched first to capture the time periods and pass them to the Display class
    in the form of a queue.
    """
    def __init__(self, master):
        """
        Start the GUI and the asynchronous threads. We are in the main
        (original) thread of the application, which will later be used by
        the GUI as well. We spawn a new thread for the worker (I/O).
        """
        self.log = logging.getLogger()
        self.log.info("[DataC] Starting Class DataCapture")
        self.master = master
        self.capturing = True
        self.refresh = SS.DEFAULT_REFRESH_RATE

        # Create the queue for data transfer
        self.queue = queue.Queue()

        # Set up the GUI part
        self.gui = RadarDisplay(master, self.queue, self.exit_command, self.refresh_command)

        # Set up the thread to do asynchronous I/O
        # More threads can also be created and used, if necessary
        self.log.info("[DataC] Starting Thread for Data Capture")

        self.thread1 = threading.Thread(target=self.time_period_read)
        self.thread1.start()

        self.log.debug("[DataC] Threads running")

        # Start the periodic call in the GUI to check if the queue contains
        # anything
        self.gui_update()
        return

    def gui_update(self):
        """
        Check every 200 ms if there is something new in the queue.
        """
        self.log.debug("[DataC] GUI Update cycle starting")

        self.gui.main()     # Jog GUI to update stuff
        self.master.after(self.refresh, self.gui_update)
        return

    def read_gpio(self):
        # Read the current state of the GPIO input
        reading = GPIO.input(SS.FREQ_PIN)
        #print("GPIO Reading = %s" % reading)
        return reading

    def current_time(self):
        # return the current system time
        # value returned is the time in seconds since 1/1/1970 00:00:00 as a floating point number
        return time.time()

    def time_period_read(self):
        """
        This is where we handle the asynchronous I/O. For example, it may be
        a 'select(  )'. One important thing to remember is that the thread has
        to yield control pretty regularly, by select or otherwise.
        """
        self.log.info("[DataC] Starting Data Capturing thread:%s" % self.capturing)
        starttime = 0.00                    # float
        nowtime = 0.00                      # float
        period = 0.0
        current_state = False

        while self.capturing:
            time.sleep(SS.CAPTURE_SPEED)
            starttime = self.current_time()
            while True:
                state = self.read_gpio()
                nowtime = self.current_time()
                if state != current_state:
                    # The state has changed since the last cycle
                    time.sleep(SS.DEBOUNCE_TIME)
                    if state == self.read_gpio():
                        period = (nowtime - starttime)
                        starttime = nowtime
                        current_state = state
                        break
                elif nowtime > (starttime + SS.MAX_WAIT):
                    # Timed out
                    self.log.debug("[DataC] Time has exceeded, default being used")
                    period = SS.MAX_WAIT
                    starttime = nowtime
                    current_state = not(state)
                    break
            self.queue.put(period)
            #self.log.debug("[DataC] Time Period Read:%s" % period)
        return

    def time_period_read_random(self):
        """
        This is where we handle the asynchronous I/O. For example, it may be
        a 'select(  )'. One important thing to remember is that the thread has
        to yield control pretty regularly, by select or otherwise.
        """
        self.log.info("[DataC] Starting Data Capturing thread:%s" % self.capturing)

        while self.capturing:
            time.sleep(SS.CAPTURE_SPEED)        # self.speed is given in uS, but time wants it in S
            msg = random.randint(0, 100)
            self.queue.put(msg)
            #self.log.debug("[DataC] Random data generated:%s" % msg)
        return

    def time_period_read_fixed(self):
        """
        This is where we handle the asynchronous I/O. For example, it may be
        a 'select(  )'. One important thing to remember is that the thread has
        to yield control pretty regularly, by select or otherwise.
        """
        self.log.info("[DataC] Starting Data Capturing thread:%s" % self.capturing)

        while self.capturing:
            time.sleep(SS.CAPTURE_SPEED)        # self.speed is given in uS, but time wants it in S
            msg = 0.00000123
            self.queue.put(msg)
            #self.log.debug("[DataC] Random data generated:%s" % msg)
        return

    def time_period_read_ramped(self):
        """
        This is where we handle the asynchronous I/O. For example, it may be
        a 'select(  )'. One important thing to remember is that the thread has
        to yield control pretty regularly, by select or otherwise.
        """
        self.log.info("[DataC] Starting Data Capturing thread:%s" % self.capturing)
        value = 0
        delta = 1
        while self.capturing:
            time.sleep(SS.CAPTURE_SPEED)        # self.speed is given in uS, but time wants it in S
            value = value + delta
            self.queue.put(value)
            if value > 10000:
                delta = -1
            if value <= 0:
                delta = +1
            #self.log.debug("[DataC] Random data generated:%s" % msg)
        return
        
    def speed_command(self,new_speed):
        """
        Take the data given by the GUI and set the speed for data capture
        The value given is in uS
        """
        self.speed = new_speed
        self.log.debug("[DataC] New Speed value (in uS):%s" % self.speed)
        
        
    def refresh_command(self,new_refresh_speed):
        """
        Take the data given by the GUI and set the speed for data capture
        The value given is in uS
        """
        self.refresh = new_refresh_speed
        self.log.debug("[DataC] New Speed value (in uS):%s" % self.refresh)
        
    def exit_command(self):
        """
        Finish the application
        """
        self.capturing = False
        #self.thread1.join()
        sys.exit()


def gpio_setup():
    # Configure the GPIO for reading the frequency
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(SS.FREQ_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

def SetupLogging():
    """
    Setup the logging defaults
    Using the logger function to span multiple files.
    """
    global gbl_log
    # Create a logger with the name of the function
    logging.config.dictConfig(dict_Logging.log_cfg)
    gbl_log = logging.getLogger()

    gbl_log.info("\n\n")
    gbl_log.info("[CTRL] Logging Started, current level is %s" % gbl_log.getEffectiveLevel())

    return

def main():

    SetupLogging()

    gpio_setup()

    global root
    global app
    root = Tk()
    root.geometry("800x410")
    app = DataCapture(root)
    app.master.title("Radar Display Tool")
    root.mainloop()
    return

if __name__ == '__main__':
	main()
