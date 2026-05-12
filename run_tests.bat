@echo off
setlocal

if not exist build mkdir build

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
if errorlevel 1 goto :fail

cmake --build build --config Debug
if errorlevel 1 goto :fail

ctest --test-dir build --output-on-failure -C Debug
goto :eof

:fail
echo Build failed.
exit /b 1
