@echo off
setlocal enabledelayedexpansion

set INPUT_FILE=main.cpp
set INCLUDE_FOLDER="./include"
set OUTPUT_FILE=main.exe

set "CPPFiles="
set "headerIncludes="

for /r %INCLUDE_FOLDER% %%f in (*.h;*.hpp) do (
    set "headerIncludes=!headerIncludes! -I"%%f""
)

for /r %INCLUDE_FOLDER% %%f in (*.cpp) do (
    set "CPPFiles=!CPPFiles! "%%f""
)

echo Header Includes:
echo %headerIncludes%

echo List of CPP files:
echo %CPPFiles%

g++ %INPUT_FILE% %CPPFiles% %headerIncludes% -o %OUTPUT_FILE% -lstdc++ -I%INCLUDE_FOLDER%
