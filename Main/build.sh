#!/bin/bash

set echo on

mkdir -p ../bin

# Get all cpp files
cppFiles=$(find . -type f -name "*.cpp")

outputFule="tl"

echo "Building $outputFule..."
g++ -o ../bin/$outputFule $cppFiles
