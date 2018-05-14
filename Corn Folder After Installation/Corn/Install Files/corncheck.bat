@echo off
echo Checking if Corn was installed successfully...
WHERE corn
IF %ERRORLEVEL% NEQ 0 goto FinishFailCorn
goto FinishSuccess

:FinishFailCorn
echo There was a problem installing Corn. Program will now exit.
exit /b

:FinishSuccess
echo Corn was successfully installed!
echo Use the command "corn help" for more information.












