@echo off

REM *** NOTE: THIS BATCH FILE IS MEANT TO BE CALLED BY make-qvm.bat!
REM *** NOTE: THIS CANNOT BE RUN BY ITSELF WITHOUT %make-qvm-location% BEING DEFINED!

cd vm
set cc=q3lcc.exe -DQ3_VM -S -Wf-target=bytecode -Wf-g -I..\..\cgame -I..\..\game -I..\..\ui


echo.
echo *** Running Q3LCC for CGAME...

REM ***Makro - bg_materials.c needed for the new surfaceparm system
%cc% ../../game/bg_materials.c
@if errorlevel 1 goto quit
%cc% ../../game/bg_misc.c
@if errorlevel 1 goto quit
%cc% ../../game/bg_pmove.c
@if errorlevel 1 goto quit
%cc% ../../game/bg_slidemove.c
@if errorlevel 1 goto quit
%cc% ../../game/bg_lib.c
@if errorlevel 1 goto quit

%cc% ../../game/q_math.c
@if errorlevel 1 goto quit
%cc% ../../game/q_shared.c
@if errorlevel 1 goto quit

%cc% ../cg_atmospheric.c
@if errorlevel 1 goto quit
%cc% ../cg_consolecmds.c
@if errorlevel 1 goto quit
%cc% ../cg_draw.c
@if errorlevel 1 goto quit
%cc% ../cg_drawtools.c
@if errorlevel 1 goto quit
%cc% ../cg_effects.c
@if errorlevel 1 goto quit
%cc% ../cg_ents.c
@if errorlevel 1 goto quit
%cc% ../cg_event.c
@if errorlevel 1 goto quit
%cc% ../cg_info.c
@if errorlevel 1 goto quit
%cc% ../cg_localents.c
@if errorlevel 1 goto quit
%cc% ../cg_main.c
@if errorlevel 1 goto quit
%cc% ../cg_marks.c
@if errorlevel 1 goto quit
%cc% ../cg_players.c
@if errorlevel 1 goto quit
%cc% ../cg_playerstate.c
@if errorlevel 1 goto quit
%cc% ../cg_predict.c
@if errorlevel 1 goto quit
%cc% ../cg_scoreboard.c
@if errorlevel 1 goto quit
%cc% ../cg_servercmds.c
@if errorlevel 1 goto quit
%cc% ../cg_snapshot.c
@if errorlevel 1 goto quit
%cc% ../cg_unlagged.c
@if errorlevel 1 goto quit
%cc% ../cg_view.c
@if errorlevel 1 goto quit
%cc% ../cg_weapons.c
@if errorlevel 1 goto quit

echo.
echo *** Running Q3ASM for CGAME...

REM *** This tells q3asm to generate a vanilla q3-compatible qvm, generate a .map file, output 
REM *** the resulting .qvm into "%make-qvm-location%bin\qvm\vm\cgame" (it will be called cgame.qvm), 
REM *** and to compile the files listed in the cgame.q3asm script located in "%make-qvm-location%code/cgame/cgame".

q3asm -vq3 -m -o "%make-qvm-location%bin\qvm\vm\cgame" -f "%make-qvm-location%code/cgame/cgame"

:quit
if errorlevel 1 (
echo.
echo ERROR IN Q3LCC PARSING! CGAME COMPILATION HALTED!
echo.
)
echo.
cd ..
