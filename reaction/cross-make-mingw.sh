#!/bin/sh

export ARCH=x86
export CC=i686-pc-mingw32-gcc
export WINDRES=i686-pc-mingw32-windres
export PLATFORM=mingw32
exec make $*
