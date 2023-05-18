#!/bin/bash

if [ ! -d cmake-build-mingw-i686 ]
then
	mkdir cmake-build-mingw-i686
fi

cd cmake-build-mingw-i686
cmake -D CMAKE_TOOLCHAIN_FILE=cmake/mingw-i686.cmake ..
make
