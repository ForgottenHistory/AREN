@echo off
setlocal enabledelayedexpansion

set INCLUDE_FOLDER=%1
set OUTPUT_FILE=%2

set "CPPFiles="

for /r %%f in (*.cpp) do (
    set "CPPFiles=!CPPFiles! "%%f""
)

echo List of CPP files:
echo %CPPFiles%

g++ %CPPFiles% -o %OUTPUT_FILE% -lstdc++ -I"%INCLUDE_FOLDER%"
