#!/bin/bash

if [ ! -d cmake-build-mingw-x86_64 ]
then
	mkdir cmake-build-mingw-x86_64
fi

cd cmake-build-mingw-x86_64
cmake -D CMAKE_TOOLCHAIN_FILE=cmake/mingw-x86_64.cmake ..
make
