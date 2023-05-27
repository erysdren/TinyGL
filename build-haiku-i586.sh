#!/bin/bash

if ! [ -x "$(command -v i586-pc-haiku-gcc)" ]
then
	echo "haiku x86 cross-compiler not found"
else

	if [ ! -d cmake-build-haiku-i586 ]
	then
		mkdir cmake-build-haiku-i586
	fi

	# oh, a hack!
	TEMP=${SDL2_DIR}
	export SDL2_DIR=/usr/lib32/cmake/SDL2/

	cd cmake-build-haiku-i586
	cmake -D CMAKE_TOOLCHAIN_FILE=cmake/haiku-i586.cmake ..
	make
	cd ..

	export SDL2_DIR=${TEMP}

fi
