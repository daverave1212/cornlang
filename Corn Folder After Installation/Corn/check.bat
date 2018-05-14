@echo off
WHERE g++
IF %ERRORLEVEL% NEQ 0 goto CppNotWorking
goto CppWorking

:CppNotWorking
echo C++ Compiler state: Not Working
goto CheckCornState

:CppWorking
echo C++ Compiler state: Working
goto CheckCornState

:CheckCornState
WHERE corntest
IF %ERRORLEVEL% NEQ 0 goto CornNotWorking
goto CornWorking

:CornNotWorking
echo Corn Compiler state: Not Working
goto Finish

:CornWorking
echo Corn Compiler state: Working
goto Finish

:Finish
pause
exit /b

