@echo off

if "%1"=="c" goto cr
goto compile

:cr
xcopy /s "D:\Corn" "%cd%\%2\"
if not exist "%cd%\%2\Binaries\" mkdir "%cd%\%2\Binaries\"
if not exist "%cd%\%2\CPP Source Code\" mkdir "%cd%\%2\CPP Source Code\"
goto fin

:compile
echo "Starting program..."
start /WAIT "" "D:\CornCompiler\CornCompiler.exe" "%cd%\%1" "%cd%\CPP Source Code\main.cpp"
g++ "%cd%\CPP Source Code\main.cpp" -o "%cd%\Binaries\%2"

:fin
echo Done!