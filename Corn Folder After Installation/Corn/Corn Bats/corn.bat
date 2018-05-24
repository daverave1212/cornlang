@echo off
if "%1"=="c" goto cr
if "%1"=="create" goto cr
if "%1"=="test" goto test
goto compile

:cr
:create
xcopy /s "D:\Corn\Project Template" "%cd%\%2\"
if not exist "%cd%\%2\Binaries\" mkdir "%cd%\%2\Binaries\"
if not exist "%cd%\%2\C++ Source Code\" mkdir "%cd%\%2\C++ Source Code\"
goto fin

:compile
echo Compiling .corn
start /WAIT "" "D:\Corn\Corn Compiler\CornCompiler.exe" "%cd%\%1" "%cd%\C++ Source Code\main.cpp"
pause
g++ -std=c++11 "%cd%\C++ Source Code\main.cpp" -o "%cd%\Binaries\%2"

:fin
if "%3"=="-r" goto ArgumentRun
echo Done!

:ArgumentRun
start /WAIT "" "%cd%\Binaries\%2.exe"
echo Done!