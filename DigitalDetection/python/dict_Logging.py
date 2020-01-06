""" 
 * File:   dict_logging.py
 * Author: Matthew Bennett <matthew.bennett@bostintechnology.com>
 *
 * Created on 21 September 2019, 10:19
 * 
 * Example code to provide all the various settings associated with the 
 * Display Demo running in python
 *
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation as version 2 of the License.
 *
 * For more information refer to www.BostinTechnology.com
 *
"""

"""
Logging Configuration File
Levels
- CRITICAL
- ERROR
- WARNING
- INFO
- DEBUG
"""

import logging


log_cfg = dict(
    version = 1,
    formatters = {
        'full': {'format':
              '%(asctime)s - %(levelname)-8s - %(message)s',
              },
        'brief': {'format':
              '%(asctime)s - %(message)s',
              'datefmt': '%d-%m-%Y %H:%M:%S'}
        },
    handlers = {
        'screen': {'class': 'logging.StreamHandler',
              'formatter': 'brief',
              'level': logging.ERROR,
              'stream': 'ext://sys.stdout'},
              
        'file': {'class': 'logging.handlers.RotatingFileHandler',
                'formatter': 'full',
                'level': logging.DEBUG,
                'filename': 'CognIot.log',
                'maxBytes':  1638400,
                'backupCount' : 5,
                'mode': 'w'},
                  
        },
    root = {
        'handlers': ['screen', 'file'],
        'level': logging.DEBUG,
        },
        )
