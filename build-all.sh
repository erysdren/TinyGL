#!/bin/bash

# clean slate
source ./clean.sh

# generic
source ./build-generic.sh
cd ..

# gcc
source ./build-gcc.sh
cd ..

# clang
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

# watcom dos
source ./build-watcom-dos.sh
cd ..

# watcom linux
source ./build-watcom-linux.sh
cd ..

# watcom os/2
source ./build-watcom-os2.sh
cd ..

# watcom windows
source ./build-watcom-windows.sh
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
