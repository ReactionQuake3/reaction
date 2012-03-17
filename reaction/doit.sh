#!/bin/bash
#
# Script to set up after build on JB's system
#
cd build/release-linux-x86_64/
cp Reaction* /usr/local/games/Reaction/
cd Boomstick
rm -f /usr/local/games/Reaction/Boomstick/zzzzzzzzzzzzzzzzzzzz-code.pk3
zip -r /usr/local/games/Reaction/Boomstick/zzzzzzzzzzzzzzzzzzzz-code.pk3 vm/

