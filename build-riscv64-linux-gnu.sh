#!/bin/bash

if [ ! -d cmake-build-riscv64-linux-gnu ]
then
	mkdir cmake-build-riscv64-linux-gnu
fi

cd cmake-build-riscv64-linux-gnu
cmake -D CMAKE_TOOLCHAIN_FILE=cmake/riscv64-linux-gnu.cmake ..
make
