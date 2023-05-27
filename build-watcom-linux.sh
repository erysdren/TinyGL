#!/bin/bash

if ! [ -x "$(command -v wcl386)" ]
then
	echo "open watcom cross-compiler not found"
else

	if [ ! -d cmake-build-watcom-linux ] 
	then
		mkdir cmake-build-watcom-linux
	fi

	cd cmake-build-watcom-linux
	cmake -G "Watcom WMake" -D CMAKE_SYSTEM_NAME=Linux -D WATCOM=TRUE ..
	wmake
	cd ..

fi
