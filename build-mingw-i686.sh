#!/bin/bash

if ! [ -x "$(command -v i686-w64-mingw32-gcc)" ]
then
	echo "mingw x86 cross-compiler not found"
else

	if [ ! -d cmake-build-mingw-i686 ]
	then
		mkdir cmake-build-mingw-i686
	fi

	cd cmake-build-mingw-i686
	cmake -D CMAKE_TOOLCHAIN_FILE=cmake/mingw-i686.cmake ..
	make
	cd ..

fi
