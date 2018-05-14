@echo off
echo Checking if C++ was installed successfully...
WHERE g++
IF %ERRORLEVEL% NEQ 0 goto FinishFailCpp
goto InstallCorn

:FinishFailCpp
echo There was a problem installing the C++ compiler.
echo Program will now exit.
pause
EXIT /B

:InstallCorn
start "Installing Corn" "%~dp0corninstall.bat"
EXIT /B












