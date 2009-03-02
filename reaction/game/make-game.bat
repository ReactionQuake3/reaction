@echo off

REM *** TEMPORARY BATCH FILE FOR OLD SVN PATHS!

REM *** NOTE: THIS BATCH FILE IS MEANT TO BE CALLED BY make-qvm.bat!
REM *** NOTE: THIS CANNOT BE RUN BY ITSELF WITHOUT %make-qvm-location% BEING DEFINED!

cd vm
set cc=q3lcc.exe -DQ3_VM -S -Wf-target=bytecode -Wf-g -I..\..\cgame -I..\..\game -I..\..\ui


echo.
echo *** Running Q3LCC for GAME/QAGAME...

%cc%  ../g_main.c
@if errorlevel 1 goto quit
REM ***%cc%  ../g_syscalls.c
REM *** cpp: ../g_syscalls.c:29 #error directive: "Do not use in VM build"
@if errorlevel 1 goto quit

REM *** Makro - bg_materials.c needed for the new surfaceparm system
%cc%  ../bg_materials.c
@if errorlevel 1 goto quit
%cc%  ../bg_misc.c
@if errorlevel 1 goto quit
%cc%  ../bg_lib.c
@if errorlevel 1 goto quit
%cc%  ../bg_pmove.c
@if errorlevel 1 goto quit
%cc%  ../bg_slidemove.c
@if errorlevel 1 goto quit

%cc%  ../q_math.c
@if errorlevel 1 goto quit
%cc%  ../q_shared.c
@if errorlevel 1 goto quit

%cc%  ../ai_dmnet.c
@if errorlevel 1 goto quit
%cc%  ../ai_dmq3.c
@if errorlevel 1 goto quit
%cc%  ../ai_main.c
@if errorlevel 1 goto quit
%cc%  ../ai_chat.c
@if errorlevel 1 goto quit
%cc%  ../ai_cmd.c
@if errorlevel 1 goto quit
%cc%  ../ai_team.c
@if errorlevel 1 goto quit
%cc%  ../ai_vcmd.c
@if errorlevel 1 goto quit

%cc%  ../g_active.c
@if errorlevel 1 goto quit
%cc%  ../g_arenas.c
@if errorlevel 1 goto quit
%cc%  ../g_bot.c
@if errorlevel 1 goto quit
%cc%  ../g_client.c
@if errorlevel 1 goto quit
%cc%  ../g_cmds.c
@if errorlevel 1 goto quit
%cc%  ../g_combat.c
@if errorlevel 1 goto quit
%cc%  ../g_items.c
@if errorlevel 1 goto quit
%cc%  ../g_matchmode.c
@if errorlevel 1 goto quit
%cc%  ../g_mem.c
@if errorlevel 1 goto quit
%cc%  ../g_misc.c
@if errorlevel 1 goto quit
%cc%  ../g_missile.c
@if errorlevel 1 goto quit
%cc%  ../g_mover.c
@if errorlevel 1 goto quit
%cc%  ../g_parser.c
@if errorlevel 1 goto quit
%cc%  ../g_scripts.c
@if errorlevel 1 goto quit
%cc%  ../g_session.c
@if errorlevel 1 goto quit
%cc%  ../g_spawn.c
@if errorlevel 1 goto quit
%cc%  ../g_svcmds.c
@if errorlevel 1 goto quit
%cc%  ../g_target.c
@if errorlevel 1 goto quit
%cc%  ../g_team.c
@if errorlevel 1 goto quit
%cc%  ../g_teamplay.c
@if errorlevel 1 goto quit
%cc%  ../g_trigger.c
@if errorlevel 1 goto quit
%cc%  ../g_utils.c
@if errorlevel 1 goto quit
%cc%  ../g_unlagged.c
@if errorlevel 1 goto quit
%cc%  ../g_weapon.c
@if errorlevel 1 goto quit
%cc%  ../g_fileio.c
@if errorlevel 1 goto quit

%cc%  ../rxn_game.c
@if errorlevel 1 goto quit

%cc%  ../zcam.c
@if errorlevel 1 goto quit
%cc%  ../zcam_target.c
@if errorlevel 1 goto quit

echo.
echo *** Running Q3ASM for GAME/QAGAME...

REM *** This tells q3asm to generate a vanilla q3-compatible qvm, generate a .map file, output 
REM *** the resulting .qvm into "%make-qvm-location%bin\qvm\vm\qagame" (it will be called qagame.qvm), 
REM *** and to compile the files listed in the game.q3asm script located in "%make-qvm-location%game/game".

REM *** TEMPORARY BATCH FILE FOR OLD SVN PATHS!

q3asm -vq3 -m -o "%make-qvm-location%bin\qvm\vm\qagame" -f "%make-qvm-location%game/game"

:quit
if errorlevel 1 (
echo.
echo ERROR IN Q3LCC PARSING! GAME/QAGAME COMPILATION HALTED!
echo.
)
echo.
cd ..
