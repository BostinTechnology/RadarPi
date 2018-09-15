
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

APP_DEP_MEASURE_QTY = 20            # The number of readings to be used for determinging the
                                    # the quantitiy of readings to use to determine approaching or departing

GRAPH_MAX = 2000              # The default maximum value for the graph
GRAPH_MIN = 10              # The lowest maximum value allowed
GRAPH_DEFAULT = 500           # The default graph y max value
GRAPH_INC = 10             # the increment / decrement value for the y max

DEPARTING = "Departing"
APPROACHING = "Approaching"
STABLE = "Stable"
NO_DATA = "Awaiting Readings"


FREQ_PIN = 17       # The GPIO pin used for the frequency input
