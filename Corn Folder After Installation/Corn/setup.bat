@echo off

echo Checking if C++ is installed...
WHERE g++
IF %ERRORLEVEL% NEQ 0 goto InstallCPP
echo A C++ Compiler already exists on this machine.
goto CheckCorn

:InstallCPP
echo C++ compiler not found on your machine. It will be intalled now.
pause
setx PATH "%PATH%;%~dp0C++ Compiler\MinGW\bin"

:CheckCorn
echo Checking if Corn is already installed.
WHERE corntest
IF %ERRORLEVEL% NEQ 0 goto InstallCorn
echo Corn is already installed. The program will now exit.
echo NOTE: Use 'check.bat' to see if everything is in order before using corn.
pause
EXIT /B

:GenerateCornBats
start /WAIT "Breeding bats..." "%~dp0Install Files\batgen.exe" "%~dp0"

:InstallCorn
echo Corn will now be installed.
pause
start /WAIT "Breeding bats..." "%~dp0Install Files\batgen.exe" %~dp0
setx PATH "%PATH%;%~dp0Corn Bats"
echo Installation finished!
echo Use 'check.bat' to see if everything is in order before using corn!
pause
EXIT /B




