#!/bin/bash

if [ ! -d cmake-build-watcom-os2 ] 
then
	mkdir cmake-build-watcom-os2
fi

cd cmake-build-watcom-os2
cmake -G "Watcom WMake" -D CMAKE_SYSTEM_NAME=OS2 -D WATCOM=TRUE ..
wmake
