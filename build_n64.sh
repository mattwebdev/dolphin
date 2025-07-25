#!/bin/bash

# N64 Extension Build Script
# This script builds the N64 extension for Dolphin

echo "Building N64 Extension for Dolphin..."
echo "====================================="

# Create build directory
mkdir -p build_n64
cd build_n64

# Configure with N64 support enabled
echo "Configuring CMake with N64 support..."
cmake -DENABLE_N64=ON -DENABLE_TESTS=ON ../

if [ $? -ne 0 ]; then
    echo "CMake configuration failed!"
    exit 1
fi

# Build the N64 extension
echo "Building N64 extension..."
cmake --build . --target dolphin-n64

if [ $? -ne 0 ]; then
    echo "N64 extension build failed!"
    exit 1
fi

# Build the demo
echo "Building N64 demo..."
cmake --build . --target dolphin-n64-demo

if [ $? -ne 0 ]; then
    echo "N64 demo build failed!"
    exit 1
fi

# Build the memory test
echo "Building N64 memory test..."
cmake --build . --target dolphin-n64-memory-test

if [ $? -ne 0 ]; then
    echo "N64 memory test build failed!"
    exit 1
fi

echo ""
echo "Build completed successfully!"
echo "==========================="
echo "Available targets:"
echo "  - dolphin-n64 (library)"
echo "  - dolphin-n64-demo (executable)"
echo "  - dolphin-n64-memory-test (test executable)"
echo ""
echo "To run the demo:"
echo "  ./build_n64/dolphin-n64-demo"
echo ""
echo "To run the memory test:"
echo "  ./build_n64/dolphin-n64-memory-test"