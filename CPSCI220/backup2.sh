#!/bin/bash 
# Take a backup of a specific directory 

if [ -d $1 ]; then
	cp -r $1 ~kxiao/CPSCI220/OFFLOAD
	echo "Directory copy completed: " $1
	chmod a+x ~kxiao/CPSCI220/OFFLOAD
else
	echo "Could not locate: " $1
fi
