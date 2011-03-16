#!/bin/bash
#Reaction make script by Gimp

#Change to where this file is located
PATH_SRC=~/reaction-dev
#Change to your Reaction install directory
PATH_GAME=~/reaction

if [ -d "$PATH_SRC" ] && [ -d "$PATH_GAME" ]; then
	#remove old QVMs
	echo "Deleting old QVMs..."
	rm $PATH_SRC/bin/qvm/vm/*.map
	rm $PATH_SRC/bin/qvm/vm/*.qvm
	rm $PATH_SRC/code/cgame/vm/*.asm
	rm $PATH_SRC/code/game/vm/*.asm
	rm $PATH_SRC/ui/vm/*.asm
	#remove old builds
	echo "Deleting old builds..."
	rm -Rf $PATH_SRC/build/release-*
	rm $PATH_GAME/Reaction.*
	rm $PATH_GAME/Boomstick/zzzz-code*.pk3
else
	echo "Source and Game paths do not exist."
	exit
fi

cd $PATH_SRC

make

echo "Make completed."

#create temp qvm dir
cd $PATH_GAME
mkdir zzzz-code
cd zzzz-code
mkdir vm
mkdir ui

#move QVM ui files
cp $PATH_SRC/uifiles/*.menu $PATH_GAME/zzzz-code/ui
cp $PATH_SRC/uifiles/*.h $PATH_GAME/zzzz-code/ui
cp $PATH_SRC/uifiles/menus.txt $PATH_GAME/zzzz-code/ui
cp $PATH_SRC/uifiles/ingame.txt $PATH_GAME/zzzz-code/ui

#move QVM vm files
mv $PATH_SRC/build/release-*/Boomstick/vm/*.qvm $PATH_GAME/zzzz-code/vm

cd $PATH_GAME/zzzz-code

zip -r $PATH_GAME/Boomstick/zzzz-code.pk3 vm
zip -r $PATH_GAME/Boomstick/zzzz-code.pk3 ui

rm -Rf $PATH_GAME/zzzz-code

mv $PATH_SRC/build/release-*/Reaction.* $PATH_GAME/
mv $PATH_SRC/build/release-*/Reactionded.* $PATH_GAME/

echo "Done."
