goto %1
:cgame
cd cgame
call cgame
cd..
goto done
:game
cd game
call game
cd..
goto done
:ui
cd ui
call ui
:done
cd\
cd quake3
cd baseq3
cd vm
copy /Y *.qvm "c:\program files\quake iii arena\reaction\vm"
del *.qvm
cd \
cd reaction


