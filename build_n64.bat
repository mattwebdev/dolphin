@echo off

REM N64 Extension Build Script for Windows
REM This script builds the N64 extension for Dolphin

echo Building N64 Extension for Dolphin...
echo =====================================

REM Create build directory
if not exist build_n64 mkdir build_n64
cd build_n64

REM Configure with N64 support enabled
echo Configuring CMake with N64 support...
cmake -DENABLE_N64=ON -DENABLE_TESTS=ON ..\

if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed!
    exit /b 1
)

REM Build the N64 extension
echo Building N64 extension...
cmake --build . --target dolphin-n64

if %ERRORLEVEL% neq 0 (
    echo N64 extension build failed!
    exit /b 1
)

REM Build the demo
echo Building N64 demo...
cmake --build . --target dolphin-n64-demo

if %ERRORLEVEL% neq 0 (
    echo N64 demo build failed!
    exit /b 1
)

REM Build the memory test
echo Building N64 memory test...
cmake --build . --target dolphin-n64-memory-test

if %ERRORLEVEL% neq 0 (
    echo N64 memory test build failed!
    exit /b 1
)

echo.
echo Build completed successfully!
echo ===========================
echo Available targets:
echo   - dolphin-n64 (library)
echo   - dolphin-n64-demo (executable)
echo   - dolphin-n64-memory-test (test executable)
echo.
echo To run the demo:
echo   build_n64\dolphin-n64-demo.exe
echo.
echo To run the memory test:
echo   build_n64\dolphin-n64-memory-test.exe

cd ..