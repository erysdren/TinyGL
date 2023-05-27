#!/bin/bash

if ! [ -x "$(command -v arm-none-eabi-gcc)" ]
then
	echo "devkitpro-arm not found"
else

	if [ ! -d cmake-build-devkitpro-arm ]
	then
		mkdir cmake-build-devkitpro-arm
	fi

	cd cmake-build-devkitpro-arm
	cmake -D CMAKE_TOOLCHAIN_FILE=cmake/devkitpro-arm.cmake ..
	make
	cd ..

fi
