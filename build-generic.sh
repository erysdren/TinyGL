#!/bin/bash

if [ ! -d cmake-build-generic ]
then
	mkdir cmake-build-generic
fi

cd cmake-build-generic
cmake ..
make
cd ..
