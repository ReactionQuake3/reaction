@echo off
cls

REM *** Last updated: Jun 27 2009

REM *** The first part of this batch file is dedicated to checking that your QVM compiling
REM *** environment is set up properly and double-checking that it is because you are an
REM *** end-user and not to be trusted!


REM *** Tell the batch file where it is located.
REM *** Typically this will be something like c:\code\reaction\
REM *** but you can put in whatever you want, like make-qvm-location="c:\reaction code\"
REM *** Remember to add in a trailing backslash \ at the end of the path!

set make-qvm-location=%~dp0


REM *** Check to see if the location of make-qvm.bat is valid.  It is required for this batch file.

IF NOT EXIST "%make-qvm-location%"make-qvm.bat (
echo.
echo make-qvm.bat not found where it was expected!  
echo Edit this batch file and/or rename your folder!
echo Expected to find make-qvm.bat at: 
echo %make-qvm-location%make-qvm.bat
echo.
GOTO END
)


REM *** Tell the batch files where you have installed 7-zip.  
REM *** %PROGRAMFILES% is typically something like "C:\Program Files\"
REM *** but you can put in whatever you want, like zipper="f:\download files\7zip\7z.exe"

set zipper=%PROGRAMFILES%\7-Zip\7z.exe


REM *** Check to see if 7-zip is installed.  It is required for this batch file.

IF NOT EXIST "%zipper%" (
echo.
echo 7-Zip not found where it was expected!  
echo Edit this batch file and/or install 7-zip!
echo Expected to find 7z.exe at: 
echo %PROGRAMFILES%\7-Zip\7z.exe
echo.
GOTO END
)


REM *** Check to see if the location of lcc.exe is valid.  It is required for this batch file.

IF NOT EXIST "%make-qvm-location%"bin\tools\q3lcc.exe (
echo.
echo lcc.exe not found where it was expected!  
echo Edit this batch file and/or rename your folder!
echo Expected to find make-qvm.bat at: 
echo %make-qvm-location%bin\tools\q3lcc.exe
echo.
GOTO END
)

REM *** Check to see if the location of q3asm.exe is valid.  It is required for this batch file.

IF NOT EXIST "%make-qvm-location%"bin\tools\q3asm.exe (
echo.
echo q3asm.exe not found where it was expected!  
echo Edit this batch file and/or rename your folder!
echo Expected to find make-qvm.bat at: 
echo %make-qvm-location%bin\tools\q3asm.exe
echo.
GOTO END
)


REM *** Put the tools folder in the path; used in the separate batch files called below.
set PATH=%PATH%;%make-qvm-location%bin\tools\


REM *** Feedback for what this batch file is using/expecting.
echo.
echo This batch file's defined location: 
echo %make-qvm-location%
echo.
echo 7-zip's defined location: 
echo %zipper%
echo.


REM *** Removing any previous QVM files.
echo.
echo *** Removing any previous QVM files.
del "%make-qvm-location%bin\qvm\vm\*.map"
del "%make-qvm-location%bin\qvm\vm\*.qvm"
del "%make-qvm-location%code\cgame\vm\*.asm"
del "%make-qvm-location%code\game\vm\*.asm"
del "%make-qvm-location%code\ui\vm\*.asm"


REM *** Generating the QVMs
REM *** Note: Q3_UI is not used by Reaction so is not compiled or included in the source.
echo.
echo *** Generating the QVMs
echo.
echo.
echo *** Generating CGAME...
cd "%make-qvm-location%"code\cgame
call make-cgame.bat
cd..
echo.
echo *** Generating GAME/QAGAME...
cd "%make-qvm-location%"code\game
call make-game.bat
cd..
echo.
echo *** Generating UI...
cd "%make-qvm-location%"code\ui
call make-ui.bat
cd..


REM *** Remove any old pk3 and create a new one.
REM *** The pk3 is named like it is so it is always loaded last for testing.

echo.
echo *** Remove any old pk3 and create a new one...
echo.
set zipname=%make-qvm-location%bin\qvm\zzzz-code-*.pk3
del "%zipname%"
set zipname=%make-qvm-location%bin\qvm\zzzz-code-%date:~-4,4%%date:~-7,2%%date:~-10,2%.pk3
cd "%make-qvm-location%bin\qvm"
copy /y "%make-qvm-location%uifiles\*.menu" "%make-qvm-location%bin\qvm\ui"
copy /y "%make-qvm-location%uifiles\menus.txt" "%make-qvm-location%bin\qvm\ui"
copy /y "%make-qvm-location%uifiles\ingame.txt" "%make-qvm-location%bin\qvm\ui"
"%zipper%" a -tzip "%zipname%" vm\*.qvm
"%zipper%" a -tzip "%zipname%" ui\*.menu
"%zipper%" a -tzip "%zipname%" ui\menus.txt
"%zipper%" a -tzip "%zipname%" ui\ingame.txt

:END
echo.
echo.
echo.
echo You might wish to scroll up and check for any warnings or fatal errors before 
echo you press any key and this window closes...
echo.
echo.
pause
