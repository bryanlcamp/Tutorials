#!/bin/bash

# Stop on errors
set -e

# Clean old builds
echo "Cleaning previous builds..."
rm -rf build/
rm -rf bin/

# Create new build directory
echo "Creating build directory..."
mkdir build

# Navigate to the build directory
cd build

# Run CMake to configure the project
echo "Running cmake..."
cmake ..

# Build the project
echo "Building the project..."
cmake --build .

# Print success message
echo "Build complete! Binaries are located in the 'bin' directory."

# Optional: List contents of the bin directory
echo "Contents of bin/ directory:"
ls ../bin