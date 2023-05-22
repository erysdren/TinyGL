#!/bin/bash

if [ ! -d cmake-build-clang ]
then
	mkdir cmake-build-clang
fi

TEMP=${CC}
export CC=clang

cd cmake-build-clang
cmake .. 
make

export CC=${TEMP}
