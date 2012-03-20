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

