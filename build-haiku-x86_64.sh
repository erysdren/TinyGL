#!/bin/bash

if ! [ -x "$(command -v x86_64-unknown-haiku-gcc)" ]
then
	echo "haiku x86_64 cross-compiler not found"
else

	if [ ! -d cmake-build-haiku-x86_64 ]
	then
		mkdir cmake-build-haiku-x86_64
	fi

	cd cmake-build-haiku-x86_64
	cmake -D CMAKE_TOOLCHAIN_FILE=cmake/haiku-x86_64.cmake ..
	make
	cd ..

fi
