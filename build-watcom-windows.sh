#!/bin/bash

if ! [ -x "$(command -v wcl386)" ]
then
	echo "open watcom cross-compiler not found"
else

	if [ ! -d cmake-build-watcom-windows ] 
	then
		mkdir cmake-build-watcom-windows
	fi

	cd cmake-build-watcom-windows
	cmake -G "Watcom WMake" -D CMAKE_SYSTEM_NAME=Windows -D WATCOM=TRUE ..
	wmake
	cd ..

fi
