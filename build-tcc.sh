#!/bin/bash

if ! [ -x "$(command -v tcc)" ]
then
	echo "tcc not found"
else

	if [ ! -d cmake-build-tcc ]
	then
		mkdir cmake-build-tcc
	fi

	TEMP=${CC}
	export CC=tcc

	cd cmake-build-tcc
	cmake .. 
	make
	cd ..

	export CC=${TEMP}

fi
