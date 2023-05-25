#!/bin/bash

if [ ! -d cmake-build-watcom-windows ] 
then
	mkdir cmake-build-watcom-windows
fi

cd cmake-build-watcom-windows
cmake -G "Watcom WMake" -D CMAKE_SYSTEM_NAME=Windows -D WATCOM=TRUE ..
wmake
