#!/bin/bash

if ! [ -x "$(command -v i586-pc-msdosdjgpp-gcc)" ]
then
	echo "djgpp not found"
else

	if [ ! -d cmake-build-djgpp-i586 ]
	then
		mkdir cmake-build-djgpp-i586
	fi

	cd cmake-build-djgpp-i586
	cmake -D CMAKE_TOOLCHAIN_FILE=cmake/djgpp-i586.cmake ..
	make
	cd ..

fi
