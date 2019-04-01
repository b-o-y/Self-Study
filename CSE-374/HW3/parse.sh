#!/bin/bash
#
# Created by: Travis Henderson
# Date Last Modified: 18/07/24
# 
# Notes:
# - Instructions say to print an error for fewer than 2 arguments, although
# I don't know what the program would do with greater than 2 arguments,
# hence why it checks ONLY for 2 arguments.
# 
# - The assignment asks the question what to do with the links that aren't
# a part of the top 100; I didn't do anything clever I just hardwired it.

if [ "$#" -ne 2 ]
then
	echo "ERROR: parse.sh only accepts 2 arguments."
	exit 1
elif [[ "${2: -5}" != ".html" ]] || [[ "${1: -4}" != ".txt" ]]
then
	echo "ERROR: First argument must be a .txt file, and second argument must be a .html file."
	exit 1 
else
	cat "$2" | grep "http://" | sed -e 's/^.*http/http/' -e 's/".*//g' > "#1" > "$1" # Give me lines that start with http, and delete everything after ".
	sed -i -e '/100bestwebsites/d' -e '/babelfish/d' -e '/List_of/d' ./"$1"          # Getting rid of site names NOT in the top 100.
	exit 0
fi	
