cmake_minimum_required(VERSION 3.16)
project(SPSC_RingBuffer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(matching_engine/v1)
add_subdirectory(matching_engine/v2)
add_subdirectory(matching_engine/v3)

add_subdirectory(spsc/v1)
add_subdirectory(spsc/v2)
add_subdirectory(spsc/v3)