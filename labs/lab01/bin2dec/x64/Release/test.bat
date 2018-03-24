rem @echo off
set program="%1"
if program=="" goto err
set /a x=1

:1
set /a x+=1
echo Test1: > testResult.txt
echo %program%>>testResult.txt
%program% >> testResult.txt
if ERRORLEVEL 1 goto testFailed
bin2dec.exe  
if ERRORLEVEL 1 goto testFailed

:2
set /a x+=1
echo Test2: >> testResult.txt
echo %program% 101010>>testResult.txt
%program% 101010>>testResult.txt
if ERRORLEVEL 1 goto testFailed
bin2dec.exe 101010
if ERRORLEVEL 1 goto testFailed

:3
set /a x+=1
echo Test3: >> testResult.txt
echo %program% 123456789>>testResult.txt
%program% 123456789>>testResult.txt
if ERRORLEVEL 1 goto testFailed
bin2dec.exe 123456789
if ERRORLEVEL 1 goto testFailed

:4
set /a x+=1
echo Test4: >> testResult.txt
echo %program% -afsgdhfjgjk>>testResult.txt
%program% -afsgdhfjgjk>>testResult.txt
if ERRORLEVEL 1 goto testFailed
bin2dec.exe -afsgdhfjgjk
if ERRORLEVEL 1 goto testFailed

:5
set /a x+=1
echo Test5: >> testResult.txt
echo %program% 111111111111000000000000111111111>>testResult.txt
%program% 111111111111000000000000111111111>>testResult.txt
if ERRORLEVEL 1 goto testFailed
bin2dec.exe 111111111111000000000000111111111
if ERRORLEVEL 1 goto testFailed

:6
set /a x+=1
echo Test6: >> testResult.txt
echo %program% 11111111111111111111111111111111>>testResult.txt
%program% 11111111111111111111111111111111>>testResult.txt
if ERRORLEVEL 1 goto testFailed
bin2dec.exe 11111111111111111111111111111111
if ERRORLEVEL 1 goto testFailed

echo OK >> testResult.txt
exit /B

:testFailed
echo Testing failed >>testResult.txt
if not %x%==8 goto %x% else exit /B

:err
echo Usage: test.bat <Path to program> 