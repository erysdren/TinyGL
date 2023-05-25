#!/bin/bash

if [ ! -d cmake-build-watcom-dos ] 
then
	mkdir cmake-build-watcom-dos
fi

cd cmake-build-watcom-dos
cmake -G "Watcom WMake" -D CMAKE_SYSTEM_NAME=DOS -D WATCOM=TRUE ..
wmake
