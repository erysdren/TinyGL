#!/bin/bash

if [ ! -d cmake-build-watcom-linux ] 
then
	mkdir cmake-build-watcom-linux
fi

cd cmake-build-watcom-linux
cmake -G "Watcom WMake" -D CMAKE_SYSTEM_NAME=Linux -D WATCOM=TRUE ..
wmake
