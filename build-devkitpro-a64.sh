#!/bin/bash

if ! [ -x "$(command -v aarch64-none-elf-gcc)" ]
then
	echo "devkitpro-a64 not found"
else

	if [ ! -d cmake-build-devkitpro-a64 ]
	then
		mkdir cmake-build-devkitpro-a64
	fi

	cd cmake-build-devkitpro-a64
	cmake -D CMAKE_TOOLCHAIN_FILE=cmake/devkitpro-a64.cmake ..
	make
	cd ..

fi
