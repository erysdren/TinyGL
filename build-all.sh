#!/bin/bash

# clean slate
source ./clean.sh

# generic
source ./build.sh
cd ..

# generic (clang)
source ./build-clang.sh
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

# watcom
source ./build-watcom.sh
cd ..

# haiku i586
source ./build-haiku-i586.sh
cd ..

# haiku x86_64
source ./build-haiku-x86_64.sh
cd ..

# risv linux 64-bit
source ./build-riscv64-linux-gnu.sh
cd ..
