#!/bin/bash
#
# Created by: Travis Henderson
# Date Last Modified: 18/07/23
# Thanks to /fglt/ for helping me with wget.
# 
# Notes:
# - Sometimes wget --spider returns the content-length more than once, I'm not really sure if there
# is a difference between the instances and just arbitarily chose to use the first instance. 

if [ "$#" -eq 1 ]
then
	wget --spider -S "$1" 2>&1 | grep Content-Length > /dev/null # Check if a valid argument for wget,
	if [ $? -ne 0 ]                                              # if not then exit.
	then
		echo "0"
		exit 1
	fi
	wget --spider -S "$1" 2>&1 | grep Content-Length | head -1 | sed 's/\s\sContent-Length:\s//g' # Otherwise print the size.
	exit 0
else
	echo "ERROR: perform-measurement only accepts one argument."
	exit 1
fi
exit 0

