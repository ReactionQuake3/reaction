#!/bin/bash
#
# Script to set up after build on JB's system
#
cd build/release-linux-x86_64/
cp Reaction* *.so /usr/local/games/Reaction/
cd Boomstick
cp *.so /usr/local/games/Reaction/Boomstick/
rm -f /usr/local/games/Reaction/Boomstick/zzzzzzzzzzzzzzzzzzzz-code.pk3
zip -r /usr/local/games/Reaction/Boomstick/zzzzzzzzzzzzzzzzzzzz-code.pk3 vm/

# Check for the Windows bins
cd ../..
if [ -d release-mingw32-x86 ]; then
	cd release-mingw32-x86
	cp *.exe *.dll /usr/local/games/Reaction/
	cd Boomstick
	cp *.dll /usr/local/games/Reaction/Boomstick/
fi
