#!/bin/bash

if [ ! -d cmake-build-haiku-x86_64 ]
then
	mkdir cmake-build-haiku-x86_64
fi

cd cmake-build-haiku-x86_64
cmake -D CMAKE_TOOLCHAIN_FILE=cmake/haiku-x86_64.cmake ..
make
