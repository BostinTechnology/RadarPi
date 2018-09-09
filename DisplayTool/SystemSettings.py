
"""
Contains all the system settings required to be used

"""

# Refresh Rate settings for the data capture, NOT graph
DEFAULT_REFRESH_RATE = 100
REFRESH_INCREMENT = 5
MAX_REFRESH_RATE = 100000
MIN_REFRESH_RATE = 5

GRAPH_REFRESH = 250             # time in mS between screen refreshes

APP_DEP_MEASURE_QTY = 20            # The number of readings to be used for determinging the
                                    # the quantitiy of readings to use to determine approaching or departing

DEPARTING = "Departing"
APPROACHING = "Approaching"
STABLE = "Stable"
NO_DATA = "Awaiting Readings"


FREQ_PIN = 17       # The GPIO pin used for the frequency input
