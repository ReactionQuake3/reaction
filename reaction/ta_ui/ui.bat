@echo off
mkdir vm
cd vm

set cc=call ..\..\compile.bat

%cc% ../ui_main.c
@if errorlevel 1 goto quit
%cc% ../../game/bg_misc.c
@if errorlevel 1 goto quit
%cc% ../../game/bg_lib.c
@if errorlevel 1 goto quit
%cc% ../../game/q_math.c
@if errorlevel 1 goto quit
%cc% ../../game/q_shared.c
@if errorlevel 1 goto quit
%cc% ../ui_atoms.c
@if errorlevel 1 goto quit
%cc% ../ui_players.c
@if errorlevel 1 goto quit
%cc% ../ui_util.c
@if errorlevel 1 goto quit
%cc% ../ui_shared.c
@if errorlevel 1 goto quit
%cc% ../ui_gameinfo.c
@if errorlevel 1 goto quit

q3asm -f ../ui
:quit
cd ..
