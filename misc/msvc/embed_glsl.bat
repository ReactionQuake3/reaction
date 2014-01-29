@echo off
setlocal ENABLEDELAYEDEXPANSION

if "%~1" == "" goto noinput
if "%~2" == "" goto nooutput

echo // Generated automatically from %~nx1, do not modify...>%2
echo const char *fallbackShader_%~n1 = >>%2
for /f "tokens=*" %%l in (%1) do call :stringize %%l>>%2
echo ;>>%2

set ERRORLEVEL=0

goto end

:stringize
set str=%*
if "!str!" EQU "" (
	echo "\n"
	goto :eof
)
set str=!str:\=\\!
set str=!str:^"=\^"!
echo "!str!\n"
goto :eof

:noinput
echo No input file specified 1>&2
set ERRORLEVEL=1
goto end

:nooutput
echo No output file specified 1>&2
set ERRORLEVEL=2
goto end

:end
endlocal
