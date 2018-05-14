@echo off
echo Corn Compiler will now be installed on this machine.
pause
echo Installing Corn compiler...
setx PATH "%PATH%;%~dp0..\Corn Compiler"
start "Checking Corn" "%~dp0corncheck.bat"
EXIT /B












