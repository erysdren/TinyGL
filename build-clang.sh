#!/bin/bash

if ! [ -x "$(command -v clang)" ]
then
	echo "clang not found"
else

	if [ ! -d cmake-build-clang ]
	then
		mkdir cmake-build-clang
	fi

	TEMP=${CC}
	export CC=clang

	cd cmake-build-clang
	cmake .. 
	make
	cd ..

	export CC=${TEMP}

fi
