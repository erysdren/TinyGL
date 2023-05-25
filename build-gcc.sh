#!/bin/bash

if [ ! -d cmake-build-gcc ]
then
	mkdir cmake-build-gcc
fi

TEMP=${CC}
export CC=gcc

cd cmake-build-gcc
cmake .. 
make

export CC=${TEMP}
