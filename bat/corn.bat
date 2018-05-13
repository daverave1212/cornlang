@echo off

if "%1"=="c" goto cr
if "%1" == "create" goto cr
goto compile

:cr
xcopy /s "D:\Corn\Project Template" "%cd%\%2\"
if not exist "%cd%\%2\Binaries\" mkdir "%cd%\%2\Binaries\"
if not exist "%cd%\%2\C++ Source Code\" mkdir "%cd%\%2\C++ Source Code\"
goto fin

:compile
echo "Compiling .corn"
start /WAIT "" "D:\CornCompiler\CornCompiler.exe" "%cd%\%1" "%cd%\CPP Source Code\main.cpp"
g++ "%cd%\C++ Source Code\main.cpp" -o "%cd%\Binaries\%2"

:fin
echo Done!