#!/bin/bash

if [ ! -d cmake-build-haiku-i586 ]
then
	mkdir cmake-build-haiku-i586
fi

cd cmake-build-haiku-i586
cmake -D CMAKE_TOOLCHAIN_FILE=cmake/haiku-i586.cmake ..
make
