#!/bin/bash

if ! [ -x "$(command -v x86_64-w64-mingw32-gcc)" ]
then
	echo "mingw x86_64 cross-compiler not found"
else

	if [ ! -d cmake-build-mingw-x86_64 ]
	then
		mkdir cmake-build-mingw-x86_64
	fi

	cd cmake-build-mingw-x86_64
	cmake -D CMAKE_TOOLCHAIN_FILE=cmake/mingw-x86_64.cmake ..
	make
	cd ..

fi
