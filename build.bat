@echo off
setlocal enabledelayedexpansion

set INCLUDE_FOLDER=%1
set OUTPUT_FILE=%2
set LIB_FOLDER=%3
set DEBUG=%4
set PCH_FILE=./include/glmpch.h
set PCH_OUTPUT=./include/glmpch.h.gch

rem Compile the precompiled header
if "%DEBUG%"=="true" (
    g++ -g -Winvalid-pch -x c++-header %PCH_FILE% -o %PCH_OUTPUT% -I"%INCLUDE_FOLDER%"
) else (
    g++ -Winvalid-pch -x c++-header %PCH_FILE% -o %PCH_OUTPUT% -I"%INCLUDE_FOLDER%"
)

set "CPPFiles="

for /r %%f in (*.cpp) do (
    set "CPPFiles=!CPPFiles! "%%f""
)
set "CPPFiles=!CPPFiles! "./src/glad.c""
set MAKEFLAGS=-j8
if "%DEBUG%"=="true" (
    g++ -g %CPPFiles% -Winvalid-pch -include %PCH_FILE% -o %OUTPUT_FILE% -lstdc++ -I"%INCLUDE_FOLDER%" -L"%LIB_FOLDER%" -lglfw3 -lopengl32 -lgdi32 -luser32
) else (
    g++ %CPPFiles% -Winvalid-pch -include %PCH_FILE% -o %OUTPUT_FILE% -lstdc++ -I"%INCLUDE_FOLDER%" -L"%LIB_FOLDER%" -lglfw3 -lopengl32 -lgdi32 -luser32
)

rem Run the executable
"%OUTPUT_FILE%"
