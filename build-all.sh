#!/bin/bash

# generic
source ./build.sh
cd ..

# djgpp
source ./build-djgpp-i586.sh
cd ..

# mingw x86_64
source ./build-mingw-x86_64.sh
cd ..

# mingw i686
source ./build-mingw-i686.sh
cd ..
