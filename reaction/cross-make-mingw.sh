#!/bin/sh

export CC=i386-mingw32-gcc
export WINDRES=i386-mingw32-windres
export PLATFORM=mingw32
exec make $*
