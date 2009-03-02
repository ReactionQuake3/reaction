@echo off

REM *** TEMPORARY BATCH FILE FOR OLD SVN PATHS!

REM *** NOTE: THIS BATCH FILE IS MEANT TO BE CALLED BY make-qvm.bat!
REM *** NOTE: THIS CANNOT BE RUN BY ITSELF WITHOUT %make-qvm-location% BEING DEFINED!

cd vm
set cc=q3lcc.exe -DQ3_VM -S -Wf-target=bytecode -Wf-g -I..\..\cgame -I..\..\game -I..\..\ui


echo.
echo *** Running Q3LCC for UI...

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

echo.
echo *** Running Q3ASM for UI...

REM *** This tells q3asm to generate a vanilla q3-compatible qvm, generate a .map file, output 
REM *** the resulting .qvm into "%make-qvm-location%bin\qvm\vm\ui" (it will be called ui.qvm), 
REM *** and to compile the files listed in the ui.q3asm script located in "%make-qvm-location%ui/ui".

REM *** TEMPORARY BATCH FILE FOR OLD SVN PATHS!

q3asm -vq3 -m -o "%make-qvm-location%bin\qvm\vm\ui" -f "%make-qvm-location%ui/ui"

:quit
if errorlevel 1 (
echo.
echo ERROR IN Q3LCC PARSING! UI COMPILATION HALTED!
echo.
)
echo.
cd ..
