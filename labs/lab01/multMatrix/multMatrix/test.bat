rem @echo off
set program="%1"
if program=="" goto err

echo Test1: > testResult.txt
echo %program% one_matrixfile.txt>>testResult.txt
%program% one_matrixfile.txt >> testResult.txt
if ERRORLEVEL 1 goto testFailed
multmatrix.exe one_matrixfile.txt 
if ERRORLEVEL 1 goto testFailed

echo Test2: >> testResult.txt
echo %program% one_matrixfile.txt empty_matrixfile.txt>>testResult.txt
%program% one_matrixfile.txt empty_matrixfile.txt>>testResult.txt
if ERRORLEVEL 1 goto testFailed
multmatrix.exe one_matrixfile.txt empty_matrixfile.txt
if ERRORLEVEL 1 goto testFailed

echo Test3: >> testResult.txt
echo %program% symbol_matrixfile.txt one_matrixfile.txt>>testResult.txt
%program% symbol_matrixfile.txt one_matrixfile.txt>>testResult.txt
if ERRORLEVEL 1 goto testFailed
multmatrix.exe symbol_matrixfile.txt one_matrixfile.txt
if ERRORLEVEL 1 goto testFailed

echo Test4: >> testResult.txt
echo %program% matrixfile2.txt matrixfile3.txt>>testResult.txt
%program% matrixfile2.txt matrixfile3.txt>>testResult.txt
if ERRORLEVEL 1 goto testFailed
multmatrix.exe matrixfile2.txt matrixfile3.txt
if ERRORLEVEL 1 goto testFailed

echo Test5: >> testResult.txt
echo %program% matrixfile5.txt matrixfile6.txt>>testResult.txt
%program% matrixfile5.txt matrixfile6.txt>>testResult.txt
if ERRORLEVEL 1 goto testFailed
multmatrix.exe matrixfile5.txt matrixfile6.txt
if ERRORLEVEL 1 goto testFailed
                               
echo Test6: >> testResult.txt
echo %program% big_matrix_elements.txt matrixfile3.txt>>testResult.txt
%program% big_matrix_elements.txt matrixfile3.txt>>testResult.txt
if ERRORLEVEL 1 goto testFailed
multmatrix.exe big_matrix_elements.txt matrixfile3.txt
if ERRORLEVEL 1 goto testFailed

echo Test7: >> testResult.txt
echo %program% matrixfile3.txt few_items_matrix.txt>>testResult.txt
%program% matrixfile3.txt few_items_matrix.txt>>testResult.txt
if ERRORLEVEL 1 goto testFailed
multmatrix.exe matrixfile3.txt few_items_matrix.txt
if ERRORLEVEL 1 goto testFailed

echo OK
exit /B

:testFailed
echo Testing failed
exit /B

:err
echo Usage: test.bat <Path to program> 