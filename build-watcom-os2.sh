#!/bin/bash

if ! [ -x "$(command -v wcl386)" ]
then
	echo "open watcom cross-compiler not found"
else

	if [ ! -d cmake-build-watcom-os2 ] 
	then
		mkdir cmake-build-watcom-os2
	fi

	cd cmake-build-watcom-os2
	cmake -G "Watcom WMake" -D CMAKE_SYSTEM_NAME=OS2 -D WATCOM=TRUE ..
	wmake
	cd ..

fi
