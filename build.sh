#!/bin/bash

if [ ! -d cmake-build ] 
then
	mkdir cmake-build
fi

cd cmake-build
cmake ..
make
