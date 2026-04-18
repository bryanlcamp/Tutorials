cmake_minimum_required(VERSION 3.16)

# Set project name
project(Tutorials LANGUAGES CXX)

# Add version-specific directories under spsc (add v1 here)
add_subdirectory(spsc/v1)

# Optionally set a C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Explicitly specify intermediate build directories
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)