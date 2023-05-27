#!/bin/bash

if ! [ -x "$(command -v riscv64-linux-gnu-gcc)" ]
then
	echo "risc-v linux cross-compiler not found"
else

	if [ ! -d cmake-build-riscv64-linux-gnu ]
	then
		mkdir cmake-build-riscv64-linux-gnu
	fi

	cd cmake-build-riscv64-linux-gnu
	cmake -D CMAKE_TOOLCHAIN_FILE=cmake/riscv64-linux-gnu.cmake ..
	make
	cd ..

fi
