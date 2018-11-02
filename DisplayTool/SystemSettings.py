
"""
Contains all the system settings required to be used

"""

# Refresh Rate settings for the data capture, NOT graph
DEFAULT_REFRESH_RATE = 100
REFRESH_INCREMENT = 25
MAX_REFRESH_RATE = 100000
MIN_REFRESH_RATE = 5

GRAPH_REFRESH = 250             # time in mS between screen refreshes
CAPTURE_SPEED = 0.0005#0.000005        # The time between GPIO readings, 5uS
DEBOUNCE_TIME = 0.000001

GRAPH_MAX = 2000              # The default maximum value for the graph
GRAPH_MIN = 10              # The lowest maximum value allowed
GRAPH_DEFAULT = 500           # The default graph y max value
GRAPH_INC = 10             # the increment / decrement value for the y max

TRIGGERED = "Triggered"
NOT_TRIGGERED = "Monitoring"
READY = "Ready"
TRIGGER_LVL = 50
MAX_TRIGGER_LVL = 1000
MIN_TRIGGER_LVL = 5
TRIGGER_INCREMENT = 25
TRIGGER_MEASURE_QTY = 20

MAX_WAIT = 1        # Time in S, to wait for a trigger

FREQ_PIN = 4       # The GPIO pin used for the frequency input
SAMPLE_HOLD = 17

# LEDs
LED_RUNNING = 14
LED_MONITORING = 15
LED_TRIGGERED = 18
