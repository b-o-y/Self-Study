#!/bin/bash
#
# Created by: Travis Henderson
# Date Last Modified: 18/07/24
#
# Notes:
# - First argument is where the results will go, second argument is where
# the list of websites are.
# - Some websites don't have a Content-Length when ran with wget --spider,
# I have no idea what that's about, and just chalk it up as a failure.

if [ "$#" -eq 2 ]
then
	num=0
	size=0
	echo -n > "$1"

	while read -r line
	do
		echo "Performing byte-size measurement on" $line
		size=$(sh ./perform-measurement.sh "$line")
		echo "size is" $size
		num=$(( $num + 1))
		if [[ "$size" -gt 0 ]] || [[ "$size" -ne "" ]]
		then
			echo "...succesful."
			echo $num $line $size >> "$1"
		else
			echo "...failure"
		fi
	done <"$2"	
	exit 0
else
	echo "ERROR: run-experiment requires 2 arguments."
	exit 1
fi
