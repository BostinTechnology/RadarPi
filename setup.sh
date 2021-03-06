#!/bin/bash
# 
# File:   setup.sh
# Author: matthew
#
# Created on 18-Sep-2020, 08:19:56
#


# Colour Scheme
# change echo to echo -e
# Titles: Bold, undelined, white on blue background   \e[1;4;97;44m
# Progress dot: bold, white, green background \e[1;97;42m
# Debug Info: normal, white, magenta background \e[97;105m
# Error Message: bold, white, light red background \e[1;97;101m
#       remainder of errro text \e[39;49m
# reset at end of section \e[0m



# removed -o errexit  so I can trap errors manually.
set -o nounset -o noclobber

# Variable declarations
APPS="gnuplot glade libcairo2-dev"

DEBUG=0

COMMAND_LINE_ARGS=""
RUNNING_FUNCTION=""
CURRENT_USER=""

BASE_DIR=""

# This function requires an additional parameter to be passed that is the task it was performing
# before it failed.
error_encountered(){
    if [ $# -ne 1 ]; then
        RUNNING_FUNCTION=$0
    else
        RUNNING_FUNCTION=$1
    fi
    echo -e "\e[1;97;101mERROR HAS OCCURRED\e[0m"
    echo " "
    echo -e "\e[39;49m An error has occurred whilst running \e[1;97;101m$RUNNING_FUNCTION\e[39;49m routine\e[0m"
    echo -e " "
    read -p "Do you wish to attempt to continue? " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        [[ "$0" = "$BASH_SOURCE" ]] && exit 1 || return 1 # handle exits from shell or function but don't exit interactive shell
    fi

}

system_update()
{
    # Update the installed operating system
    if [ "$DEBUG" == 1 ]; then
        echo -e "\e[97;105mPerforming System Update .....\e[0m"
    fi
    sudo apt-get update      1>&2
    if [ $? != 0 ]; then
        error_encountered "system update"
    fi
    sudo apt-get upgrade -y  1>&2
    if [ $? != 0 ]; then
        error_encountered "system upgrade"
    fi
    echo -e "\e[1;97;42m.\e[0m"
}

comms_setup()
{
    # Configure Serial terminals, I2C and SPI
    if [ "$DEBUG" == 1 ]; then
        echo -e "\e[97;105mDisabling Serial Terminal and enable serial port, I2C and SPI .....\e[0m"
    fi
    sudo raspi-config nonint do_serial 2
    if [ $? != 0 ]; then
        error_encountered "setting serial port"
    fi
    sudo raspi-config nonint do_i2c 0
    if [ $? != 0 ]; then
        error_encountered "setting i2c port"
    fi
    sudo raspi-config nonint do_spi 0
    if [ $? != 0 ]; then
        error_encountered "setting SPi port"
    fi
    echo -e "\e[1;97;42m.\e[0m"
}


install_apps()
{
    if [ "$DEBUG" == 1 ]; then
        echo -e "\e[97;105mInstall Standard Apps .....\e[0m"
    fi
    # Install global and host specific applications
    sudo apt-get install -y $APPS
    if [ $? != 0 ]; then
        error_encountered "installing standard apps"
    fi

    echo -e "\e[1;97;42m.\e[0m"
}

# install the latest GTK libaries
install_gtk()
{
    if [ "$DEBUG" == 1 ]; then
        echo -e "\e[97;105mInstall GTK Libaries .....\e[0m"
    fi
    sudo apt-get install libgtk-3-0
    if [ $? != 0 ]; then
        error_encountered "installing gtk libaries"
    fi

    sudo apt-get install libgtk-3-dev
    if [ $? != 0 ]; then
        error_encountered "installing gtk development libaries"
    fi

}

install_bcm2835()
{
    if [ "$DEBUG" == 1 ]; then
        echo -e "\e[97;105mInstalling bcm2835 libaries .....\e[0m"
    fi
    mkdir -p ~/tmp
    cd ~/tmp
    wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.58.tar.gz
    if [ $? != 0 ]; then
        error_encountered "downloading bcm2835"
    fi
    tar zxvf bcm2835-1.58.tar.gz
    cd bcm2835-1.58
    ./configure
    make
    sudo make check
    sudo make install
    if [ $? != 0 ]; then
        error_encountered "building and installing bcm2835"
    fi
    cd ~
    rm -Rf ~/tmp
    echo -e "\e[1;97;42m.\e[0m"
}

compile_radarpi()
{
    if [ "$DEBUG" == 1 ]; then
        echo -e "\e[97;105mCompiling Radar Pi applications .....\e[0m"
    fi
    cd $BASE_DIR
    if [ $? != 0 ]; then
        error_encountered "switching to the Radar Pi directory"
    fi
    make
    if [ $? != 0 ]; then
        error_encountered "compiling the Radar Pi applications"
    fi

    
}

#Display information about how to use the script
usage()
{
    echo "usage: setup_pi.sh [OPTIONS]..."
    echo "      Install the required software for a Radar Pi on the Raspberry Pi"
    echo ""
    echo "      -d --debug                  Turn on Debug Info"
}

get_command_line_options()
{

#This bit is not working, the comamnd line args in the second bit should
#be a single element, it isn't - its the lot!

    eval set -- "$COMMAND_LINE_ARGS"
    while [ "$1" != "" ]; do
        case $1 in
            -h | --help )           usage
                                    exit 1
                                    ;;
            -d | --debug )          DEBUG=1
                                    ;;
            -- )                    shift
                                    break
                                    ;;
            * )                     usage
                                    exit 1
        esac
        shift
    done

}

debug()
{
    echo -e "\e[1;4;97;44mDebug Information\e[0m"
    echo " "
    echo -e "User                  :: \e[97;105m$CURRENT_USER\e[0m"
    echo -e "Base Directory        :: \e[97;105m$BASE_DIR\e[0m"
    echo -e "Debug Status (1=ON)   :: \e[97;105m$DEBUG\e[0m"
    echo "Command Line Parameters"
    for arg in "$COMMAND_LINE_ARGS"; do
        echo -e "  parameter           :: \e[97;105m$arg\e[0m"
    done
    echo " "

}

set_user()
{
    CURRENT_USER=`whoami`
    if [ "$CURRENT_USER" == "root" ]; then
        # If the user is root, it is being run as sudo, so get the actual user
        CURRENT_USER=$SUDO_USER
        echo -e "\e[1;97;101mERROR: \e[39;49mScript needs to be run as NORMAL user, don't run with sudo .....\e[0m"
        exit 1
    fi

}
#-------------------git add *-----------------------------------------------------------
#
#  MAIN
#
#------------------------------------------------------------------------------
echo -e "\n\e[1;4;97;44mStarting configuration of the Radar Pi on the Raspberry Pi....\e[0m"
echo " "



COMMAND_LINE_ARGS=$(getopt -o hd --long help,debug -- "$@")

get_command_line_options
set_user

BASE_DIR=$(dirname $(readlink -f "$0"))

if [ "$DEBUG" == 1 ]; then
    debug
fi

system_update
comms_setup
install_bcm2835
install_apps
install_gtk

compile_radarpi

echo -e "\e[1;97;42m*************************************************************************\e[0m"
echo -e "                       \e[1;97;42mALL DONE - REBOOTING\e[0m"
echo -e "\e[1;97;42m*************************************************************************\e[0m"
sleep 2
sudo reboot -f
