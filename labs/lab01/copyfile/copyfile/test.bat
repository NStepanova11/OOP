rem @echo off
set program="%1"
if program=="" goto err

echo Test1: > testResult.txt
echo %program% one_param.txt>>testResult.txt
%program% one_param.txt >> testResult.txt
if ERRORLEVEL 1 goto testFailed
copyfile.exe one_param.txt 
if ERRORLEVEL 1 goto testFailed

echo Test2: >> testResult.txt
echo %program% one_line.txt output.txt>>testResult.txt
%program% one_line.txt output.txt>>testResult.txt
if ERRORLEVEL 1 goto testFailed
copyfile.exe one_line.txt output.txt
if ERRORLEVEL 1 goto testFailed

echo Test3: >> testResult.txt
echo %program% many_lines.txt output.txt>>testResult.txt
%program% many_lines.txt output.txt>>testResult.txt
if ERRORLEVEL 1 goto testFailed
copyfile.exe many_lines.txt output.txt
if ERRORLEVEL 1 goto testFailed

echo Test4: >> testResult.txt
echo %program% input.txt non_existing.txt>>testResult.txt
%program% input.txt non_existing.txt>>testResult.txt
if ERRORLEVEL 1 goto testFailed
copyfile.exe input.txt non_existing.txt
if ERRORLEVEL 1 goto testFailed

echo OK
exit /B

:testFailed
echo Testing failed
exit /B

:err
echo Usage: test.bat <Path to program> 