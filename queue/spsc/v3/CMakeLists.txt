cmake_minimum_required(VERSION 3.16)
project(SPSC_RingBuffer LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(spsc_v3_driver
    driver_v3.cpp
)

target_include_directories(spsc_v3_driver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)